#include "sbCamel.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbRigidbody.h"
#include "sbPlayerBottom.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbCamelGun.h"
#include "sbCamelBullet.h"

namespace sb
{
	Camel::Camel()
		:mState(eCamelState::Ready)
		, mRideOn(false)
		, mRotate(0.0f)
		, mBulletTime(0.0f)
		, mRideTime(0.0f)
		, mDeathTime(0.0f)
		, mFire(false)
	{
		ResourceLoad();
	}
	Camel::~Camel()
	{
	}
	void Camel::Initialize()
	{
	}
	void Camel::Update()
	{
		GameObject::Update();
		mBulletTime -= Time::DeltaTime();
		if (mBulletTime <= 0.0f)
			mBulletTime = 0.0f;
		mRideTime -= Time::DeltaTime();
		if (mRideTime <= 0.0f)
			mRideTime = 0.0f;
		mDeathTime -= Time::DeltaTime();
		if (mDeathTime <= 0.0f)
			mDeathTime = 0.0f;
		switch (mState)
		{
		case sb::Camel::eCamelState::Ready:
			Ready();
			break;
		case sb::Camel::eCamelState::Idle:
			Idle();
			break;
		case sb::Camel::eCamelState::Move:
			Move();
			break;
		case sb::Camel::eCamelState::Death:
			Death();
			break;
		case sb::Camel::eCamelState::Jump:
			Jump();
			break;
		default:
			break;
		}
	}
	void Camel::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Camel::Ready()
	{
	}
	void Camel::Idle()
	{
		if (Input::GetKey(eKeyCode::DOWN)
			&& Input::GetKeyDown(eKeyCode::S))
		{
			PlayerBottom* pb = dynamic_cast<PlayerBottom*>(mOwner);
			mRideOn = false;
			pb->SetPlayerRide(mRideOn);
			pb->RideOff();
			pb->SetInvincible(1.0f);
			mRideTime = 2.0f;
			mRotate = 0.0f;
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"CamelReadyAX");
			mState = eCamelState::Ready;
			return;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"CamelmoveAX", true);
			mState = eCamelState::Move;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"CamelmoveAX", true);
			mState = eCamelState::Move;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			mRotate -= 300.0f * Time::DeltaTime();
			if (mRotate <= -180.0f)
				mRotate = 180.0f;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			mRotate += 300.0f * Time::DeltaTime();
			if (mRotate >= 180.0f)
				mRotate = -180.0f;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			if(mBulletTime <= 0.0f)
			{
				if(mFire==false)
					mFire = true;

				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				Vector2 pos2 = pos + Vector2(20.0f, 0.0f);
				pos = Rotate(pos2, mRotate) * 20.0f;
				CreatHeavyBullet(-mRotate, pos);
				mBulletTime = 0.1f;
			}
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"CamelmoveAX", true);;
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			mState = eCamelState::Jump;
			return;
		}
	}
	void Camel::Move()
	{
		PlayerBottom* pb = dynamic_cast<PlayerBottom*>(mOwner);
		Transform* pbtr = pb->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = pbtr->GetPosition();
		pos.y = tr->GetPosition().y;
		tr->SetPosition(pos);
		if (Input::GetKey(eKeyCode::DOWN)
			&& Input::GetKeyDown(eKeyCode::S))
		{
			PlayerBottom* pb = dynamic_cast<PlayerBottom*>(mOwner);
			mRideOn = false;
			pb->SetPlayerRide(mRideOn);
			pb->RideOff();
			pb->SetInvincible(1.0f);
			mRideTime = 2.0f;
			mRotate = 0.0f;
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"CamelReadyAX");
			mState = eCamelState::Ready;
			return;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			mRotate -= 100.0f * Time::DeltaTime();
			if (mRotate <= -180.0f)
				mRotate = 180.0f;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			mRotate += 100.0f * Time::DeltaTime();
			if (mRotate >= 180.0f)
				mRotate = -180.0f;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			if (mBulletTime <= 0.0f)
			{
				if (mBulletTime <= 0.0f)
				{
					if (mFire == false)
						mFire = true;

					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPosition();
					Vector2 pos2 = pos + Vector2(20.0f, 0.0f);
					pos = Rotate(pos2, mRotate);
					CreatHeavyBullet(-mRotate, pos);
					mBulletTime = 0.1f;
				}
			}
		}
		if (Input::GetKey(eKeyCode::S))
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"CamelmoveAX", true);;
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			mState = eCamelState::Jump;
			return;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::LEFT))
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"CamelIdleAX", true);
			mState = eCamelState::Idle;
			return;
		}
	}
	void Camel::Death()
	{
	}
	void Camel::Jump()
	{
		PlayerBottom* pb = dynamic_cast<PlayerBottom*>(mOwner);
		Transform* pbtr = pb->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 pos = pbtr->GetPosition();
		pos.y = tr->GetPosition().y;
		tr->SetPosition(pos);
		if (Input::GetKey(eKeyCode::UP))
		{
			mRotate -= 100.0f * Time::DeltaTime();
			if (mRotate <= -180.0f)
				mRotate = 180.0f;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			mRotate += 100.0f * Time::DeltaTime();
			if (mRotate >= 180.0f)
				mRotate = -180.0f;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			if (mBulletTime <= 0.0f)
			{
				Vector2 pos = Vector2(0.0f, 0.0f);
				if (mRotate == 0.0f)
				{
					pos = Vector2(0.0f, -20.0f);
				}
				else if (mRotate < 0.0f
					&& mRotate >-20.0f)
				{
					pos = Vector2(-20.0f, -10.0f);
				}
				else if (mRotate <= -20.0f)
				{
					pos = Vector2(-20.0f, 0.0f);
				}
				else if (mRotate >= 180.0f
					&& mRotate <= 200.0f)
				{
					pos = Vector2(0.0f, 30.0f);
				}
				else
				{
					pos = Vector2(30.0f, 0.0f);
				}
				CreatHeavyBullet(-mRotate, pos);
				mBulletTime = 0.1f;
			}
		}
		if (rb->GetGround())
		{
			Rigidbody* pbrb = pb->GetComponent<Rigidbody>();
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"CamelIdleAX", true);
			pbrb->SetGround(true);
			mState = eCamelState::Idle;
		}
	}
	void Camel::PlayerCollisionEnter(Collider* other)
	{
		PlayerBottom* pb = dynamic_cast<PlayerBottom*>(other->GetOwner());
		if (pb == nullptr)
			return;
		else
		{
			float leny = other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y;
			float lenx = fabs(other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
			float Enterx = this->GetComponent<Collider>()->GetSize().x /2.0f;

			if (leny < -40.0f
				&& lenx < Enterx)
			{
				pb->SetInvincible(1.0f);
				Transform* pbtr = pb->GetComponent<Transform>();
				Transform* tr = this->GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 90.0f;
				pos.x -= 15.0f;
				pbtr->SetPosition(pos);
				mRideOn = true;
				pb->SetPlayerRide(mRideOn);
				pb->RideOn();
				Animator* at = GetComponent<Animator>();
				at->PlayAnimation(L"CamelIdleAX",true);
				mState = eCamelState::Idle;
				mOwner = pb;
				pb->SetVehicle(this);
			}

		}
	}
	void Camel::PlayerStateCheck(Collider* other)
	{
		PlayerBottom* pb = dynamic_cast<PlayerBottom*>(mOwner);
		if (pb->GetState() == PlayerBottom::eState::Death
			|| pb->GetState() == PlayerBottom::eState::RideVictory)
		{
			Animator* at = GetComponent<Animator>();
			mRideOn = false;
			mRideTime = 0.0f;
			mDeathTime = 2.0f;
			at->PlayAnimation(L"CamelReadyAX");
			mState = eCamelState::Ready;
		}
	}
	void Camel::OnCollisionEnter(Collider* other)
	{
		if (!mRideOn
			&& mRideTime == 0.0f
			&& mDeathTime == 0.0f)
			PlayerCollisionEnter(other);
	}
	void Camel::OnCollisionStay(Collider* other)
	{
		if (!mRideOn
			&& mRideTime == 0.0f
			&& mDeathTime == 0.0f)
			PlayerCollisionEnter(other);
		else
			PlayerStateCheck(other);
	}
	void Camel::OnCollisionExit(Collider* other)
	{
	}
	void Camel::CreatHeavyBullet(float Rotation, math::Vector2 offset, bool Down)
	{
		Transform* tr = mGun->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos += offset;
		pos = BulletRotate2(pos, Rotation,30.0f);	
		CamelBullet* camelbullet = object::Instantiate<CamelBullet>(eLayerType::Effects, pos);
		camelbullet->SetDegree(Rotation);

	}
	void Camel::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"Camel"
			, L"..\\Resource\\Vehicle\\Camel.bmp");
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		Rigidbody* rb = AddComponent<Rigidbody>();
		at->CreateAnimation(L"CamelIdleAX", image, Vector2(0.0f, 88.0f), Vector2(88.0f, 88.0f), 3, Vector2(0.0f, -100.0f));
		at->CreateAnimation(L"CamelmoveAX", image, Vector2(0.0f, 176.0f), Vector2(88.0f, 88.0f), 11, Vector2(0.0f, -100.0f));
		at->CreateAnimation(L"CamelReadyAX", image, Vector2(0.0f, 0.0f), Vector2(88.0f, 88.0f), 1, Vector2(0.0f, -100.0f));
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"CamelReadyAX");
		col->SetSize(Vector2(250.0f, 200.0f));
		col->SetPosition(Vector2(10000.0f, 1000.0f));
		CamelGun* camelgun = object::Instantiate<CamelGun>(eLayerType::Npc, tr->GetPosition());
		mGun = camelgun;
		camelgun->SetOwner(this);
	}
}
