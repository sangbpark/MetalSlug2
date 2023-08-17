#include "sbCameraPlayer.h"
#include "sbTransform.h"
#include "sbPlayerBottom.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbObject.h"


namespace sb
{
	
	CameraPlayer::CameraPlayer()
		:mState(eState::Idle)
		,mStage(eStage::Idle)
		, mTime(0.0f)
	{
		Ui* ui = object::Instantiate<Ui>(enums::eLayerType::UI, Vector2(100.0f, 100.0f));
		mUi = ui;
		ControlTower* ControlTower1 = object::Instantiate<ControlTower>(enums::eLayerType::ControlTower, Vector2(6300.0f, 700.0f));
		ControlTower1->SetStage(ControlTower::eStage::Truck);
		mControlTower.push_back(ControlTower1);
		ControlTower* ControlTower2 = object::Instantiate<ControlTower>(enums::eLayerType::ControlTower, Vector2(9000.0f, 700.0f));
		ControlTower2->SetStage(ControlTower::eStage::MiddleBoss);
		ControlTower2->SetControlTowerState(ControlTower::eState::Create);
		mControlTower.push_back(ControlTower2);
	}
	CameraPlayer::~CameraPlayer()
	{
	}
	void CameraPlayer::Initialize()
	{
	}
	void CameraPlayer::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::CameraPlayer::eState::Idle:
			Idle();
			break;
		case sb::CameraPlayer::eState::Move:
			Move();
			break;
		case sb::CameraPlayer::eState::Rock:
			Rock();
			break;
		case sb::CameraPlayer::eState::Resetting:
			Resetting();
			break;
		case sb::CameraPlayer::eState::End:
			break;
		default:
			break;
		}
		UiSetting();
		
	}
	void CameraPlayer::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CameraPlayer::Idle()
	{

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = PlayerBottom::GetPlayerPosition();
		math::Vector2 pos2 = tr->GetPosition();

		pos.y = pos2.y;

		if (pos.x <= pos2.x)
		{
			pos.x = pos2.x;
		}

		tr->SetPosition(pos);

		SearchControlTower();
	}
	void CameraPlayer::Move()
	{
		Transform* tr = GetComponent<Transform>();
		if (mStage == eStage::Truck)
		{
			Vector2 pos = tr->GetPosition();
			pos.x += 100.0f * Time::DeltaTime();
			pos.y -= 50.0f * Time::DeltaTime();
			if (pos.y <= 295.0f)
				pos.y = 295.0f;
			if (pos.x >= 6700.0f)
			{
				pos.x = 6700.0f;
				mState = eState::Rock;
			}
			tr->SetPosition(pos);
		}
		else if (mStage == eStage::MiddleBoss)
		{
			Vector2 pos = tr->GetPosition();
			pos.x += 100.0f * Time::DeltaTime();
			if (pos.x >= 9300.0f)
			{

				pos.x = 9300.0f;
				pos.y -= 50.0f * Time::DeltaTime();
				if (pos.y <= 282.0f)
				{
					pos.y = 282.0f;
					mState = eState::Rock;
				}
			}
			tr->SetPosition(pos);
		}
	}
	void CameraPlayer::Rock()
	{
		SearchControlTowerTarget();
	}
	void CameraPlayer::Resetting()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = PlayerBottom::GetPlayerPosition();
		math::Vector2 pos2 = tr->GetPosition();

		if (pos.x - pos2.x > 0.0f)
		{
			pos2.x += 400.0f * Time::DeltaTime();
			tr->SetPosition(pos2);
		}
		else if (pos.x - pos2.x <= 0.0f)
		{
			mState = eState::Idle;
		}
	}
	void CameraPlayer::SearchControlTower()
	{
		for (auto iter = mControlTower.begin()
			; iter != mControlTower.end()
			; iter++)
		{
			if ((*iter)->GetActive() == true)
			{
				if ((*iter)->GetStage() == ControlTower::eStage::Truck)
					mStage = eStage::Truck;
				else if ((*iter)->GetStage() == ControlTower::eStage::MiddleBoss)
					mStage = eStage::MiddleBoss;
				else if ((*iter)->GetStage() == ControlTower::eStage::Wall)
					mStage = eStage::Wall;
				else if ((*iter)->GetStage() == ControlTower::eStage::Helicopter)
					mStage = eStage::Helicopter;
				else if ((*iter)->GetStage() == ControlTower::eStage::Boss)
					mStage = eStage::Boss;

				mState = eState::Move;
				return;
			}
		}
	}
	void CameraPlayer::SearchControlTowerTarget()
	{
		for (auto iter = mControlTower.begin()
			; iter != mControlTower.end()
			; iter++)
		{
			if ((*iter)->GetActive() == true)
			{
				if ((*iter)->GetTargetLive() == false)
				{
					auto controltower = *iter;
					controltower->SetActive(false);
					controltower->SetTargetlive(true);
					mState = eState::Resetting;
				}
			}
			
		}
	}

	void CameraPlayer::UiSetting()
	{
		Ui* ui = dynamic_cast<Ui*>(mUi);
		PlayerBottom* pb = dynamic_cast<PlayerBottom*>(mOwner);
		Transform* uitr = ui->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		math::Vector2 uipos = uitr->GetPosition();
		ui->SetPlayerBomb(pb->GetEfBombCount());
		ui->SetPlayerHeavyBullet(pb->GetHeavyBulletCount());
		uipos.x = pos.x - 320.0f;
		uipos.y = pos.y - 400.0f;
		uitr->SetPosition(uipos);
		pb->SetCameraTransform(pos);
		if (mState == eState::Move)
		{
			pb->SetStopState(true);
		}
		if (pb->GetStopState() == true
			&& mState != eState::Move)
			pb->SetStopState(false);
	}
}