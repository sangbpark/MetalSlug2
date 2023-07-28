#include "sbPlayerBottom.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimator.h"
#include "sbRigidbody.h"
#include "sbPlayerTop.h"
#include "sbTexture.h"
#include "sbResources.h"

namespace sb
{
	math::Vector2 PlayerBottom::mPlayposition = {};
	bool PlayerBottom::mGround = {};
	bool state = false;

	PlayerBottom::PlayerBottom()
		:mDirect(true)	
	{
	}
	PlayerBottom::~PlayerBottom()
	{
	}
	void PlayerBottom::Initialize()
	{
	}
	void PlayerBottom::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		///pixel Ãæµ¹
	/*	COLORREF rgb = mFloorTexture->GetTexturePixel(tr->GetPosition().x, tr->GetPosition().y - 200 );*/

		Rigidbody* rb = GetComponent<Rigidbody>();
		//if (rgb == RGB(0, 0, 255))
		//{
		//	Transform* tr = GetComponent<Transform>();

		//	Vector2 pos = tr->GetPosition();
		//	pos.y -= 1;
		//	tr->SetPosition(pos);

		//	rb->SetGround(true);
		//}
		//else
		//{
		//	rb->SetGround(false);
		//}

		switch (mState)
		{
		case sb::PlayerBottom::eState::Idle:
			Idle();
			break;
		case sb::PlayerBottom::eState::Move:
			Move();
			break;
		case sb::PlayerBottom::eState::Down:
			Down();
			break;
		case sb::PlayerBottom::eState::attack:
			Attack();
			break;
		case sb::PlayerBottom::eState::Downattack:
			DownAttack();
			break;
		case sb::PlayerBottom::eState::DownBomb:
			DownBomb();
			break;
		case sb::PlayerBottom::eState::bomb:
			Bomb();
			break;
		case sb::PlayerBottom::eState::jump:
			Jump();
			break;
		case sb::PlayerBottom::eState::Death:
			Death();
			break;
		case sb::PlayerBottom::eState::End:
			break;
		default:
			break;
		}

	
		Vector2 pos = tr->GetPosition();
		mGround = rb->GetGround();
		mPlayposition = pos;

	}
	void PlayerBottom::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PlayerBottom::OnCollisionEnter(Collider* other)
	{

	}
	void PlayerBottom::OnCollisionStay(Collider* other)
	{
	}
	void PlayerBottom::OnCollisionExit(Collider* other)
	{
	}
	void PlayerBottom::Idle()
	{
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::UP))
		{
			//animator->PlayAnimation(L"PlayerUpMove", true);
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightBAX", true);
			mState = eState::Move;
			mDirect = true;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{

			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownBAX");
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownBAX");
				mState = eState::Down;
			}
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftBAX", true);				
			mState = eState::Move;
			mDirect = false;	
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightjumpBAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftjumpBAX");
				mState = eState::jump;
			}

			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
		}

	}
	void PlayerBottom::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::UP))
		{

		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 1000.0f * Time::DeltaTime();
			mDirect = false;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 1000.0f * Time::DeltaTime();
			mDirect = true;
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
	
		}

		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightBAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftBAX", true);
				mState = eState::Idle;
			}
		}
		else if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightrunjumpBAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftrunjumpBAX");
				mState = eState::jump;
			}
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
		}
	}

	void PlayerBottom::Attack()
	{

	}
	void PlayerBottom::Bomb()
	{	
		


	}
	void PlayerBottom::Jump()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 1000.0f * Time::DeltaTime();
			mDirect = false;

		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 1000.0f * Time::DeltaTime();
			mDirect = true;

		}
		tr->SetPosition(pos);

		if (rb->GetGround())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightBAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftBAX", true);
				mState = eState::Idle;

			}
		}
	}
	void PlayerBottom::Down()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftdownwalkBAX", true);
			mDirect = false;
		}
		
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 1000.0f * Time::DeltaTime();

		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightdownwalkBAX", true);
			mDirect = true;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 1000.0f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownbombBAX");
				mState = eState::DownBomb;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownbombBAX");
				mState = eState::DownBomb;
			}
		}
		tr->SetPosition(pos);
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdowngunBAX");
				mState = eState::Downattack;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdowngunBAX");
				mState = eState::Downattack;
			}
		
		}
		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::A))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownidleBAX", true);
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownidleBAX", true);
			}
		}

		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightBAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftBAX", true);
				mState = eState::Idle;
			}
		}

		tr->SetPosition(pos);

	}
	void PlayerBottom::DownAttack()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			state = true;
		}
		if (state && animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightBAX", true);
				mState = eState::Idle;
				state = false;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftBAX", true);
				mState = eState::Idle;
				state = false;
			}
		}
		else if (!state && animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownidleBAX", true);
				mState = eState::Down;
				state = false;
			}
			else if (!mDirect)
			{
				animator->PlayAnimation(L"PlayerleftdownidleBAX", true);
				mState = eState::Down;
				state = false;
			}
		}
	}
	void PlayerBottom::DownBomb()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			state = true;
		}
		if (state && animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightBAX", true);
				mState = eState::Idle;
				state = false;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftBAX", true);
				mState = eState::Idle;
				state = false;
			}
		}
		else if (!state && animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownidleBAX", true);
				mState = eState::Down;
				state = false;
			}
			else if (!mDirect)
			{
				animator->PlayAnimation(L"PlayerleftdownidleBAX", true);
				mState = eState::Down;
				state = false;
			}
		}
	}
	void PlayerBottom::Death()
	{
	}
	
}
