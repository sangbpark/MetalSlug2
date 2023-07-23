#include "sbPlayerBottom.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimator.h"

namespace sb
{
	math::Vector2 PlayerBottom::mPlayposition = {};

	PlayerBottom::PlayerBottom()
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
			//animator->PlayAnimation(L"PlayerDownMove", true);
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftBAX", true);
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
	void PlayerBottom::Move()
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
				animator->PlayAnimation(L"PlayerIdlerightBAX", true);
				mState = eState::Idle;
			}
			else
			{
				Animator* animator = GetComponent<Animator>();
				animator->PlayAnimation(L"PlayerIdleleftBAX", true);
				mState = eState::Idle;
			}
		}

	}

	void PlayerBottom::Dead()
	{
	}
	void PlayerBottom::Attack()
	{
	}
	void PlayerBottom::Bomb()
	{
	}
}