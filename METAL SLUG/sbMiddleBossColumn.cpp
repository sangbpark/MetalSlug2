#include "sbMiddleBossColumn.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbTransform.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbTime.h"
#include "sbPlayerBottom.h"
#include "sbObject.h"
#include "sbControlTower.h"

namespace sb
{
	MiddleBossColumn::MiddleBossColumn()
		:mState(eState::Create)
		, mCreatLauncher(false)
		, mPlayerDistance(0.0f)
		, mTime(0.0f)
	{
		ResourseLoad();
	}
	MiddleBossColumn::~MiddleBossColumn()
	{
	}
	void MiddleBossColumn::Initialize()
	{
	}
	void MiddleBossColumn::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayerDistance = fabs(pos.x - PlayerBottom::GetPlayerPosition().x);
		if (mPlayerDistance > 2000.0f)
			return;
		GameObject::Update();
		switch (mState)
		{
		case::sb::MiddleBossColumn::eState::Create:
			Create();
			break;
		case::sb::MiddleBossColumn::eState::Encounter:
			Encounter();
			break;
		case::sb::MiddleBossColumn::eState::Animation:
			Animation();
			break;
		case::sb::MiddleBossColumn::eState::Find:
			Find();
			break;
		case::sb::MiddleBossColumn::eState::Idle:
			Idle();
			break;
		case::sb::MiddleBossColumn::eState::Death:
			Death();
			break;
		}
	}
	void MiddleBossColumn::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayerDistance = fabs(pos.x - PlayerBottom::GetPlayerPosition().x);
		if (mPlayerDistance > 2000.0f)
			return;
		GameObject::Render(hdc);
	}
	void MiddleBossColumn::Idle()
	{

	}
	void MiddleBossColumn::Create()
	{
		Animator* at = GetComponent<Animator>();
		if(mPosition == ePosition::Left)
			at->PlayAnimation(L"MiddleBossLeftIdleAX");
		else if (mPosition == ePosition::Middle)
			at->PlayAnimation(L"MiddleBossMiddleIdleAX");
		else if (mPosition == ePosition::Right)
			at->PlayAnimation(L"MiddleBossRIghtIdleAX");
		mState = eState::Find;

	}
	void MiddleBossColumn::Encounter()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();
		if (mPosition == ePosition::Left)
		{
			Vector2 pos = tr->GetPosition();
			pos = BulletRotate(pos, 100, 50.0f * Time::DeltaTime(),true);
			tr->SetPosition(pos);
			if (pos.y <= 50.0f)
			{
				pos.y = 50.0f;
				at->PlayAnimation(L"MiddleBossLeftanimationAX");
				mState = eState::Animation;
			}
		}
		else if (mPosition == ePosition::Middle)
		{
			Vector2 pos = tr->GetPosition();
			pos.y -= 50.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			if (pos.y <= 50.0f)
			{
				pos.y = 50.0f;
				at->PlayAnimation(L"MiddleBossMiddleanimationAX");
				mState = eState::Animation;
			}
		}
		else if (mPosition == ePosition::Right)
		{
			Vector2 pos = tr->GetPosition();
			pos = BulletRotate(pos, 80, 50.0f * Time::DeltaTime(), true);
			tr->SetPosition(pos);
			if (pos.y <= 50.0f)
			{
				pos.y = 50.0f;
				at->PlayAnimation(L"MiddleBossRIghtanimationAX");
				mState = eState::Animation;
			}
		}


	
	}
	void MiddleBossColumn::Animation()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* at = GetComponent<Animator>();
		if (at->GetIndex() == 29
			&& mCreatLauncher == false)
		{

			Vector2 pos = tr->GetPosition();
			pos += Vector2(60.0f, -100.0f);
			MiddleBossLauncher* middlebosslauncher = object::Instantiate <MiddleBossLauncher>(eLayerType::Monster, pos);
			middlebosslauncher->SetLauncherPositon(LauncherPosition(mPosition));
			middlebosslauncher->SetmOwner(this);
			mCreatLauncher = true;
		}
		if (at->Getcomplete())
		{
			mState = eState::Idle;
		}
		
	}
	void MiddleBossColumn::Find()
	{
		if (PlayerBottom::GetPlayerPosition().x >= 8900.0f)
		{
			mTime += Time::DeltaTime();
			if(mTime >= 3.4f)
			{
				mTime = 0.0f;
				mState = eState::Encounter;
			}
		}
	}

	void MiddleBossColumn::Death()
	{
		Animator* at = GetComponent<Animator>();
		if(mPosition == ePosition::Left)
			at->PlayAnimation(L"MiddleBossLeftdeathAX");
		else if (mPosition == ePosition::Middle)
			at->PlayAnimation(L"MiddleBossMiddledeathAX");
		else if (mPosition == ePosition::Right)
			at->PlayAnimation(L"MiddleBossRIghtdeathAX");
			Transform* tr = GetComponent<Transform>();
		if (PlayerBottom::GetPlayerPosition().x - tr->GetPosition().x > 2000.0f)
			Destroy(this);
	}

	MiddleBossLauncher::ePosition MiddleBossColumn::LauncherPosition(ePosition mPosition)
	{
		if (mPosition == ePosition::Left)
			return MiddleBossLauncher::ePosition::Left;
		else if (mPosition == ePosition::Middle)
			return MiddleBossLauncher::ePosition::Middle;
		else if (mPosition == ePosition::Right)
			return MiddleBossLauncher::ePosition::Right;
	}

	void MiddleBossColumn::ResourseLoad()
	{
		Texture* imagePlayer = Resources::Load<Texture>(L"MiddleBoss"
			, L"..\\Resource\\Monster\\middle boss.bmp");
		Animator* at = this->AddComponent<Animator>();
		Transform* tr = this->AddComponent<Transform>();
		at->CreateAnimation(L"MiddleBossLeftIdleAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(132.0f, 176.0f), 1);
		at->CreateAnimation(L"MiddleBossMiddleIdleAX", imagePlayer, Vector2(0.0f, 176.0f), Vector2(132.0f, 176.0f), 1);
		at->CreateAnimation(L"MiddleBossRIghtIdleAX", imagePlayer, Vector2(0.0f, 352.0f), Vector2(132.0f, 176.0f), 1);
		at->CreateAnimation(L"MiddleBossLeftanimationAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(132.0f, 176.0f), 30);
		at->CreateAnimation(L"MiddleBossMiddleanimationAX", imagePlayer, Vector2(0.0f, 176.0f), Vector2(132.0f, 176.0f), 30);
		at->CreateAnimation(L"MiddleBossRIghtanimationAX", imagePlayer, Vector2(0.0f, 352.0f), Vector2(132.0f, 176.0f), 30);
		at->CreateAnimation(L"MiddleBossLeftdeathAX", imagePlayer, Vector2(0.0f, 1056.0f), Vector2(132.0f, 176.0f), 1);
		at->CreateAnimation(L"MiddleBossMiddledeathAX", imagePlayer, Vector2(132.0f, 1056.0f), Vector2(132.0f, 176.0f), 1);
		at->CreateAnimation(L"MiddleBossRIghtdeathAX", imagePlayer, Vector2(264.0f, 1056.0f), Vector2(132.0f, 176.0f), 1);
		at->PlayAnimation(L"MiddleBossIdleAX");
		at->SetScale(Vector2(4.5f, 4.5f));
	}
}