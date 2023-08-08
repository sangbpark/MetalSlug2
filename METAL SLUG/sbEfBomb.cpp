#include "sbEfBomb.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbRigidbody.h"
#include "sbFloor.h"
#include "sbArabian.h"

namespace sb
{
	EfBomb::EfBomb()
		:mDeathTime(3.0f)
		,mState(BombState::first)
		,mCount(0)
		,mEfBomb1Speed(900.0f)
	{
		Texture* image = Resources::Load<Texture>(L"PlayerBomb", 
			L"..\\Resource\\effect\\Bomb.bmp");
		Texture* images = Resources::Load<Texture>(L"PlayerBombDeath",
			L"..\\Resource\\effect\\Bombexplosion.bmp");
		Animator* ar = this->AddComponent<Animator>();
		ar->CreateAnimation(L"RightBombAX", image, Vector2(0.0f, 0.0f), Vector2(22.0f, 22.0f), 32);
		ar->CreateAnimation(L"LeftBombAX", image, Vector2(0.0f, 22.0f), Vector2(22.0f, 22.0f), 32);
		ar->CreateAnimation(L"BombDeathAX", images, Vector2(0.0f, 0.0f), Vector2(88.0f, 122.0f), 20, Vector2(0.0f, -100.0f), 0.05f);
		ar->SetScale(Vector2::One);
		ar->SetScale(Vector2(2.5f, 2.5f));
		Rigidbody* rb = this->AddComponent<Rigidbody>();
		Collider* col = this->AddComponent<Collider>();
		Transform* tr = this->AddComponent<Transform>();
		col->SetSize(Vector2(50.0f, 50.0f));
	}
	EfBomb::~EfBomb()
	{
	}
	void EfBomb::Initialize()
	{
	}
	void EfBomb::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::EfBomb::BombState::first:
			First();
			break;
		case sb::EfBomb::BombState::move:
			Move();
			break;
		case sb::EfBomb::BombState::second:
			Second();
			break;
		case sb::EfBomb::BombState::secondMove:
			SecondMove();
			break;
		case sb::EfBomb::BombState::death:
			Death();
			break;

		default:
			break;
		}

		mDeathTime -= Time::DeltaTime();
		if (mDeathTime < 0.0f)
		{
			Death();
		}
	
	}
	void EfBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void EfBomb::OnCollisionEnter(Collider* other)
	{
		if (!(mState == BombState::death))
		{
			FloorCollisionEnter(other);
			ArabianCollisionEnter(other);
		}
	}
	void EfBomb::OnCollisionStay(Collider* other)
	{
	}
	void EfBomb::OnCollisionExit(Collider* other)
	{
	}
	void EfBomb::First()
	{
		Animator* ar = GetComponent<Animator>();
		if (mBombDirect)
			ar->PlayAnimation(L"RightBombAX");
		else
			ar->PlayAnimation(L"LeftBombAX");
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();
		velocity.y = EfBomb1_Jump;
		rb->SetGravity(Vector2(0.0f, 1500.0f));
		rb->SetVelocity(velocity);
		rb->SetGround(false);
		mState = BombState::move;
	}
	void EfBomb::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (mBombDirect)
		{
			pos.x += mEfBomb1Speed * Time::DeltaTime();
		}
		else
		{
			pos.x -= mEfBomb1Speed * Time::DeltaTime();
		}
		tr->SetPosition(pos);
		mEfBomb1Speed -= 700.0f * Time::DeltaTime();
	}
	void EfBomb::Second()
	{
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();
		velocity.y = EfBomb2_Jump;
		rb->SetVelocity(velocity);
		rb->SetGround(false);
		mState = BombState::secondMove;
	}
	void EfBomb::SecondMove()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (mBombDirect)
		{
			pos.x += EfBomb2_Speed * Time::DeltaTime();
		}
		else
		{
			pos.x -= EfBomb2_Speed * Time::DeltaTime();
		}
		tr->SetPosition(pos);
	}
	void EfBomb::Death()
	{
		Animator* ar = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGround(true);
		if (ar->Getcomplete())
		{
			Destroy(this);
		}
	}
	void EfBomb::FloorCollisionEnter(Collider* other)
	{
		Floor* fl = dynamic_cast<Floor*>(other->GetOwner());
		if (fl == nullptr)
			return;
		if (!(fl == nullptr)
			&& mCount == 1)
		{
			Animator* ar = GetComponent<Animator>();
			ar->PlayAnimation(L"BombDeathAX");
			mState = BombState::death;
			return;
		}
		if (!(fl == nullptr))
		{
			mState = BombState::second;
			mCount = 1;
		}
	}
	void EfBomb::ArabianCollisionEnter(Collider* other)
	{
		Arabian* arabian = dynamic_cast<Arabian*>(other->GetOwner());
		if (arabian == nullptr)
			return;
		else
		{
			Animator* ar = GetComponent<Animator>();
			Rigidbody* rb = GetComponent<Rigidbody>();
			ar->PlayAnimation(L"BombDeathAX");
			mState = BombState::death;
		}
		
	}
}