#include "sbPlayerBottom.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimator.h"
#include "sbRigidbody.h"


namespace sb
{
	math::Vector2 PlayerBottom::mPlayposition = {};


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

		switch (mState)
		{
		case sb::PlayerBottom::eState::Idle:
			Idle();
			break;
		case sb::PlayerBottom::eState::Move:
			Move();
			break;
		case sb::PlayerBottom::eState::attack:
			Attack();
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

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
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
			if(mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownBAX");
				mState = eState::Move;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownBAX");
				mState = eState::Move;
			}
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftBAX", true);
			mState = eState::Move;
			mDirect = false;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			
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
		if (Input::GetKey(eKeyCode::DOWN))
		{

		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 1000.0f * Time::DeltaTime();

		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 1000.0f * Time::DeltaTime();

		}

		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::UP)
			|| Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::DOWN)
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

	}

	void PlayerBottom::Death()
	{
	}
	void PlayerBottom::Attack()
	{
	}
	void PlayerBottom::Bomb()
	{
	}
	void PlayerBottom::Jump()
	{
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 velocity = rb->GetVelocity();
		velocity.y = -300.0f;
		rb->SetVelocity(velocity);
		rb->SetGround(false);
		if (animator->Getcomplete())
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
}