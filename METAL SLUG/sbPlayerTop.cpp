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
	bool tstate = false;

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
<<<<<<< HEAD
		case sb::PlayerTop::eState::Down:
			Down();
			break;
=======
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
		case sb::PlayerTop::eState::stay:
			Stay();
			break;
=======
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		case sb::PlayerTop::eState::End:
			break;
		default:
			break;
		}

		tr->SetPosition(pos);
<<<<<<< HEAD

=======
	
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
				mState = eState::Down;
=======
				mState = eState::Move;
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownTAX");
<<<<<<< HEAD
				mState = eState::Down;
=======
				mState = eState::Move;
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
			}
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftTAX", true);
			mState = eState::Move;
			mDirect = false;
		}

<<<<<<< HEAD
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightknifeTAX");
=======
		if (Input::GetKey(eKeyCode::A))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightknifeTAX", true);
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
				mState = eState::attack;
			}
			else
			{
<<<<<<< HEAD
				animator->PlayAnimation(L"PlayerleftknifeTAX");
				mState = eState::attack;
			}
		}
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightgunTAX");
				mState = eState::attack;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftgunTAX");
=======
				animator->PlayAnimation(L"PlayerleftknifeTAX", true);
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
				mState = eState::attack;
			}
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirect)
			{
<<<<<<< HEAD
=======
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
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
				animator->PlayAnimation(L"PlayerrightjumpTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftjumpTAX");
				mState = eState::jump;
			}
<<<<<<< HEAD

=======
		
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::UP))
		{
<<<<<<< HEAD

		}
		if (Input::GetKey(eKeyCode::DOWN))
		{

		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			mDirect = false;

=======
		
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			/*pos.x -= 1000.0f * Time::DeltaTime();*/

		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
<<<<<<< HEAD
			mDirect = true;

=======
			//pos.x += 1000.0f * Time::DeltaTime();
			
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		}
		tr->SetPosition(pos);

		if (Input::GetKeyDown(eKeyCode::A))
		{
		
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightkniferunTAX");
				mState = eState::attack;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftkniferunTAX");
				mState = eState::attack;
			}
		}
		if (Input::GetKeyDown(eKeyCode::Z))
		{
	
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightgunrunTAX");
				mState = eState::attack;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftgunrunTAX");
				mState = eState::attack;
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

		if (Input::GetKeyUp(eKeyCode::UP)
			|| Input::GetKeyUp(eKeyCode::LEFT)
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
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightrunjumpTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftrunjumpTAX");
				mState = eState::jump;
			}

		}
	}

	void PlayerTop::Death()
	{
	}
	void PlayerTop::Attack()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->Getcomplete())
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
<<<<<<< HEAD
=======

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
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
		if (Input::GetKeyDown(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKeyDown(eKeyCode::LEFT))
			mDirect = false;

		if (PlayerBottom::Getground())
=======
	

		if (animator->Getcomplete())
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
	}
	void PlayerTop::Down()
	{

		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyDown(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKeyDown(eKeyCode::LEFT))
			mDirect = false;
		if (Input::GetKeyDown(eKeyCode::A))
		{
			animator->PlayAnimation(L"PlayerrightdowngunTAX");
			mState = eState::stay;
		}

		if (Input::GetKeyUp(eKeyCode::DOWN))
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
		if (Input::GetKeyDown(eKeyCode::D))
		{
			animator->PlayAnimation(L"PlayerleftdownbombTAX");
			mState = eState::stay;
		}
	}


	void PlayerTop::Stay()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			tstate = true;
		}
		if (tstate && animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightTAX", true);
				mState = eState::Idle;
				tstate = false;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftTAX", true);
				mState = eState::Idle;
				tstate = false;
			}
		}
		else if (!tstate && animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownidleTAX", true);
				mState = eState::Down;
				tstate = false;
			}
			else if (!mDirect)
			{
				animator->PlayAnimation(L"PlayerleftdownidleTAX", true);
				mState = eState::Down;
				tstate = false;
			}
		}
=======
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
	}
}