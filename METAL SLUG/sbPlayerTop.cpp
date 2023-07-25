#include "sbPlayerTop.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimation.h"
#include "sbAnimator.h"
#include "sbPlayerBottom.h"
#include "sbRigidbody.h"


namespace sb
{
	math::Vector2 PlayerTop::mPlayposition = {};

	PlayerTop::PlayerTop()
		:mDirect(true)
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

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = PlayerBottom::GetPlayerPosition();
		pos.y = pos.y - 30.0f;
		switch (mState)
		{
		case sb::PlayerTop::eState::Idle:
			Idle();
			break;
		case sb::PlayerTop::eState::Move:
			Move();
			break;
		case sb::PlayerTop::eState::attack:
			Attack();
			break;
		case sb::PlayerTop::eState::jump:
			Jump();
			break;
		case sb::PlayerTop::eState::Death:
			Death();
			break;
		case sb::PlayerTop::eState::bomb:
			Bomb();
			break;
		case sb::PlayerTop::eState::End:
			break;
		default:
			break;
		}

		tr->SetPosition(pos);
	
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
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownTAX");
				mState = eState::Move;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownTAX");
				mState = eState::Move;
			}
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftTAX", true);
			mState = eState::Move;
			mDirect = false;
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightknifeTAX", true);
				mState = eState::attack;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftknifeTAX", true);
				mState = eState::attack;
			}
		}
		if (Input::GetKey(eKeyCode::Z))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightgunTAX", true);
				mState = eState::attack;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftgunTAX", true);
				mState = eState::attack;
			}
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightjumpTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftjumpTAX");
				mState = eState::jump;
			}
		
		}
		if (Input::GetKey(eKeyCode::D))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightbombTAX", true);
				mState = eState::bomb;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftbombTAX", true);
				mState = eState::bomb;
			}
		}
	}
	void PlayerTop::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::UP))
		{
		
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			/*pos.x -= 1000.0f * Time::DeltaTime();*/

		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			//pos.x += 1000.0f * Time::DeltaTime();
			
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

	void PlayerTop::Death()
	{
	}
	void PlayerTop::Attack()
	{

		if (Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::Z))
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
	void PlayerTop::Bomb()
	{
		if (Input::GetKeyUp(eKeyCode::D))
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
	void PlayerTop::Jump()
	{

		Animator* animator = GetComponent<Animator>();
	

		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}
}