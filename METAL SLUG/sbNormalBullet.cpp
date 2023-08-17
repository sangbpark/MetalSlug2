#include "sbNormalBullet.h"
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
#include "sbNormalBullet.h"
#include "sbTruck.h"
#include "sbBerserker.h"

namespace sb
{
	sbNormalBullet::sbNormalBullet()
		:mDeathTime(2.0f)
		,mCreat(true)
	{
	}
	sbNormalBullet::~sbNormalBullet()
	{
	}
	void sbNormalBullet::Initialize()
	{
	}
	void sbNormalBullet::Update()
	{
		GameObject::Update();
		
		if (mCreat)
		{
			ResourceLoad();
			mCreat = false;

		}
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (mState == eBulletState::Right)
		{
			pos.x += 1000.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			mDeathTime -= Time::DeltaTime();
			if (mDeathTime < 0.0f)
			{
				Destroy(this);
			}
		}
		else if (mState == eBulletState::Left)
		{
			pos.x -= 1000.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			mDeathTime -= Time::DeltaTime();
			if (mDeathTime < 0.0f)
			{
				Destroy(this);
			}
		}
		else if (mState == eBulletState::Up)
		{
			pos.y -= 1000.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			mDeathTime -= Time::DeltaTime();
			if (mDeathTime < 0.0f)
			{
				Destroy(this);
			}
		}
		else if (mState == eBulletState::Down)
		{
			pos.y += 1000.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			mDeathTime -= Time::DeltaTime();
			if (mDeathTime < 0.0f)
			{
				Destroy(this);
			}
		}

	}
	void sbNormalBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void sbNormalBullet::OnCollisionEnter(Collider* other)
	{
		ArabianDeath(other);
		FloorEnter(other);
		HOldManEnter(other);
		MiddleBossLauncherEnter(other);
		TruckCollisionEnter(other);
		BerserkerCollisionEnter(other);
	}
	void sbNormalBullet::OnCollisionStay(Collider* other)
	{
	
	}
	void sbNormalBullet::OnCollisionExit(Collider* other)
	{
	
	}
	void sbNormalBullet::ArabianDeath(Collider* other)
	{
		Arabian* ab = dynamic_cast<Arabian*>(other->GetOwner());
		if (ab == nullptr || ab->GetArabianState() == Arabian::Arabianstate::death)
			return;
		else
		{
			Destroy(this);
		}
	}
	void sbNormalBullet::MiddleBossLauncherEnter(Collider* other)
	{
		MiddleBossLauncher* mbl = dynamic_cast<MiddleBossLauncher*>(other->GetOwner());
		if (mbl == nullptr
			|| mbl->GetMiddleBossLauncher() == MiddleBossLauncher::eState::Death)
			return;
		else
			Destroy(this);
	}
	void sbNormalBullet::FloorEnter(Collider* other)
	{
		Floor* fl = dynamic_cast<Floor*>(other->GetOwner());
		if (fl == nullptr)
			return;
		else
			Destroy(this);
	}
	void sbNormalBullet::TruckCollisionEnter(Collider* other)
	{
		Truck* tk = dynamic_cast<Truck*>(other->GetOwner());
		if (tk == nullptr
			|| tk->GetTruckState() != Truck::eState::Create)
			return;
		else
			Destroy(this);
	}

	void sbNormalBullet::BerserkerCollisionEnter(Collider* other)
	{
		Berserker* berserker = dynamic_cast<Berserker*>(other->GetOwner());
		if (berserker == nullptr
			|| berserker->GetBerserkerState() == Berserker::eState::Death)
			return;
		else
			Destroy(this);
	}

	void sbNormalBullet::HOldManEnter(Collider* other)
	{
		HOldMan* holdman = dynamic_cast<HOldMan*>(other->GetOwner());
		if (holdman == nullptr
			|| !(holdman->GetHOldManState() == HOldMan::eState::Idle))
			return;
		else
			Destroy(this);
	}
	void sbNormalBullet::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"NormalBullet",
			L"..\\Resource\\effect\\DS DSi - Metal Slug 7 Metal Slug XX - Weapon SFXNormal.bmp");
		Texture* images = Resources::Load<Texture>(L"NormalBulletY",
			L"..\\Resource\\effect\\DS DSi - Metal Slug 7 Metal Slug XX - Weapon SFXNormalUp.bmp");
		SpriteRenderer* sr = this->AddComponent<SpriteRenderer>();
		Collider* col = this->AddComponent<Collider>();
		Transform* tr = this->AddComponent<Transform>();
		if (mState == eBulletState::Up
			|| mState == eBulletState::Down)
		{
			sr->SetImage(images);
			col->SetSize(Vector2(20.0f, 30.0f));
		}
		else
		{
			sr->SetImage(image);
			col->SetSize(Vector2(30.0f, 20.0f));
		}
		sr->SetScale(Vector2(3.5f, 2.5f));
	}
}