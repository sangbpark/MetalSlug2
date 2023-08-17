#include "sbHeavyBullet.h"
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

namespace sb
{
	HeavyBullet::HeavyBullet()
		:mDeathTime(0.5f)
		,mDown(false)
	{
		ResourceLoad();
	}
	HeavyBullet::~HeavyBullet()
	{
	}
	void HeavyBullet::Initialize()
	{
	}
	void HeavyBullet::Update()
	{
		GameObject::Update();
		if(mDirect == true)
		{
			if(mDown == false)
			{
				Transform* tr = GetComponent<Transform>();
				Collider* col = GetComponent<Collider>();
				tr->SetRotation(-mDegree);
				Vector2 pos = tr->GetPosition();
				pos = BulletRotate(pos, mDegree, 1500.0f * Time::DeltaTime(), mDirect);
				tr->SetPosition(pos);
				col->SetOffset(BulletRotate(pos, mDegree, 30.0f,mDirect) - pos);
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Collider* col = GetComponent<Collider>();
				tr->SetRotation(mDegree);
				Vector2 pos = tr->GetPosition();
				pos = BulletRotate(pos, -mDegree, 1500.0f * Time::DeltaTime(), mDirect);
				tr->SetPosition(pos);
				col->SetOffset(BulletRotate(pos, -mDegree, 30.0f, mDirect) - pos);
			}
		}
		else
		{
			if (mDown == false)
			{
				Transform* tr = GetComponent<Transform>();
				Collider* col = GetComponent<Collider>();
				mDegree -= 180;
				tr->SetRotation(mDegree);
				mDegree += 180;
				Vector2 pos = tr->GetPosition();
				pos = BulletRotate(pos, mDegree, -1500.0f * Time::DeltaTime(),mDirect);
				
				tr->SetPosition(pos);
				col->SetOffset(BulletRotate(pos, mDegree, -30.0f, mDirect) - pos);
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Collider* col = GetComponent<Collider>();
				mDegree += 180;
				tr->SetRotation(-mDegree);
				mDegree -= 180;
				Vector2 pos = tr->GetPosition();
				pos = BulletRotate(pos, -mDegree, -1500.0f * Time::DeltaTime(), mDirect);
				tr->SetPosition(pos);
				col->SetOffset(BulletRotate(pos, -mDegree, -30.0f, mDirect) - pos);
			}
		}
		mDeathTime -= Time::DeltaTime();
		if (mDeathTime < 0.0f)
		{
			Destroy(this);
		}
	}
	void HeavyBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HeavyBullet::OnCollisionEnter(Collider* other)
	{
		ArabianDeath(other);
		FloorEnter(other);
		HOldManEnter(other);
		MiddleBossLauncherEnter(other);
		TruckCollisionEnter(other);
		BerserkerCollisionEnter(other);
	}
	void HeavyBullet::OnCollisionStay(Collider* other)
	{
	}
	void HeavyBullet::OnCollisionExit(Collider* other)
	{
	}
	void HeavyBullet::ArabianDeath(Collider* other)
	{
		Arabian* ab = dynamic_cast<Arabian*>(other->GetOwner());
		if (ab == nullptr || ab->GetArabianState() == Arabian::Arabianstate::death)
			return;
		else
		{
			Destroy(this);
		}
	}
	void HeavyBullet::FloorEnter(Collider* other)
	{
		Floor* fl = dynamic_cast<Floor*>(other->GetOwner());
		if (fl == nullptr)
			return;
		else
			Destroy(this);
	}

	void HeavyBullet::HOldManEnter(Collider* other)
	{
		HOldMan* holdman = dynamic_cast<HOldMan*>(other->GetOwner());
		if (holdman == nullptr
			|| !(holdman->GetHOldManState() == HOldMan::eState::Idle))
			return;
		else
			Destroy(this);
	}

	void HeavyBullet::MiddleBossLauncherEnter(Collider* other)
	{
		MiddleBossLauncher* mbl = dynamic_cast<MiddleBossLauncher*>(other->GetOwner());
		if (mbl == nullptr
			|| mbl->GetMiddleBossLauncher() == MiddleBossLauncher::eState::Death)
			return;
		else
			Destroy(this);
	}
	void HeavyBullet::TruckCollisionEnter(Collider* other)
	{
		Truck* tk = dynamic_cast<Truck*>(other->GetOwner());
		if (tk == nullptr
			|| tk->GetTruckState() != Truck::eState::Create)
			return;
		else
			Destroy(this);
	}

	void HeavyBullet::BerserkerCollisionEnter(Collider* other)
	{
		Berserker* berserker = dynamic_cast<Berserker*>(other->GetOwner());
		if (berserker == nullptr
			|| berserker->GetBerserkerState() == Berserker::eState::Death)
			return;
		else
			Destroy(this);
	}

	void HeavyBullet::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"HeavyBullet",
			L"..\\Resource\\effect\\DS DSi - Metal Slug 7 Metal Slug XX - Weapon SFX.png");

		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		Collider* col = AddComponent<Collider>();
		Transform* tr = AddComponent<Transform>();
		sr->SetImage(image);
		sr->SetScale(Vector2(4.5f, 4.5f));
		col->SetSize(Vector2(20.0f, 20.0f));
	}

}