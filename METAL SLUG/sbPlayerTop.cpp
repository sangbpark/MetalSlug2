#include "sbPlayerTop.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimation.h"
#include "sbAnimator.h"
#include "sbPlayerBottom.h"
#include "sbRigidbody.h"
#include "sbNormalBullet.h"
#include "sbObject.h"
#include "sbCollider.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbEfBomb.h"



namespace sb
{
	math::Vector2 PlayerTop::mPlayposition = {};
	bool PlayerTop::mComplete = false;

	PlayerTop::PlayerTop()

		:mDirect(true)
		, mKeyUp(false)
		, mLateDirect(true)
	
	{
		ResourceLoad();
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
		case sb::PlayerTop::eState::Up:
			Up();
			break;
		case sb::PlayerTop::eState::Move:
			Move();
			break;
		case sb::PlayerTop::eState::Down:
			Down();
			break;
		case sb::PlayerTop::eState::attack:
			Attack();
			break;
		case sb::PlayerTop::eState::jump:
			Jump();
			break;
		case sb::PlayerTop::eState::jumpup:
			JumpUp();
			break;
		case sb::PlayerTop::eState::jumpdown:
			JumpDown();
			break;
		case sb::PlayerTop::eState::Jumpattack:
			JumpAttack();
			break;
		case sb::PlayerTop::eState::Upattack:
			UpAttack();
			break;
		case sb::PlayerTop::eState::jumpdownattack:
			JumpDownAttack();
			break;
		case sb::PlayerTop::eState::jumpupattack:
			JumpUpAttack();
			break;
		case sb::PlayerTop::eState::jumpbomb:
			JumpBomb();
			break;
		case sb::PlayerTop::eState::Death:
			Death();
			break;
		case sb::PlayerTop::eState::bomb:
			Bomb();
			break;
		case sb::PlayerTop::eState::stay:
			Stay();
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
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightUPTAX");
				mState = eState::Up;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftUPTAX");
				mState = eState::Up;
			}
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightTAX", true);
			mState = eState::Move;
			mDirect = true;
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownTAX");
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownTAX");
				mState = eState::Down;
			}
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftTAX", true);
			mState = eState::Move;
			mDirect = false;
		}

		//if (Input::GetKeyDown(eKeyCode::A))
		//{
		//	if (mDirect)
		//	{
		//		animator->PlayAnimation(L"PlayerrightknifeTAX");
		//		mState = eState::attack;
		//	}
		//	else
		//	{
		//		animator->PlayAnimation(L"PlayerleftknifeTAX");
		//		mState = eState::attack;
		//	}
		//}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects,pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Right);
				animator->PlayAnimation(L"PlayerrightgunTAX");
				mState = eState::attack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 40.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Left);
				animator->PlayAnimation(L"PlayerleftgunTAX");
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
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::bomb;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::bomb;
			}
		}
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
	void PlayerTop::Move()
	{
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightUPTAX");
				mState = eState::Up;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftUPTAX");
				mState = eState::Up;
			}
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownTAX");
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownTAX");
				mState = eState::Down;
			}
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			mDirect = false;

		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			mDirect = true;

		}
	
		//if (Input::GetKeyDown(eKeyCode::A))
		//{
		//
		//	if (mDirect)
		//	{
		//		animator->PlayAnimation(L"PlayerrightknifeTAX");
		//		mState = eState::attack;
		//	}
		//	else
		//	{
		//		animator->PlayAnimation(L"PlayerleftknifeTAX");
		//		mState = eState::attack;
		//	}
		//}
		if (Input::GetKeyDown(eKeyCode::A))
		{
	
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Right);
				animator->PlayAnimation(L"PlayerrightgunTAX");
				mState = eState::attack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 40.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Left);
				animator->PlayAnimation(L"PlayerleftgunTAX");
				mState = eState::attack;
			}
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::bomb;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::bomb;
			}
		}

		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
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
		mComplete = false;
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyDown(eKeyCode::A)
			&& animator->GetIndex() > 4)
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Right);
				animator->PlayAnimation(L"PlayerrightgunTAX");
				mState = eState::attack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 40.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Left);
				animator->PlayAnimation(L"PlayerleftgunTAX");
				mState = eState::attack;
			}
			mComplete = true;
		}

		if (mDirect)
		{
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				animator->PlayAnimation(L"PlayerleftTAX", true);
				mState = eState::Move;
				mDirect = false;

			}
			mComplete = true;
		}
		if (!mDirect)
		{
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				animator->PlayAnimation(L"PlayerrightTAX", true);
				mState = eState::Move;
				mDirect = true;

			}
			mComplete = true;
		}

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightUPTAX");
				mState = eState::Up;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftUPTAX");
				mState = eState::Up;
			}
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownTAX");
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownTAX");
				mState = eState::Down;
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
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::bomb;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::bomb;
			}
		}
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
			mComplete = true;
		}

	}
	void PlayerTop::Bomb()
	{
		Animator* animator = GetComponent<Animator>();

		if (mDirect)
		{
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				animator->PlayAnimation(L"PlayerleftTAX", true);
				mState = eState::Move;
				mDirect = false;

			}
			mComplete = true;
		}
		if (!mDirect)
		{
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				animator->PlayAnimation(L"PlayerrightTAX", true);
				mState = eState::Move;
				mDirect = true;

			}
			mComplete = true;
		}
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
	void PlayerTop::Jump()
	{

		Animator* animator = GetComponent<Animator>();
		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightTAX", true);
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftTAX", true);
				mState = eState::jump;
			}
		}
	
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Right);
				animator->PlayAnimation(L"PlayerrightgunTAX");
				mState = eState::Jumpattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 40.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Left);
				animator->PlayAnimation(L"PlayerleftgunTAX");
				mState = eState::Jumpattack;
			}

		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::jumpbomb;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::jumpbomb;
			}
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightUPTAX");
				mState = eState::jumpup;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftUPTAX");
				mState = eState::jumpup;
			}
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightjumpdownTAX");
				mState = eState::jumpdown;
			}
			else
			{
				animator->PlayAnimation(L"PlayerrightjumpdownTAX");
				mState = eState::jumpdown;
			}
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKeyDown(eKeyCode::LEFT))
			mDirect = false;


		if (PlayerBottom::Getground())
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
	void PlayerTop::Down()
	{

		Animator* animator = GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mDirect = false;
		if (Input::GetKeyDown(eKeyCode::A))
		{
			animator->PlayAnimation(L"PlayerrightdowngunTAX");
			mState = eState::stay;
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			animator->PlayAnimation(L"PlayerleftdownbombTAX");
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
	}
	void PlayerTop::Stay()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownTAX", true);
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownTAX", true);
				mState = eState::Down;
			}
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

	}
	void PlayerTop::Up()
	{
		mComplete = false;
		Animator* animator = GetComponent<Animator>();
		if (animator->Getcomplete())
		{
			if (mDirect)
			{			
				animator->PlayAnimation(L"PlayerrightUPidleTAX", true);
			
			}
			if (!mDirect)
			{
				animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
	
			}
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightUPidleTAX", true);
			mState = eState::Up;
			mDirect = true;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
			mState = eState::Up;
			mDirect = false;
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightUPdownTAX");
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftUPdownTAX");
				mState = eState::Idle;
			}
		}
		if (Input::GetKey(eKeyCode::UP)
			&& Input::GetKeyDown(eKeyCode::S))
		{
			mState = eState::jumpup;
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownTAX");
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownTAX");
				mState = eState::Down;
			}
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;	
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"PlayerrightUPgunTAX");
				mState = eState::Upattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"PlayerleftUPgunTAX");
				mState = eState::Upattack;
			}
			mComplete = true;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::Up;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::Up;
			}
		}

	}
	void PlayerTop::UpAttack()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyDown(eKeyCode::A)
			&& animator->GetIndex() > 4)
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"PlayerrightUPgunTAX");
				mState = eState::Upattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"PlayerleftUPgunTAX");
				mState = eState::Upattack;
			}
			mComplete = true;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightUPidleTAX", true);
			mState = eState::Up;
			mDirect = true;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
			mState = eState::Up;
			mDirect = false;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::Up;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::Up;
			}
		}
		if (Input::GetKeyUp(eKeyCode::UP))
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
	void PlayerTop::JumpDown()
	{
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::RIGHT))
			mLateDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mLateDirect = false;
	
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y += 70.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Down);
				animator->PlayAnimation(L"PlayerrightjumpdowngunTAX");
				mState = eState::jumpdownattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y += 70.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Down);
				animator->PlayAnimation(L"PlayerleftjumpdowngunTAX");
				mState = eState::jumpdownattack;
			}
			mComplete = true;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::jumpdown;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::jumpdown;
			}
		}
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightjumpdownupTAX");
				mState = eState::jump;

			}
			else
			{
				animator->PlayAnimation(L"PlayerleftjumpdownupTAX");
				mState = eState::jump;
			}
		}

		if (PlayerBottom::Getground())
		{
			if (mLateDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightTAX", true);
				mState = eState::Idle;
				mDirect = true;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftTAX", true);
				mState = eState::Idle;
				mDirect = false;
			}
		}
	}
	void PlayerTop::JumpAttack()
	{
		mComplete = false;
		Animator* animator = GetComponent<Animator>();
		

		if (Input::GetKey(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mDirect = false;
		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightjumpdownTAX");
				mState = eState::jumpdown;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftjumpdownTAX");
				mState = eState::jumpdown;
			};
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightUPTAX");
				mState = eState::jumpup;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftUPTAX");
				mState = eState::jumpup;
			}
		}
		if (Input::GetKeyDown(eKeyCode::A)
			&& animator->GetIndex() > 4)
		{

			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Right);
				animator->PlayAnimation(L"PlayerrightgunTAX");
				mState = eState::Jumpattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 40.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Left);
				animator->PlayAnimation(L"PlayerleftgunTAX");
				mState = eState::Jumpattack;
			}
			mComplete = true;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::jump;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::jump;
			}
		}

		if (animator->Getcomplete())
		{

			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightTAX", true);
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftTAX", true);
				mState = eState::jump;
			}
			mComplete = true;
		}
		if (PlayerBottom::Getground())
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
			mComplete = true;
		}
	}
	void PlayerTop::JumpBomb()
	{
		mComplete = false;
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyDown(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKeyDown(eKeyCode::LEFT))
			mDirect = false;

		if (animator->Getcomplete())
		{

			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightTAX", true);
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftTAX", true);
				mState = eState::jump;
			}
			mComplete = true;
		}
		if (PlayerBottom::Getground())
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
			mComplete = true;
		}
	}
	void PlayerTop::JumpDownAttack()
	{
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mDirect = false;

		if (Input::GetKeyDown(eKeyCode::A)
			&& animator->GetIndex() > 4)
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y += 70.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Down);
				animator->PlayAnimation(L"PlayerrightjumpdowngunTAX");
				mState = eState::jumpdownattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y += 70.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Down);
				animator->PlayAnimation(L"PlayerleftjumpdowngunTAX");
				mState = eState::jumpdownattack;
			}
			mComplete = true;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::jumpdown;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::jumpdown;
			}
		}

		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightjumpdownupTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftjumpdownupTAX");
				mState = eState::jump;
			}
		}
		if (PlayerBottom::Getground())
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
			mComplete = true;
		}
	}
	void PlayerTop::JumpUpAttack()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyDown(eKeyCode::A)
			&& animator->GetIndex() > 4)
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"PlayerrightUPgunTAX");
				mState = eState::jumpupattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"PlayerleftUPgunTAX");
				mState = eState::jumpupattack;
			}
			mComplete = true;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::jumpup;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::jumpup;
			}
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightUPidleTAX", true);
			mState = eState::jumpup;
			mDirect = true;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
			mState = eState::jumpup;
			mDirect = false;
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightTAX", true);
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftTAX", true);
				mState = eState::jump;
			}
		}
		if (PlayerBottom::Getground())
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
			mComplete = true;
		}
	}
	void PlayerTop::JumpUp()
	{
		mComplete = false;
		Animator* animator = GetComponent<Animator>();
		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightUPidleTAX", true);

			}
			if (!mDirect)
			{
				animator->PlayAnimation(L"PlayerleftUPidleTAX", true);

			}
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightUPidleTAX", true);
			mState = eState::jumpup;
			mDirect = true;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
			mState = eState::jumpup;
			mDirect = false;
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightUPdownTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftUPdownTAX");
				mState = eState::jump;
			}
		}

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightjumpdownTAX");
				mState = eState::jumpdown;
			}
			else
			{
				animator->PlayAnimation(L"PlayerrightjumpdownTAX");
				mState = eState::jumpdown;
			}
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"PlayerrightUPgunTAX");
				mState = eState::jumpupattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"PlayerleftUPgunTAX");
				mState = eState::jumpupattack;
			}
			mComplete = true;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			if (mDirect)
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x += 30.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = eState::jumpup;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = eState::jumpup;
			}
		}
		if (PlayerBottom::Getground())
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
			mComplete = true;
		}
	}
	void PlayerTop::ResourceLoad()
	{
		Texture* imagePlayer = Resources::Load<Texture>(L"Player"
			, L"..\\Resource\\Character\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Marco Rossi.bmp");
		Animator* at = this->AddComponent<Animator>();
		Collider* col = this->AddComponent<Collider>();
		Transform* tr = this->AddComponent<Transform>();
		at->CreateAnimation(L"PlayerIdlerightTAX", imagePlayer, Vector2(0.0f, 264.0f), Vector2(44.0f, 34.0f), 4, Vector2(0.0f, 17.0f));
		at->CreateAnimation(L"PlayerIdleleftTAX", imagePlayer, Vector2(44.0f, 304.0f), Vector2(44.0f, 34.0f), 4, Vector2(-35.0f, 13.0f));
		at->CreateAnimation(L"PlayerrightTAX", imagePlayer, Vector2(0.0f, 472.0f), Vector2(44.0f, 34.0f), 12, Vector2(-5.0f, -5.0f), 0.05f);
		at->CreateAnimation(L"PlayerleftTAX", imagePlayer, Vector2(0.0f, 391.0f), Vector2(44.0f, 34.0f), 12, Vector2(-5.0f, -5.0f), 0.05f);
		at->CreateAnimation(L"PlayerdeadTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(-20.0f, -2.0f));
		at->CreateAnimation(L"PlayerrightjumpTAX", imagePlayer, Vector2(0.0f, 572.0f), Vector2(44.0f, 44.0f), 6, Vector2(-20.0f, -5.0f), 0.2f);
		at->CreateAnimation(L"PlayerleftjumpTAX", imagePlayer, Vector2(0.0f, 660.0f), Vector2(44.0f, 44.0f), 6, Vector2(5.0f, -5.0f), 0.2f);
		at->CreateAnimation(L"PlayerrightbombTAX", imagePlayer, Vector2(0.0f, 792.0f), Vector2(44.0f, 44.0f), 6, Vector2(-3.0f, -8.0f), 0.001f);
		at->CreateAnimation(L"PlayerleftbombTAX", imagePlayer, Vector2(0.0f, 924.0f), Vector2(44.0f, 44.0f), 6, Vector2(-6.0f, -8.0f), 0.001f);
		at->CreateAnimation(L"PlayerrightknifeTAX", imagePlayer, Vector2(0.0f, 836.0f), Vector2(44.0f, 88.0f), 6, Vector2(-8.0f, -3.0f), 0.001f);
		at->CreateAnimation(L"PlayerleftknifeTAX", imagePlayer, Vector2(0.0f, 968.0f), Vector2(44.0f, 88.0f), 6, Vector2(-10.0f, -3.0f), 0.001f);
		at->CreateAnimation(L"PlayerrightgunTAX", imagePlayer, Vector2(0.0f, 1056.0f), Vector2(88.0f, 44.0f), 10, Vector2(5.0f, 0.0f), 0.0001f);
		at->CreateAnimation(L"PlayerleftgunTAX", imagePlayer, Vector2(0.0f, 1100.0f), Vector2(88.0f, 44.0f), 10, Vector2(-15.0f, 0.0f), 0.0001f);
		at->CreateAnimation(L"PlayerrightdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightdownwalkTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f));
		at->CreateAnimation(L"PlayerleftdownwalkTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f));
		at->CreateAnimation(L"PlayerrightdownidleTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f));
		at->CreateAnimation(L"PlayerleftdownidleTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f));
		at->CreateAnimation(L"PlayerrightrunjumpTAX", imagePlayer, Vector2(308.0f, 792.0f), Vector2(44.0f, 44.0f), 6, Vector2(-15.0f, 0.0f), 0.2f);
		at->CreateAnimation(L"PlayerleftrunjumpTAX", imagePlayer, Vector2(308.0f, 880.0f), Vector2(44.0f, 44.0f), 6, Vector2(5.0f, 0.0f), 0.2f);
		at->CreateAnimation(L"PlayerleftdownbombTAX", imagePlayer, Vector2(264.0f, 1408.0f), Vector2(0.0f, 0.0f), 6, Vector2(0.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"PlayerrightdowngunTAX", imagePlayer, Vector2(0.0f, 1320.0f), Vector2(0.0f, 0.0f), 6, Vector2(0.0f, -18.0f), 0.01f);
		at->CreateAnimation(L"PlayerrightgunTAX", imagePlayer, Vector2(0.0f, 1056.0f), Vector2(88.0f, 44.0f), 10, Vector2(5.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftgunTAX", imagePlayer, Vector2(0.0f, 1100.0f), Vector2(88.0f, 44.0f), 10, Vector2(-15.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightUPTAX", imagePlayer, Vector2(264.0f, 1496.0f), Vector2(44.0f, 44.0f), 2, Vector2(0.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftUPTAX", imagePlayer, Vector2(352.0f, 1496.0f), Vector2(44.0f, 44.0f), 2, Vector2(-15.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightUPdownTAX", imagePlayer, Vector2(704.0f, 1496.0f), Vector2(44.0f, 44.0f), 2, Vector2(0.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftUPdownTAX", imagePlayer, Vector2(792.0f, 1496.0f), Vector2(44.0f, 44.0f), 2, Vector2(-15.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightUPidleTAX", imagePlayer, Vector2(528.0f, 1540.0f), Vector2(44.0f, 44.0f), 4, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"PlayerleftUPidleTAX", imagePlayer, Vector2(704.0f, 1540.0f), Vector2(44.0f, 44.0f), 4, Vector2(-15.0f, 0.0f));
		at->CreateAnimation(L"PlayerrightUPgunTAX", imagePlayer, Vector2(308.0f, 1144.0f), Vector2(44.0f, 88.0f), 10, Vector2(-16.0f, -43.0f), 0.0001f);
		at->CreateAnimation(L"PlayerleftUPgunTAX", imagePlayer, Vector2(308.0f, 1232.0f), Vector2(44.0f, 88.0f), 10, Vector2(0.0f, -43.0f), 0.0001f);
		at->CreateAnimation(L"PlayerrightjumpdownTAX", imagePlayer, Vector2(0.0f, 1496.0f), Vector2(44.0f, 44.0f), 3, Vector2(0.0f, 15.0f), 0.0001f);
		at->CreateAnimation(L"PlayerleftjumpdownTAX", imagePlayer, Vector2(132.0f, 1496.0f), Vector2(44.0f, 44.0f), 3, Vector2(-15.0f, 15.0f), 0.0001f);
		at->CreateAnimation(L"PlayerrightjumpdownupTAX", imagePlayer, Vector2(440.0f, 1496.0f), Vector2(44.0f, 44.0f), 3, Vector2(0.0f, 15.0f), 0.0001f);
		at->CreateAnimation(L"PlayerleftjumpdownupTAX", imagePlayer, Vector2(572.0f, 1496.0f), Vector2(44.0f, 44.0f), 3, Vector2(-15.0f, 15.0f), 0.0001f);
		at->CreateAnimation(L"PlayerrightjumpdowngunTAX", imagePlayer, Vector2(0.0f, 1540.0f), Vector2(44.0f, 88.0f), 6, Vector2(-5.0f, 52.0f), 0.001f);
		at->CreateAnimation(L"PlayerleftjumpdowngunTAX", imagePlayer, Vector2(264.0f, 1540.0f), Vector2(44.0f, 88.0f), 6, Vector2(-5.0f, 52.0f), 0.001f);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"PlayerIdlerightTAX", true);
	}
}