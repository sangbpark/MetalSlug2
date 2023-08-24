#include "sbMiddleBossRocket.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbCollider.h"
#include "sbAnimator.h"
#include "sbPlayerBottom.h"
#include "sbHeavyBullet.h"
#include "sbNormalBullet.h"
#include "sbEfBomb.h"
#include "sbFloor.h"

namespace sb
{
	MiddleBossRocket::MiddleBossRocket()
		:mHp(0.5f)
		,mState(eState::Create)
		, mRockOnTime(0.0f)
		, mRotation(0.0f)
		, mDeath(false)
	{
		ResourceLoad();
	}
	MiddleBossRocket::~MiddleBossRocket()
	{
	}
	void MiddleBossRocket::Initialize()
	{
	}
	void MiddleBossRocket::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::MiddleBossRocket::eState::Create:
			Create();
			break;
		case sb::MiddleBossRocket::eState::Idle:
			Idle();
			break;
		case sb::MiddleBossRocket::eState::Rockon:
			RockOn();
			break;
		case sb::MiddleBossRocket::eState::Death:
			Death();
			break;
		default:
			break;
		}
	}
	void MiddleBossRocket::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MiddleBossRocket::OnCollisionEnter(Collider* other)
	{
		if (!(mState == eState::Death))
		{
			HeavyBulletCollisionEnter(other);
			NormalBulletCollisionEnter(other);
			EfBombCollisionEnter(other);
			PlayerCollisionEnter(other);
			FloorCollisionEnter(other);
			if (mHp <= 0.0f)
			{
				SetMiddleBossRockeDeath();
			}
		}
	}
	void MiddleBossRocket::OnCollisionStay(Collider* other)
	{
	}
	void MiddleBossRocket::OnCollisionExit(Collider* other)
	{
	}
	void MiddleBossRocket::Idle()
	{
		mRockOnTime += Time::DeltaTime();
		Transform* tr = GetComponent<Transform>();
		if (mPosition == ePosition::Left)
		{
			Vector2 pos = tr->GetPosition();
			pos.x += 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (mPosition == ePosition::Middle)
		{
			Vector2 pos = tr->GetPosition();
			mRotation = 180.0f;
			tr->SetRotation(mRotation);
			pos.x -= 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (mPosition == ePosition::Right)
		{
			Vector2 pos = tr->GetPosition();
			mRotation = 180.0f;
			tr->SetRotation(mRotation);
			pos.x -= 100.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (mRockOnTime >= 2.0f)
			mState = eState::Rockon;
	}
	void MiddleBossRocket::Create()
	{
	
		Collider* col = GetComponent<Collider>();

		if (mPosition == ePosition::Left)
		{
			col->SetOffset(Vector2(30.0f, 0.0f));
		}
		else if (mPosition == ePosition::Middle)
		{
			col->SetOffset(Vector2(-30.0f, 0.0f));
		}
		else if (mPosition == ePosition::Right)
		{
			col->SetOffset(Vector2(-30.0f, 0.0f));
		}	
		mState = eState::Idle;
	}
	void MiddleBossRocket::RockOn()
	{
		Collider* col = GetComponent<Collider>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Vector2 PlayerPos = PlayerBottom::GetPlayerPosition();
		Vector2 pos2 = PlayerPos - pos;
		float Radian = atan2(pos2.y, pos2.x);
		float Degree = Radian * (180 / PI);
		if (Degree < mRotation)
		{
			mRotation -= 70 * Time::DeltaTime();
		}
		else if (Degree > mRotation)
		{
			mRotation += 70 * Time::DeltaTime();
		}
		else if (Degree == mRotation)
		{
			mRotation = Degree;
		}
		tr->SetRotation(mRotation);;
		if(PlayerPos.y < pos.y)
		{
			pos2 = BulletRotate(pos, mRotation, 30, true);
			pos2 = pos2 - pos;
			col->SetOffset(pos2);
			pos = BulletRotate(pos, mRotation, 180.0f * Time::DeltaTime(), true);
			tr->SetPosition(pos);
		}
		else
		{
			pos2 = BulletRotate(pos, mRotation, 30, false);
			pos2 = pos2 - pos;
			col->SetOffset(pos2);
			pos = BulletRotate(pos, mRotation, 180.0f * Time::DeltaTime(), false);
			tr->SetPosition(pos);
		}
	}
	void MiddleBossRocket::Death()
	{
		mDeath = true;
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
			Destroy(this);
	}
	void MiddleBossRocket::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"middlerokect",
			L"..\\Resource\\effect\\MiddleRocket.png");
		Texture* images = Resources::Load<Texture>(L"middlerokectd",
			L"..\\Resource\\effect\\middlebossdeath.bmp");
		Transform* tr = this->AddComponent<Transform>();
		Animator* at = AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();
		at->CreateAnimation(L"middlerokectonAX", image, Vector2(0.0f, 0.0f), Vector2(44.0f, 44.0f), 3);
		at->CreateAnimation(L"middlerokectdeathAX", images, Vector2(0.0f, 0.0f), Vector2(44.0f, 44.0f), 28);
		at->SetScale(Vector2(3.5f, 3.5f));
		at->PlayAnimation(L"middlerokectonAX");
		col->SetSize(Vector2(50.0f, 50.0f));
		col->SetOffset(Vector2(-20.0f, 0.0f));
	}
	void MiddleBossRocket::HeavyBulletCollisionEnter(Collider* other)
	{
		HeavyBullet* hb = dynamic_cast<HeavyBullet*>(other->GetOwner());
		if (hb == nullptr)
			return;
		else
		{
			
			mHp -= 0.7;
		}
	}
	void MiddleBossRocket::NormalBulletCollisionEnter(Collider* other)
	{
		sbNormalBullet* nb = dynamic_cast<sbNormalBullet*>(other->GetOwner());
		if (nb == nullptr)
			return;
		else
		{
			mHp -= 1;
		}
	}
	void MiddleBossRocket::EfBombCollisionEnter(Collider* other)
	{
		EfBomb* eb = dynamic_cast<EfBomb*>(other->GetOwner());
		if (eb == nullptr)
			return;
		else
		{
			mHp -= 5;
		}
	}
	void MiddleBossRocket::PlayerCollisionEnter(Collider* other)
	{
		PlayerBottom* pb = dynamic_cast<PlayerBottom*>(other->GetOwner());
		if (pb == nullptr)
			return;
		else
		{
			mHp -= 2;
		}
	}
	void MiddleBossRocket::FloorCollisionEnter(Collider* other)
	{
		Floor* fr = dynamic_cast<Floor*>(other->GetOwner());
		if (fr == nullptr)
			return;
		else
		{
			mHp -= 2;
		}
	}
	void MiddleBossRocket::SetMiddleBossRockeDeath()
	{
		Animator* at = GetComponent<Animator>();
		if (at == nullptr)		
			return;
		at->PlayAnimation(L"middlerokectdeathAX");
		mState = eState::Death;
	}
}