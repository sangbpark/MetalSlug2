#include "sbPlayerBottom.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimator.h"
#include "sbRigidbody.h"


namespace sb
{
	math::Vector2 PlayerBottom::mPlayposition = {};
<<<<<<< HEAD
	bool PlayerBottom::mGround = {};
	bool state = false;
	PlayerBottom::PlayerBottom()
		:mDirect(true)

=======


	PlayerBottom::PlayerBottom()
		:mDirect(true)
		
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
		case sb::PlayerBottom::eState::Down:
			Down();
			break;
		case sb::PlayerBottom::eState::attack:
			Attack();
			break;
		case sb::PlayerBottom::eState::bomb:
			Bomb();
			break;
=======
		case sb::PlayerBottom::eState::attack:
			Attack();
			break;
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
		Rigidbody* rb = GetComponent<Rigidbody>();
		mGround = rb->GetGround();
		mPlayposition = pos;

	}
	void PlayerBottom::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PlayerBottom::OnCollisionEnter(Collider* other)
	{
<<<<<<< HEAD

=======
	
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownBAX");
				mState = eState::Down;
=======
			if(mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownBAX");
				mState = eState::Move;
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownBAX");
<<<<<<< HEAD
				mState = eState::Down;
=======
				mState = eState::Move;
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD

=======
			
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
=======

>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD

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

	void PlayerBottom::Death()
	{
	}
	void PlayerBottom::Attack()
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
	void PlayerBottom::Bomb()
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
			else if(!mDirect)
			{
				animator->PlayAnimation(L"PlayerleftdownidleBAX", true);
				mState = eState::Down;
				state = false;
			}
		}

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
=======
		if (Input::GetKey(eKeyCode::DOWN))
		{

>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 1000.0f * Time::DeltaTime();

		}
<<<<<<< HEAD
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightdownwalkBAX", true);
			mDirect = true;
		}
=======
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 1000.0f * Time::DeltaTime();
		}
<<<<<<< HEAD
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownbombBAX");
				mState = eState::bomb;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownbombBAX");
				mState = eState::bomb;			
			}
		}
		tr->SetPosition(pos);
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdowngunBAX");
				mState = eState::attack;

			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdowngunBAX");
				mState = eState::attack;
			}

		}
		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::A))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownidleBAX",true);
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownidleBAX",true);
			}
		}

		if (Input::GetKeyUp(eKeyCode::DOWN))
=======

		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::UP)
			|| Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::DOWN)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
=======

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
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
}