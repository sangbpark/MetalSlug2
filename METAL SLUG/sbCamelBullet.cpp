#include "sbCamelBullet.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbCollider.h"
#include "sbArabian.h"
#include "sbFloor.h"
#include "sbHOldMan.h"
#include "sbMiddleBossLauncher.h"
#include "sbTruck.h"
#include "sbBerserker.h"
#include "sbAnimator.h"
#include "sbCamelBullet.h"
#include "sbBoss.h"

namespace sb
{

	CamelBullet::CamelBullet()
		: mDeathTime(0.5f)
		, mState(eCamelBulletState::Idle)
	{
		ResourceLoad();
	}
	CamelBullet::~CamelBullet()
	{
	}
	void CamelBullet::Initialize()
	{
	}
	void CamelBullet::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::CamelBullet::eCamelBulletState::Idle:
			Idle();
			break;
		case sb::CamelBullet::eCamelBulletState::Death:
			Death();
			break;
		default:
			break;
		}
	}
	void CamelBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CamelBullet::OnCollisionEnter(Collider* other)
	{
		ArabianDeath(other);
		FloorEnter(other);
		HOldManEnter(other);
		MiddleBossLauncherEnter(other);
		TruckCollisionEnter(other);
		BerserkerCollisionEnter(other);
		BossCollisionEnter(other);
	}
	void CamelBullet::OnCollisionStay(Collider* other)
	{
	}
	void CamelBullet::OnCollisionExit(Collider* other)
	{
	}

	void CamelBullet::Idle()
	{
		Transform* tr = GetComponent<Transform>();
		Collider* col = GetComponent<Collider>();
		tr->SetRotation(-mDegree);
		Vector2 pos = tr->GetPosition();
		pos = BulletRotate2(pos, mDegree, 1500.0f * Time::DeltaTime());
		tr->SetPosition(pos);
		col->SetOffset(BulletRotate2(pos, mDegree, 30.0f) - pos);
	}

	void CamelBullet::Death()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			Destroy(this);
		}
	}

	void CamelBullet::ArabianDeath(Collider* other)
	{
		Arabian* ab = dynamic_cast<Arabian*>(other->GetOwner());
		if (ab == nullptr || ab->GetArabianState() == Arabian::Arabianstate::death)
			return;
		else
		{
			Animator* at = AddComponent<Animator>();
			at->PlayAnimation(L"CamelBulletdeathAX");
			mState = eCamelBulletState::Death;
		}
	}
	void CamelBullet::FloorEnter(Collider* other)
	{
		Floor* fl = dynamic_cast<Floor*>(other->GetOwner());
		if (fl == nullptr)
			return;
		else
		{
			Animator* at = AddComponent<Animator>();
			at->PlayAnimation(L"CamelBulletdeathAX");
			mState = eCamelBulletState::Death;
		}
	}
	void CamelBullet::HOldManEnter(Collider* other)
	{
		HOldMan* holdman = dynamic_cast<HOldMan*>(other->GetOwner());
		if (holdman == nullptr
			|| !(holdman->GetHOldManState() == HOldMan::eState::Idle))
			return;
		else
		{
			Animator* at = AddComponent<Animator>();
			at->PlayAnimation(L"CamelBulletdeathAX");
			mState = eCamelBulletState::Death;
		}
	}
	void CamelBullet::MiddleBossLauncherEnter(Collider* other)
	{
		MiddleBossLauncher* mbl = dynamic_cast<MiddleBossLauncher*>(other->GetOwner());
		if (mbl == nullptr
			|| mbl->GetMiddleBossLauncher() == MiddleBossLauncher::eState::Death)
			return;
		else
		{
			Animator* at = AddComponent<Animator>();
			at->PlayAnimation(L"CamelBulletdeathAX");
			mState = eCamelBulletState::Death;
		}
	}
	void CamelBullet::TruckCollisionEnter(Collider* other)
	{
		Truck* tk = dynamic_cast<Truck*>(other->GetOwner());
		if (tk == nullptr
			|| tk->GetTruckState() != Truck::eState::Create)
			return;
		else
		{
			Animator* at = AddComponent<Animator>();
			at->PlayAnimation(L"CamelBulletdeathAX");
			mState = eCamelBulletState::Death;
		}
	}
	void CamelBullet::BerserkerCollisionEnter(Collider* other)
	{
		Berserker* berserker = dynamic_cast<Berserker*>(other->GetOwner());
		if (berserker == nullptr
			|| berserker->GetBerserkerState() == Berserker::eState::Death)
			return;
		else
		{
			Animator* at = AddComponent<Animator>();
			at->PlayAnimation(L"CamelBulletdeathAX");
			mState = eCamelBulletState::Death;
		}
	}
	void CamelBullet::BossCollisionEnter(Collider* other)
	{
		Boss* boss = dynamic_cast<Boss*>(other->GetOwner());
		if (boss == nullptr
			|| boss->GetBossStage() == Boss::eBossStage::Death)
			return;
		else
		{
			Animator* at = AddComponent<Animator>();
			at->PlayAnimation(L"CamelBulletdeathAX");
			mState = eCamelBulletState::Death;
		}
	}
	void CamelBullet::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"CamelBullet",
			L"..\\Resource\\Vehicle\\camelbullet.png");
		Animator* at = AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();
		Transform* tr = AddComponent<Transform>();
		at->CreateAnimation(L"CamelBulletIdleAX", image, Vector2(0.0f, 396.0f), Vector2(44.0f, 44.0f), 1, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"CamelBulletdeathAX", image, Vector2(0.0f, 352.0f), Vector2(44.0f, 44.0f), 10, Vector2(0.0f, 0.0f));
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"CamelBulletIdleAX");
		col->SetSize(Vector2(20.0f, 20.0f));
	}
}