#include "sbPlayerBottom.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimator.h"
#include "sbRigidbody.h"
#include "sbPlayerTop.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbSpriteRenderer.h"
#include "sbObject.h"
#include "sbCollider.h"
#include "sbNormalBullet.h"
#include "sbEfBomb.h"

namespace sb
{
	math::Vector2 PlayerBottom::mPlayposition = {};
	bool PlayerBottom::mGround = {};
	bool PlayerBottom::mComplete = {};
	
	float PBtimecheck = 0.0f;
	PlayerBottom::PlayerBottom()
		:mDirect(true)	
		,mKeyUp(false)
		,mRun(false)
		,mFree(false)
		,mLateDirect(true)
	{
		ResourceLoad();
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
		Animator* animator = GetComponent<Animator>();
		///pixel Ãæµ¹
		//COLORREF rgb = mFloorTexture->GetTexturePixel(tr->GetPosition().x, tr->GetPosition().y );

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
		case sb::PlayerBottom::eState::jumpdown:
			JumpDown();
			break;
		case sb::PlayerBottom::eState::attack:
			Attack();
			break;
		case sb::PlayerBottom::eState::jumpattack:
			JumpAttack();
			break;
		case sb::PlayerBottom::eState::jumpdownattack:
			JumpDownAttack();
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
		mComplete = animator->Getcomplete();
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

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			//animator->PlayAnimation(L"PlayerUpMove", true);
			mState = eState::Move;
			return;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightBAX", true);
			mState = eState::Move;
			mDirect = true;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
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
			return;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftBAX", true);				
			mState = eState::Move;
			mDirect = false;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
		}
		if (Input::GetKeyDown(eKeyCode::Z))
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

			Rigidbody* rb = GetComponent<Rigidbody>();
			Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
			return;
		}

	}
	void PlayerBottom::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Vector2 pos = tr->GetPosition();
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
			mRun = false;
			return;
		}
	
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightBAX", true);
			mState = eState::Move;
			mDirect = true;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftBAX", true);
			mState = eState::Move;
			mDirect = false;
			return;
		}

		if (Input::GetKey(eKeyCode::RIGHT))
			{
				pos.x += Player_Speed * Time::DeltaTime();
				mDirect = true;
			}

		if (Input::GetKey(eKeyCode::LEFT))
			{
				pos.x -= Player_Speed * Time::DeltaTime();
				mDirect = false;
			}

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownwalkBAX", true);
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownwalkBAX", true);
				mState = eState::Down;
			}
			return;
		}

		if (Input::GetKeyDown(eKeyCode::S))
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
			mRun = true;
			return;
		}
		tr->SetPosition(pos);
	}
	void PlayerBottom::Attack()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= Player_Speed * Time::DeltaTime();
			mDirect = false;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += Player_Speed * Time::DeltaTime();
			mDirect = true;
		}
		tr->SetPosition(pos);
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (Input::GetKeyUp(eKeyCode::LEFT)
				|| Input::GetKeyUp(eKeyCode::LEFT))
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
			mRun = false;
			return;
		}
		if (PlayerTop::GetComplete())
		{
			int Index = animator->GetIndex();
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightBAX",true);
				animator->SetIndex(Index);
				mState = eState::Move;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftBAX",true);
				animator->SetIndex(Index);
				mState = eState::Move;
			}
			return;
		}
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
			pos.x -= Player_Speed * Time::DeltaTime();
		
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += Player_Speed * Time::DeltaTime();
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mDirect = false;

		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mDirect = true;

		}
		tr->SetPosition(pos);
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mState = eState::jumpdown;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			PBtimecheck = 0.0f;
			int Index = (animator->GetIndex());
			if (mRun)
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightrunjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpattack;
				}
				else
				{

					animator->PlayAnimation(L"PlayerleftrunjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpattack;
				}
			}

			else
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpattack;
				}
				else
				{
					animator->PlayAnimation(L"PlayerleftjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpattack;
				}
			}
			return;
		}
		

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
			mRun = false;
			mFree = false;
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
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightdownwalkBAX", true);
			mDirect = true;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= Player_DownSpeed * Time::DeltaTime();

		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += Player_DownSpeed * Time::DeltaTime();
		}
		tr->SetPosition(pos);
		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightdownidleBAX", true);
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftdownidleBAX", true);
				mState = eState::Down;
			}
			return;
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
				animator->PlayAnimation(L"PlayerrightdownbombBAX");
				mState = eState::DownBomb;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerrightbombTAX");
				animator->PlayAnimation(L"PlayerleftdownbombBAX");
				mState = eState::DownBomb;
			}
			return;
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
				animator->PlayAnimation(L"PlayerrightdowngunBAX");
				mState = eState::Downattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 40.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Left);
				animator->PlayAnimation(L"PlayerleftdowngunBAX");
				mState = eState::Downattack;
			}
			return;
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


	}
	void PlayerBottom::DownAttack()
	{
		Animator* animator = GetComponent<Animator>();
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
			return;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightdownwalkBAX", true);
			mState = eState::Down;
			mDirect = true;

		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftdownwalkBAX", true);
			mState = eState::Down;
			mDirect = false;
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
				animator->PlayAnimation(L"PlayerrightdowngunBAX");
				mState = eState::Downattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 40.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Left);
				animator->PlayAnimation(L"PlayerleftdowngunBAX");
				mState = eState::Downattack;
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
				animator->PlayAnimation(L"PlayerrightdownbombBAX");
				mState = eState::DownBomb;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.x -= 50.0f;
				EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
				efbomb->SetDirect(mDirect);
				animator->PlayAnimation(L"PlayerleftdownbombBAX");
				mState = eState::DownBomb;
			}
			return;
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			mDirect = false;
			mRun = true;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			mDirect = true;
			mRun = true;
		}

		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mRun = false;
		}
		if (animator->Getcomplete())
		{
			if (mRun)
			{
				if(mDirect)
				{
					animator->PlayAnimation(L"PlayerrightdownwalkBAX", true);
					mState = eState::Down;
					mDirect = true;
				
				}
				else
				{
					animator->PlayAnimation(L"PlayerleftdownwalkBAX", true);
					mState = eState::Down;
					mDirect = false;
				}
			}
			else
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightdownidleBAX", true);
					mState = eState::Down;

				}
				else
				{
					animator->PlayAnimation(L"PlayerleftdownidleBAX", true);
					mState = eState::Down;

				}
			}
			return;
		}

	}
	void PlayerBottom::DownBomb()
	{
		Animator* animator = GetComponent<Animator>();
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
			return;
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			mDirect = false;
			mRun = true;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			mDirect = true;
			mRun = true;
		}

		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mRun = false;
		}

		if ( animator->Getcomplete())
		{
			if (mRun)
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightdownwalkBAX", true);
					mState = eState::Down;
					mDirect = true;
				}
				else
				{
					animator->PlayAnimation(L"PlayerleftdownwalkBAX", true);
					mState = eState::Down;
					mDirect = false;
				}
				mRun = false;
			}
			else
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightdownidleBAX", true);
					mState = eState::Down;
				}
				else if (!mDirect)
				{
					animator->PlayAnimation(L"PlayerleftdownidleBAX", true);
					mState = eState::Down;
				}
			}
			return;
		}
	}
	void PlayerBottom::JumpAttack()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 pos = tr->GetPosition();
		PBtimecheck += Time::DeltaTime();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= Player_Speed * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += Player_Speed * Time::DeltaTime();
		}
		tr->SetPosition(pos);
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mDirect = false;
		if (Input::GetKey(eKeyCode::A) || Input::GetKey(eKeyCode::D))
			
		{
			if (PBtimecheck >= 0.2f
				&& PBtimecheck < 0.3f)
			{
				int Index = (animator->GetIndex());
				if (mRun)
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"PlayerrightrunjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jumpattack;
						PBtimecheck = 0.0f;
					}
					else
					{

						animator->PlayAnimation(L"PlayerleftrunjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jumpattack;
						PBtimecheck = 0.0f;
					}
				}

				else
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"PlayerrightjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jumpattack;
						PBtimecheck = 0.0f;
					}
					else
					{
						animator->PlayAnimation(L"PlayerleftjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jumpattack;
						PBtimecheck = 0.0f;
					}
				}
			}
			else 
			{
				int Index = (animator->GetIndex());
				if (mRun)
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"PlayerrightrunjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jump;
						PBtimecheck = 0.0f;
					}
					else
					{

						animator->PlayAnimation(L"PlayerleftrunjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jump;
						PBtimecheck = 0.0f;
					}
				}

				else
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"PlayerrightjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jump;
						PBtimecheck = 0.0f;
					}
					else
					{
						animator->PlayAnimation(L"PlayerleftjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jump;
						PBtimecheck = 0.0f;
					}
				}
			}
			return;
		}

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
			mRun = false;
			mFree = false;
		}
	}
	void PlayerBottom::JumpDownAttack()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 pos = tr->GetPosition();
		PBtimecheck += Time::DeltaTime();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 1000.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 1000.0f * Time::DeltaTime();
		}
		tr->SetPosition(pos);
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mDirect = false;

		if (Input::GetKey(eKeyCode::A) || Input::GetKey(eKeyCode::D))
		{
			if (PBtimecheck >= 0.05f
				&& PBtimecheck < 0.2f)
			{
				int Index = (animator->GetIndex());
				if (mRun)
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"PlayerrightrunjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jumpdownattack;
						PBtimecheck = 0.0f;
					}
					else
					{

						animator->PlayAnimation(L"PlayerleftrunjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jumpdownattack;
						PBtimecheck = 0.0f;
					}
				}

				else
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"PlayerrightjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jumpdownattack;
						PBtimecheck = 0.0f;
					}
					else
					{
						animator->PlayAnimation(L"PlayerleftjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jumpdownattack;
						PBtimecheck = 0.0f;
					}
				}
			}
			else
			{
				int Index = (animator->GetIndex());
				if (mRun)
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"PlayerrightrunjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jump;
						PBtimecheck = 0.0f;
					}
					else
					{

						animator->PlayAnimation(L"PlayerleftrunjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jump;
						PBtimecheck = 0.0f;
					}
				}

				else
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"PlayerrightjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jump;
						PBtimecheck = 0.0f;
					}
					else
					{
						animator->PlayAnimation(L"PlayerleftjumpBAX");
						animator->SetIndex(Index);
						mState = eState::jump;
						PBtimecheck = 0.0f;
					}
				}
			
			}
			return;
		}
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
			mRun = false;
			mFree = false;
		}
	}
	void PlayerBottom::JumpDown()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= Player_Speed * Time::DeltaTime();

		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += Player_Speed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT))
			mLateDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mLateDirect = false;

	

		if (Input::GetKeyDown(eKeyCode::A))
		{
			int Index = (animator->GetIndex());
			if (mRun)
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightrunjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpdownattack;
					PBtimecheck = 0.0f;
				}
				else
				{

					animator->PlayAnimation(L"PlayerleftrunjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpdownattack;
					PBtimecheck = 0.0f;
				}
			}

			else
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpdownattack;
					PBtimecheck = 0.0f;
				}
				else
				{
					animator->PlayAnimation(L"PlayerleftjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpdownattack;
					PBtimecheck = 0.0f;
				}
			}
			return;
		}
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			mState = eState::jump;
			return;
		}

		if (rb->GetGround())
		{
			if (mLateDirect)
			{
				animator->PlayAnimation(L"PlayerIdlerightBAX", true);
				mState = eState::Idle;
				mDirect = true;
			}
			else
			{
				animator->PlayAnimation(L"PlayerIdleleftBAX", true);
				mState = eState::Idle;
				mDirect = false;
			}
		}
		tr->SetPosition(pos);
	}
	
	void PlayerBottom::Death()
	{
	}
	void PlayerBottom::ResourceLoad()
	{
		Texture* imagePlayer = Resources::Load<Texture>(L"Player"
			, L"..\\Resource\\Character\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Marco Rossi.bmp");
		Animator* at = this->AddComponent<Animator>();
		Rigidbody* rb = this->AddComponent<Rigidbody>();
		Collider* col = this->AddComponent<Collider>();
		Transform* tr = this->AddComponent<Transform>();
		at->CreateAnimation(L"PlayerIdlerightBAX", imagePlayer, Vector2(176.0f, 258.0f), Vector2(44.0f, 36.0f), 1);
		at->CreateAnimation(L"PlayerIdleleftBAX", imagePlayer, Vector2(0.0f, 299.0f), Vector2(44.0f, 36.0f), 1, Vector2(-35.0f, 0.0f));
		at->CreateAnimation(L"PlayerrightBAX", imagePlayer, Vector2(0.0f, 506.0f), Vector2(44.0f, 25.0f), 12, Vector2(-10.0f, 40.0f), 0.05f);
		at->CreateAnimation(L"PlayerleftBAX", imagePlayer, Vector2(0.0f, 425.0f), Vector2(44.0f, 25.0f), 12, Vector2(0.0f, 40.0f), 0.05f);
		at->CreateAnimation(L"PlayerdeadBAX", imagePlayer, Vector2(906.0f, 53.0f), Vector2(44.0f, 44.0f), 19, Vector2(5.0f, -4.0f));
		at->CreateAnimation(L"PlayerrightjumpBAX", imagePlayer, Vector2(0.0f, 616.0f), Vector2(44.0f, 44.0f), 12, Vector2(-10.0f, 60.0f), 0.05f);
		at->CreateAnimation(L"PlayerleftjumpBAX", imagePlayer, Vector2(0.0f, 704.0f), Vector2(44.0f, 44.0f), 12, Vector2(5.0f, 60.0f), 0.05f);
		at->CreateAnimation(L"PlayerrightdownBAX", imagePlayer, Vector2(0.0f, 1144.0f), Vector2(44.0f, 44.0f), 7, Vector2(13.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdownBAX", imagePlayer, Vector2(0.0f, 1188.0f), Vector2(44.0f, 44.0f), 7, Vector2(-25.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightdownwalkBAX", imagePlayer, Vector2(0.0f, 1232.0f), Vector2(44.0f, 44.0f), 7, Vector2(13.0f, -18.0f));
		at->CreateAnimation(L"PlayerleftdownwalkBAX", imagePlayer, Vector2(0.0f, 1276.0f), Vector2(44.0f, 44.0f), 7, Vector2(-7.0f, -18.0f));
		at->CreateAnimation(L"PlayerrightdownidleBAX", imagePlayer, Vector2(132.0f, 1144.0f), Vector2(44.0f, 44.0f), 4, Vector2(13.0f, -18.0f));
		at->CreateAnimation(L"PlayerleftdownidleBAX", imagePlayer, Vector2(132.0f, 1188.0f), Vector2(44.0f, 44.0f), 4, Vector2(-7.0f, -18.0f));
		at->CreateAnimation(L"PlayerrightrunjumpBAX", imagePlayer, Vector2(308.0f, 836.0f), Vector2(44.0f, 44.0f), 6, Vector2(-15.0f, -5.0f));
		at->CreateAnimation(L"PlayerleftrunjumpBAX", imagePlayer, Vector2(308.0f, 924.0f), Vector2(44.0f, 44.0f), 6, Vector2(0.0f, -5.0f));
		at->CreateAnimation(L"PlayerrightdowngunBAX", imagePlayer, Vector2(0.0f, 1320.0f), Vector2(88.0f, 44.0f), 10, Vector2(0.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdowngunBAX", imagePlayer, Vector2(0.0f, 1364.0f), Vector2(88.0f, 44.0f), 10, Vector2(0.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightdownbombBAX", imagePlayer, Vector2(0.0f, 1408.0f), Vector2(44.0f, 44.0f), 6, Vector2(0.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"PlayerleftdownbombBAX", imagePlayer, Vector2(264.0f, 1408.0f), Vector2(44.0f, 44.0f), 6, Vector2(0.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"PlayerrightjumatAX", imagePlayer, Vector2(0.0f, 616.0f), Vector2(44.0f, 44.0f), 12, Vector2(5.0f, 40.0f), 0.1f);
		at->CreateAnimation(L"PlayerleftjumatAX", imagePlayer, Vector2(0.0f, 704.0f), Vector2(44.0f, 44.0f), 12, Vector2(5.0f, 40.0f), 0.1f);
		at->CreateAnimation(L"PlayerrightdownBAX", imagePlayer, Vector2(0.0f, 1144.0f), Vector2(44.0f, 44.0f), 7, Vector2(13.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdownBAX", imagePlayer, Vector2(0.0f, 1188.0f), Vector2(44.0f, 44.0f), 7, Vector2(-25.0f, -18.0f), 0.000001f);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"PlayerIdlerightBAX", true);
		col->SetSize(Vector2(100.0f, 160.0f));
		Vector2 pbpos = tr->GetPosition();
		col->SetPosition(pbpos);
	}
}
