#include "sbTruck.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbRigidbody.h"
#include "sbNormalBullet.h"
#include "sbEfBomb.h"
#include "sbPlayerBottom.h"
#include "sbHeavyBullet.h"
#include "sbBerserker.h"
#include "sbHeavyMachineGun.h"

namespace sb
{
	Truck::Truck()
		: mHp(20.0f)
		, mState(eState::Idle)
		, mCreateBerserkerTime(0.0f)
		, mBerserkerCount(0)
		, mHit (false)
	{
		ResourceLoad();
	}
	Truck::~Truck()
	{
	}
	void Truck::Initialize()
	{
	}
	void Truck::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::Truck::eState::Idle:
			Idle();
			break;
		case sb::Truck::eState::Drive:
			Drive();
			break;
		case sb::Truck::eState::Drop:
			Drop();
			break;
		case sb::Truck::eState::Destroy:
			Destroy();
			break;
		case sb::Truck::eState::Death:
			Death();
			break;
		case sb::Truck::eState::Create:
			Create();
			break;
		case sb::Truck::eState::End:
			break;
		default:
			break;
		}

		Hit();
	}
	void Truck::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Truck::OnCollisionEnter(Collider* other)
	{
		if(mState == eState::Create)
		{
			NormalBulletCollsionEnter(other);
			HeavyBulletCollsionEnter(other);
			EfBombCollsionEnter(other);

			if (mHp <= 0.0f)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				Animator* at = GetComponent<Animator>();
				at->PlayAnimation(L"TruckdestroyAX",true);
				HeavyMachineGun* hmg = object::Instantiate<HeavyMachineGun>(eLayerType::Effects, pos);
				mState = eState::Destroy;
				Sound* sound = Resources::Load<Sound>(L"truckdestory"
					, L"..\\Resource\\sound\\truckDestroy.wav");
				sound->Play(false);
				sound->SetVolume(50.0f);
			}
		}
	}
	void Truck::OnCollisionStay(Collider* other)
	{
	}
	void Truck::OnCollisionExit(Collider* other)
	{
	}
	void Truck::Idle()
	{
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"TruckmoveAX",true);
		mState = eState::Drive;

	}
	void Truck::Drive()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x -= 150.0f * Time::DeltaTime();
		if (pos.x <= 7200.0f)
		{
			mMoveSound->Stop(true);
			Sound* sound = Resources::Load<Sound>(L"truckstop"
				, L"..\\Resource\\sound\\TruckStop.wav");
			sound->Play(false);
			sound->SetVolume(50.0f);
			Animator* at = GetComponent<Animator>();
			pos.x = 7200.0f;
			mState = eState::Drop;
			at->PlayAnimation(L"TruckdropAX");
		}
		tr->SetPosition(pos);

	}
	void Truck::Drop()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			mCreateBerserkerTime = 3.0f;
			mState = eState::Create;
		}
	}
	void Truck::Destroy()
	{
	}
	void Truck::Death()
	{
	}
	void Truck::Create()
	{
		mCreateBerserkerTime += Time::DeltaTime();
		if (mCreateBerserkerTime >= 3.0f)
		{
			mBerserkerCount++;
			CreateBerserker();
			mCreateBerserkerTime = 2.5f;
		}

		if (mBerserkerCount == 3)
		{
			mCreateBerserkerTime = 0.0f;
			mBerserkerCount = 0;
		}
	}
	void Truck::Hit()
	{
		if (mHit)
		{
			Animator* at = GetComponent<Animator>();
			float alpha = at->GetAlpha();
			alpha = 0.8f;
			at->SetAlpha(alpha);
			mHit = false;
		}
		else
		{
			Animator* at = GetComponent<Animator>();
			float alpha = at->GetAlpha();
			alpha = 1.0f;
			at->SetAlpha(alpha);
		}

	}
	void Truck::CreateBerserker()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x -= 180.0f;
		Berserker* berserker = object::Instantiate<Berserker>(eLayerType::Effects, pos);
	}

	void Truck::NormalBulletCollsionEnter(Collider* other)
	{
		sbNormalBullet* normalbullet = dynamic_cast<sbNormalBullet*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (normalbullet == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 1.0f;
		}

	}
	void Truck::HeavyBulletCollsionEnter(Collider* other)
	{
		HeavyBullet* heavybullet = dynamic_cast<HeavyBullet*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (heavybullet == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 0.7f;
		}
	}
	void Truck::EfBombCollsionEnter(Collider* other)
	{
		EfBomb* efbomb = dynamic_cast<EfBomb*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (efbomb == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 5.0f;
		}

	}
	void Truck::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"tuck"
			, L"..\\Resource\\Monster\\mission1truck.bmp");
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		Rigidbody* rb = AddComponent<Rigidbody>();
		at->CreateAnimation(L"TruckIdleAX", image, Vector2(0.0f, 0.0f), Vector2(176.0f, 88.0f), 1, Vector2(-100.0f, -25.0f));
		at->CreateAnimation(L"TruckmoveAX", image, Vector2(0.0f, 88.0f), Vector2(176.0f, 88.0f), 4, Vector2(-100.0f, -25.0f));
		at->CreateAnimation(L"TruckdropAX", image, Vector2(0.0f, 176.0f), Vector2(176.0f, 88.0f), 12, Vector2(-100.0f, -25.0f));
		at->CreateAnimation(L"TruckdestroyAX", image, Vector2(0.0f, 264.0f), Vector2(176.0f, 88.0f), 6, Vector2(-100.0f, -25.0f));
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"TruckIdleAX");
		col->SetSize(Vector2(500.0f, 350.0f));
		Sound* sound = Resources::Load<Sound>(L"truckmove"
			, L"..\\Resource\\sound\\TruckMove.wav");
		sound->Play(true);
		sound->SetVolume(50.0f);
		mMoveSound = sound;
	}
}