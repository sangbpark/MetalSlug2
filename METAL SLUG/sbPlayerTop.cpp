#include "sbPlayerTop.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimator.h"

namespace sb
{
	math::Vector2 PlayerTop::mPlayposition = {};

	PlayerTop::PlayerTop()
	{
	}
	PlayerTop::~PlayerTop()
	{
	}
	void PlayerTop::Initialize()
	{
	}
	void PlayerTop::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case sb::PlayerTop::eState::Idle:
			Idle();
			break;
		case sb::PlayerTop::eState::Move:
			Move();
			break;
		case sb::PlayerTop::eState::End:
			break;
		default:
			break;
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayposition = pos;
	}
	void PlayerTop::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PlayerTop::OnCollisionEnter(Collider* other)
	{
	}
	void PlayerTop::OnCollisionStay(Collider* other)
	{
	}
	void PlayerTop::OnCollisionExit(Collider* other)
	{
	}
	void PlayerTop::Idle()
	{
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::UP))
		{
			//animator->PlayAnimation(L"PlayerUpMove", true);
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightTAX", true);
			mState = eState::Move;
			mDirect = true;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			//animator->PlayAnimation(L"PlayerDownMove", true);
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftTAX", true);
			mState = eState::Move;
			mDirect = false;
		}

		if (Input::GetKey(eKeyCode::C))
		{
			//animator->PlayAnimation(L"PlayerDropWater", false);
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::X))
		{
			//animator->PlayAnimation(L"PlayerDropWater", false);
			mState = eState::attack;
		}
		if (Input::GetKey(eKeyCode::Z))
		{
			//animator->PlayAnimation(L"PlayerDropWater", false);
			mState = eState::bomb;
		}
	}
	void PlayerTop::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::UP))
		{
		
			pos.y -= 1000.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 1000.0f * Time::DeltaTime();
			
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y += 1000.0f * Time::DeltaTime();
			
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
				Animator* animator = GetComponent<Animator>();
				animator->PlayAnimation(L"PlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				Animator* animator = GetComponent<Animator>();
				animator->PlayAnimation(L"PlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}

	}

	void PlayerTop::Dead()
	{
	}
	void PlayerTop::Attack()
	{
	}
	void PlayerTop::Bomb()
	{
	}
}