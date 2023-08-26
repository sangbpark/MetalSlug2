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
#include "sbHeavyBullet.h"




namespace sb
{
	bool PlayerTop::mComplete = false;

	PlayerTop::PlayerTop()

		: mDirect(true)
		, mKeyUp(false)
		, mLateDirect(true)
		, ptTimecheck(0.0f)
		, mWeaponState(eWeaponState::normal)
		, mHeavyBullet(0.0f)
		, mHeavyBullettime(0.0f)
		, mHeavyBulletCount(false)
		, mState(eState::Idle)
		, mRide(false)
		, mVictory(false)
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

		GetPlayerBottomState();
		if(!mRide
			|| !mVictory)
		{
			if (mWeaponState == eWeaponState::heavy)
				mHeavyBullettime += Time::DeltaTime();
			else
				mHeavyBullettime = 0.0f;

			if (mWeaponState == eWeaponState::normal)
			{
				switch (mState)
				{
				case sb::PlayerTop::eState::Idle:
					Idle();
					break;
				case sb::PlayerTop::eState::StopAnimator:
					StopAnimator();
					break;
				case sb::PlayerTop::eState::Stop:
					Stop();
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
				case sb::PlayerTop::eState::revive:
					Revive();
					break;
				case sb::PlayerTop::eState::bomb:
					Bomb();
					break;
				case sb::PlayerTop::eState::stay:
					Stay();
					break;
				case sb::PlayerTop::eState::Ride:
					Ride();
					break;
				case sb::PlayerTop::eState::Victory:
					Victory();
					break;
				default:
					break;
				}
			}
			else if (mWeaponState == eWeaponState::heavy)
			{
				switch (mState)
				{
				case sb::PlayerTop::eState::Idle:
					HIdle();
					break;
				case sb::PlayerTop::eState::Up:
					HUp();
					break;
				case sb::PlayerTop::eState::StopAnimator:
					StopAnimator();
					break;
				case sb::PlayerTop::eState::Stop:
					Stop();
					break;
				case sb::PlayerTop::eState::huping:
					HUping();
					break;
				case sb::PlayerTop::eState::hupdowning:
					HUpDowning();
					break;
				case sb::PlayerTop::eState::Move:
					HMove();
					break;
				case sb::PlayerTop::eState::Down:
					HDown();
					break;
				case sb::PlayerTop::eState::jump:
					HJump();
					break;
				case sb::PlayerTop::eState::jumpup:
					HJumpUp();
					break;
				case sb::PlayerTop::eState::jumpdown:
					HJumpDown();
					break;
				case sb::PlayerTop::eState::hjumpdowning:
					HJumpDowning();
					break;
				case sb::PlayerTop::eState::hjumpdownuping:
					HJumpDownUping();
					break;
				case sb::PlayerTop::eState::Jumpattack:
					HJumpAttack();
					break;
				case sb::PlayerTop::eState::jumpdownattack:
					HJumpDownAttack();
					break;
				case sb::PlayerTop::eState::jumpupattack:
					HJumpUpAttack();
					break;
				case sb::PlayerTop::eState::jumpbomb:
					HJumpBomb();
					break;
				case sb::PlayerTop::eState::Death:
					Death();
					break;
				case sb::PlayerTop::eState::revive:
					Revive();
					break;
				case sb::PlayerTop::eState::bomb:
					HBomb();
					break;
				case sb::PlayerTop::eState::stay:
					HStay();
					break;
				case sb::PlayerTop::eState::Ride:
					Ride();
					break;
				case sb::PlayerTop::eState::Victory:
					Victory();
				default:
					break;
				}
			}
		}


		
	}
	void PlayerTop::Render(HDC hdc)
	{
		if(!mRide)
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
			return;
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
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
				return;
			}

		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightTAX", true);
			mState = eState::Move;
			return;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftTAX", true);
			mState = eState::Move;
			return;
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
			if (mRide)
				return;
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
			return;
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
			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::bomb);
			return;
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
			return;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightTAX", true);
			mState = eState::Move;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftTAX", true);
			mState = eState::Move;
			return;
		}

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

	
		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
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
				return;
			}
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
			if (mRide)
				return;
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
			CreatEfBomb(eState::bomb);
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
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			at->PlayAnimation(L"PlayerreviveTAX");
			mState = eState::revive;
		}
	}
	void PlayerTop::Attack()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftTAX", true);
			mState = eState::Move;
			return;

		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightTAX", true);
			mState = eState::Move;
			return;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
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
				return;
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
			return;
		}

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
			return;
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
			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::bomb);
			return;
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
	void PlayerTop::Bomb()
	{
		Animator* animator = GetComponent<Animator>();

		if (mDirect)
		{
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				animator->PlayAnimation(L"PlayerleftTAX", true);
				mState = eState::Move;

			}
		}
		if (!mDirect)
		{
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				animator->PlayAnimation(L"PlayerrightTAX", true);
				mState = eState::Move;
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
			if (mRide)
				return;
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
			ptTimecheck = 0.0f;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			
			CreatEfBomb(eState::jumpbomb);
			return;
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
			return;
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
			return;
		}

		if (mbGround)
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
			return;
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mRide)
				return;
			animator->PlayAnimation(L"PlayerrightdowngunTAX");
			mState = eState::stay;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			animator->PlayAnimation(L"PlayerleftdownbombTAX");
			mState = eState::stay;
			return;
		}
	}
	void PlayerTop::Stay()
	{
		Animator* animator = GetComponent<Animator>();
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
			return;
		}

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
	}
	void PlayerTop::Up()
	{
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
			return;
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightUPidleTAX", true);
			mState = eState::Up;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
			mState = eState::Up;
			return;
		}

		if (Input::GetKey(eKeyCode::UP)
			&& Input::GetKeyDown(eKeyCode::S))
		{
			mState = eState::jumpup;
			return;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
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
				return;
			}
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			if (mRide)
				return;
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
			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::Up);
			return;
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
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightUPidleTAX", true);
			mState = eState::Up;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
			mState = eState::Up;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::Up);
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
			if (mRide)
				return;
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
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::jumpdown);
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

		if (mbGround)
		{
			if (mLateDirect)
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
	void PlayerTop::JumpAttack()
	{
		Animator* animator = GetComponent<Animator>();
		ptTimecheck += Time::DeltaTime();

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
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::jump);
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
		}
		if (mbGround)
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
	void PlayerTop::JumpBomb()
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
		if (mbGround)
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
	void PlayerTop::JumpDownAttack()
	{
		Animator* animator = GetComponent<Animator>();
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
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::jumpdown);
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
		if (mbGround)
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
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::jumpup);
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightUPidleTAX", true);
			mState = eState::jumpup;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
			mState = eState::jumpup;
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
		if (mbGround)
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
	void PlayerTop::JumpUp()
	{
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
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftUPidleTAX", true);
			mState = eState::jumpup;
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
			if (mRide)
				return;
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
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatEfBomb(eState::jumpup);
		}
		if (mbGround)
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

	void PlayerTop::Ride()
	{
	}

	void PlayerTop::HIdle()
	{
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPTAX");
				mState = eState::huping;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftUPTAX");
				mState = eState::huping;
			}
	
			return;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightTAX", true);
			mState = eState::Move;
	
			return;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayerleftTAX", true);
			mState = eState::Move;
		
			return;
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
			{

				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownTAX");
					mState = eState::Down;
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownTAX");
					mState = eState::Down;
				}
		
				return;
			}

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
		if (Input::GetKey(eKeyCode::A))
		{
			if(mHeavyBullettime >= 0.2f)
			{
				if (mDirect)
				{
					CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 20.0f));
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerrightgunTAX");
				}
				else
				{
					CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 20.0f));
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerleftgunTAX");

				}
				mHeavyBullettime = 0.0f;
				return;
			}

		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightjumpTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftjumpTAX");
				mState = eState::jump;
			}

			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::bomb);
			return;
		}
		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}
	void PlayerTop::HMove()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}

			return;
		}
		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightTAX", true);
				mState = eState::Move;		
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftTAX", true);
				mState = eState::Move;
			}
		}
	

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightTAX", true);
			mState = eState::Move;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayerleftTAX", true);
			mState = eState::Move;;
			return;
		}

		if (Input::GetKey(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPTAX");
				mState = eState::huping;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftUPTAX");
				mState = eState::huping;
			}
			return;
		}


		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownTAX");
					mState = eState::Down;
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownTAX");
					mState = eState::Down;
				}
				return;
			}
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
		if (Input::GetKey(eKeyCode::A))
		{
			if (mHeavyBullettime >=0.2f)
			{
				if (mDirect)
				{
					CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 20.0f));
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerrightgunTAX");
				}
				else
				{
					CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 20.0f));
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerleftgunTAX");
				}
				mHeavyBullettime = 0.0f;
				return;
			}
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::bomb);
			return;
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightrunjumpTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftrunjumpTAX");
				mState = eState::jump;
			}
		}
	}
	void PlayerTop::HBomb()
	{
		Animator* animator = GetComponent<Animator>();

		if (mDirect)
		{
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				animator->PlayAnimation(L"hPlayerleftTAX", true);
				mState = eState::Move;

			}
		}
		if (!mDirect)
		{
			if (Input::GetKeyDown(eKeyCode::RIGHT))
			{
				animator->PlayAnimation(L"hPlayerrightTAX", true);
				mState = eState::Move;
			}
		}
		if (animator->Getcomplete())
		{
			if (mDirect)
			{

				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}
	void PlayerTop::HJump()
	{

		Animator* animator = GetComponent<Animator>();

		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
			}
		
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if(mHeavyBullettime >=0.2f)
			{
				if (mDirect)
				{
					CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 20.0f));
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerrightgunTAX");

				}
				else
				{
					CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 20.0f));
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerleftgunTAX");
		
				}
				mHeavyBullettime = 0.0f;
			}
	
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::jumpbomb);
			return;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPTAX");
				mState = eState::huping;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftUPTAX");
				mState = eState::huping;
			}
			return;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			mKeyUp = false;
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownTAX");
				mState = eState::hjumpdowning;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownTAX");
				mState = eState::hjumpdowning;
			}
			return;
		}

		if (mbGround)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}
	void PlayerTop::HDown()
	{

		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
			return;
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			animator->PlayAnimation(L"hPlayerrightdowngunTAX");
			mState = eState::stay;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			animator->PlayAnimation(L"hPlayerleftdownbombTAX");
			mState = eState::stay;
			return;
		}
	}
	void PlayerTop::HStay()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
			return;
		}

		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightdownTAX", true);
				mState = eState::Down;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftdownTAX", true);
				mState = eState::Down;
			}
		}
	}
	void PlayerTop::HUp()
	{
		Animator* animator = GetComponent<Animator>();
		mHeavyBullet = 0.21f;
		if (mKeyUp)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPdownTAX");
				mState = eState::hupdowning;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftUPdownTAX");
				mState = eState::hupdowning;
			}
			mKeyUp = false;
			return;
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPdownTAX");
				mState = eState::hupdowning;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftUPdownTAX");
				mState = eState::hupdowning;
			}
			return;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownTAX");
					mHeavyBullet = 0.0f;
					mState = eState::Down;
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownTAX");
					mHeavyBullet = 0.0f;
					mState = eState::Down;
				}
				return;
			}
		}

		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPidleTAX", true);
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftUPidleTAX", true);
			}

		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightUPidleTAX", true);
			mState = eState::Up;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayerleftUPidleTAX", true);
			mState = eState::Up;
			return;
		}

		if (Input::GetKey(eKeyCode::UP)
			&& Input::GetKeyDown(eKeyCode::S))
		{
			mState = eState::jumpup;
			return;
		}


		if (Input::GetKey(eKeyCode::A))
		{
			if (mHeavyBullettime>=0.2f)
			{
				if (mDirect)
				{
					CreatHeavyBullet(mDirect, mHeavyBullet);
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerrightUPgunTAX");
				}
				else
				{
					CreatHeavyBullet(mDirect, mHeavyBullet);
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerleftUPgunTAX");
				}
				mHeavyBullettime = 0.0f;
				return;
			}
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::Up);
			return;
		}

	}
	void PlayerTop::HUping()
	{
		Animator* animator = GetComponent<Animator>();
		int index = animator->GetIndex();
		mHeavyBullet += Time::DeltaTime();
		if (mHeavyBullet >= 0.21f)
			mHeavyBullet = 0.21f;
		if (Input::GetKeyUp(eKeyCode::UP))
		{
			mKeyUp = true;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownTAX");
					mState = eState::Down;
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownTAX");
					mState = eState::Down;
				}
				mHeavyBullet = 0.0f;
				return;
			}
		}
		if (mHeavyBullet == 0.21f||animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPidleTAX", true);

			}
			if (!mDirect)
			{
				animator->PlayAnimation(L"hPlayerleftUPidleTAX", true);

			}
			mState = eState::Up;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightUPTAX", true);
			animator->SetIndex(index);
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayertUPTAX", true);
			animator->SetIndex(index);
		}

		if (Input::GetKey(eKeyCode::UP)
			&& Input::GetKeyDown(eKeyCode::S))
		{
			mState = eState::jumpup;
			return;
		}


		if (Input::GetKey(eKeyCode::A))
		{
			if (mDirect)
			{
				CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 0.0f));
				if (!mHeavyBulletCount)
					return;
				animator->PlayAnimation(L"hPlayerrightUPingattackTAX");
				animator->SetIndex(index);
			}
			else
			{
				CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 0.0f));
				if (!mHeavyBulletCount)
					return;
				animator->PlayAnimation(L"hPlayerleftUPingattackTAX");
				animator->SetIndex(index);
			}
			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::Up);
			return;
		}
	}
	void PlayerTop::HUpDowning()
	{
		Animator* animator = GetComponent<Animator>();
		int index = animator->GetIndex();
		mHeavyBullet -= Time::DeltaTime();
		if (mHeavyBullet <= 0.0f)
			mHeavyBullet = 0.0f;
	
		
		if (mHeavyBullet == 0.0f
			||animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);

			}
			if (!mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);

			}
			mHeavyBullet = 0.0f;
			mState = eState::Idle;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightUPdownTAX", true);
			animator->SetIndex(index);
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayerleftUPdownTAX", true);
			animator->SetIndex(index);
		}

		if (Input::GetKey(eKeyCode::UP)
			&& Input::GetKeyDown(eKeyCode::S))
		{
			mState = eState::jumpup;
			return;
		}
	

		if (Input::GetKey(eKeyCode::A))
		{
			if (mDirect)
			{
				CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 0.0f));
				if (!mHeavyBulletCount)
					return;
				animator->PlayAnimation(L"hPlayerrightUPdowningattackTAX");
				animator->SetIndex(index);
			}
			else
			{
				CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 0.0f));
				if (!mHeavyBulletCount)
					return;
				animator->PlayAnimation(L"hPlayerleftUPdowningattackTAX");
				animator->SetIndex(index);
			}
			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::Idle);
			return;
		}
	}
	void PlayerTop::HJumpDown()
	{
		Animator* animator = GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::RIGHT))
			mLateDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mLateDirect = false;
		mHeavyBullet = 0.21f;
		if (mKeyUp == true)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownupTAX");
				mState = eState::hjumpdownuping;

			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftjumpdownupTAX");
				mState = eState::hjumpdownuping;
			}
		}
		if (Input::GetKey(eKeyCode::A))
		{
			if(mHeavyBullettime >=0.2f)
			{
				if (mDirect)
				{
					CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 200.0f), true);
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerrightjumpdowngunTAX");
				}
				else
				{
					CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(0.0f, 200.0f), true);
					if (!mHeavyBulletCount)
						return;
					animator->PlayAnimation(L"hPlayerleftjumpdowngunTAX");
				}
				mHeavyBullettime = 0.0f;
			}
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::jumpdown);
		}
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownupTAX");
				mState = eState::hjumpdownuping;

			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftjumpdownupTAX");
				mState = eState::hjumpdownuping;
			}
		}

		if (mbGround)
		{
			if (mLateDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
			mHeavyBullet = 0.0f;
		}
	}
	void PlayerTop::HJumpDowning()
	{
		Animator* animator = GetComponent<Animator>();
		int index = animator->GetIndex();
		mHeavyBullet += Time::DeltaTime();
		if (mHeavyBullet >= 0.21f)
			mHeavyBullet = 0.21f;
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			mKeyUp = true;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mbGround)
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownTAX");
					mState = eState::Down;
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownTAX");
					mState = eState::Down;
				}
				mHeavyBullet = 0.0f;
				return;
			}
		}
		if (mHeavyBullet >= 0.21f || animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownTAX");
				animator->SetIndex(2);
			}
			if (!mDirect)
			{
				animator->PlayAnimation(L"hPlayerleftjumpdownTAX");
				animator->SetIndex(2);
			}
			mState = eState::jumpdown;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightjumpdownTAX");
			animator->SetIndex(index);
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayerleftjumpdownTAX");
			animator->SetIndex(index);
		}


		if (Input::GetKey(eKeyCode::A))
		{
			if (mDirect)
			{
				CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(50.0f, 200.0f),true);
				if (!mHeavyBulletCount)
					return;
				animator->PlayAnimation(L"hPlayerrightdowningattackTAX");
				animator->SetIndex(index);
			}
			else
			{
				CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(-50.0f, 200.0f),true);
				if (!mHeavyBulletCount)
					return;
				animator->PlayAnimation(L"hPlayerleftdowningattackTAX");
				animator->SetIndex(index);
			}
			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::Down);
			return;
		}
	}
	void PlayerTop::HJumpDownUping()
	{
		Animator* animator = GetComponent<Animator>();
		int index = animator->GetIndex();
		mHeavyBullet -= Time::DeltaTime();
		if (mHeavyBullet <= 0.0f)
			mHeavyBullet = 0.0f;

		if (mbGround)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightIdleTAX");
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftIdleTAX");
				mState = eState::Idle;
			}
			mHeavyBullet = 0.0f;
			return;
		}

		if (mHeavyBullet == 0.0f
			|| animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);

			}
			if (!mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);

			}
			mHeavyBullet = 0.0f;
			mState = eState::jump;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightdownupTAX", true);
			animator->SetIndex(index);
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayerleftdownupTAX", true);
			animator->SetIndex(index);
		}

		if (Input::GetKey(eKeyCode::A))
		{
			if (mDirect)
			{
				CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(50.0f, 200.0f),true);
				if (!mHeavyBulletCount)
					return;
				animator->PlayAnimation(L"hPlayerrightdownupTAX");
				animator->SetIndex(index);
			}
			else
			{
				CreatHeavyBullet(mDirect, mHeavyBullet, Vector2(-50.0f, 200.0f),true);
				if (!mHeavyBulletCount)
					return;
				animator->PlayAnimation(L"hPlayerleftdownupTAX");
				animator->SetIndex(index);
			}
			return;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::Idle);
			return;
		}
	}
	void PlayerTop::HJumpAttack()
	{
		Animator* animator = GetComponent<Animator>();
		ptTimecheck += Time::DeltaTime();

		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownTAX");
				mState = eState::jumpdown;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftjumpdownTAX");
				mState = eState::jumpdown;
			};
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPTAX");
				mState = eState::jumpup;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftUPTAX");
				mState = eState::jumpup;
			}
		}

		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::jump);
		}

		if (animator->Getcomplete())
		{

			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::jump;
			}
		}
		if (mbGround)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}
	void PlayerTop::HJumpBomb()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->Getcomplete())
		{

			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::jump;
			}
		}
		if (mbGround)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}
	void PlayerTop::HJumpDownAttack()
	{
		Animator* animator = GetComponent<Animator>();
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
				animator->PlayAnimation(L"hPlayerrightjumpdowngunTAX");
				mState = eState::jumpdownattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y += 70.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Down);
				animator->PlayAnimation(L"hPlayerleftjumpdowngunTAX");
				mState = eState::jumpdownattack;
			}
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::jumpdown);
		}

		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownupTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftjumpdownupTAX");
				mState = eState::jump;
			}
		}
		if (mbGround)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}
	void PlayerTop::HJumpUpAttack()
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
				animator->PlayAnimation(L"hPlayerrightUPgunTAX");
				mState = eState::jumpupattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"hPlayerleftUPgunTAX");
				mState = eState::jumpupattack;
			}
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::jumpup);
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightUPidleTAX", true);
			mState = eState::jumpup;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayerleftUPidleTAX", true);
			mState = eState::jumpup;
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::jump;
			}
		}
		if (mbGround)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}
	void PlayerTop::HJumpUp()
	{
		Animator* animator = GetComponent<Animator>();
		if (animator->Getcomplete())
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPidleTAX", true);

			}
			if (!mDirect)
			{
				animator->PlayAnimation(L"hPlayerleftUPidleTAX", true);

			}
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"hPlayerrightUPidleTAX", true);
			mState = eState::jumpup;
		}
		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"hPlayerleftUPidleTAX", true);
			mState = eState::jumpup;
		}

		if (Input::GetKeyUp(eKeyCode::UP))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightUPdownTAX");
				mState = eState::jump;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftUPdownTAX");
				mState = eState::jump;
			}
		}

		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownTAX");
				mState = eState::jumpdown;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerrightjumpdownTAX");
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
				animator->PlayAnimation(L"hPlayerrightUPgunTAX");
				mState = eState::jumpupattack;
			}
			else
			{
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos.y -= 100.0f;
				sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
				normalbullet->SetState(sbNormalBullet::eBulletState::Up);
				animator->PlayAnimation(L"hPlayerleftUPgunTAX");
				mState = eState::jumpupattack;
			}
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			CreatHEfBomb(eState::jumpup);
		}
		if (mbGround)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerIdlerightTAX", true);
				mState = eState::Idle;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerIdleleftTAX", true);
				mState = eState::Idle;
			}
		}
	}

	void PlayerTop::StopAnimator()
	{
		Animator* at = GetComponent<Animator>();
		if (mWeaponState == eWeaponState::normal)
		{
			if (mDirect)
				at->PlayAnimation(L"PlayerIdlerightTAX",true);
			else
				at->PlayAnimation(L"PlayerIdleleftTAX", true);
		}
		else if (mWeaponState == eWeaponState::heavy)
		{
			if (mDirect)
				at->PlayAnimation(L"hPlayerIdlerightTAX", true);
			else
				at->PlayAnimation(L"hPlayerIdleleftTAX", true);
		}
		mState = eState::Stop;
	}

	void PlayerTop::Stop()
	{
	}

	void PlayerTop::Victory()
	{
		mVictory = true;
	}

	void PlayerTop::GetPlayerBottomState()
	{
		PlayerBottom* playerbottom = static_cast<PlayerBottom*>(mPlayerBottomOwner);
		Animator* at = this->GetComponent<Animator>();
		mDirect = playerbottom->GetDirect();
		mbGround = playerbottom->Getground();
		if(playerbottom->GetChange())
		{
			if (playerbottom->GetWeaponState() == PlayerBottom::eWeaponState::normal)
			{
				mWeaponState = eWeaponState::normal;
				{
					if(mDirect)
						at->PlayAnimation(L"PlayerIdlerightTAX",true);
					else
						at->PlayAnimation(L"PlayerIdleleftTAX",true);

					mHeavyBulletCount = false;
					mState = eState::Idle;
					playerbottom->SetChange(false);
					
				}
			}
			else if (playerbottom->GetWeaponState() == PlayerBottom::eWeaponState::heavy)
			{
				mWeaponState = eWeaponState::heavy;
				{
					if (mDirect)
						at->PlayAnimation(L"hPlayerIdlerightTAX",true);
					else
						at->PlayAnimation(L"hPlayerIdleleftTAX",true);

					mHeavyBulletCount = true;
					mState = eState::Idle;
					playerbottom->SetChange(false);

				}
			}
		}
		if (playerbottom->GetState() == PlayerBottom::eState::Death)
		{
			if (mState != eState::Death)
			{
				at->PlayAnimation(L"PlayerdeadTAX");
				mState = eState::Death;
			}
		}

		if (playerbottom->GetStopState() == true
			&& mState != eState::StopAnimator
			&& mState != eState::Stop)
		{
			mState = eState::StopAnimator;
		}
		if (mState == eState::Stop
			&& playerbottom->GetStopState() == false)
			mState = eState::Idle;
		mRide = playerbottom->GetRide();
		if (playerbottom->GetVictory() == true
			&& mVictory == false)
		{
			at->PlayAnimation(L"PlayerreviveTAX");
			mState = eState::Victory;
		}
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = playerbottom->GetPlayerPosition();
		pos.y = pos.y - 30.0f;
		tr->SetPosition(pos);
	}

	void PlayerTop::Revive()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			at->PlayAnimation(L"PlayerIdlerightTAX",true);
			Clear();
		}
	}

	void PlayerTop::Clear()
	{
		mDirect = true;
		mKeyUp = false;
		mLateDirect = true;
		ptTimecheck = 0.0f;
		mWeaponState = eWeaponState::normal;
		mHeavyBullet = 0.0f;
		mHeavyBullettime = 0.0f;
		mState = eState::Idle;
	}

	void PlayerTop::CreatHeavyBullet(bool Direct, float mheavybullet, math::Vector2 offset, bool Down)
	{
		if (mRide)
			return;
		PlayerBottom* playerbottom = static_cast<PlayerBottom*>(mPlayerBottomOwner);
		if (mheavybullet == 0.0f)
		{
			for (int i = 0; i < 3; i++)
			{
				playerbottom->SetHeavyBulletCount(-1);
				if (playerbottom->GetHeavyBulletCount() == 0)
				{
					mHeavyBulletCount = false;
					return;
				}
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos += offset;
				float degree = mheavybullet * 428.57f;
				if (Direct == true)
					pos = BulletRotate(pos, degree, 30.0f, Direct);
				else
					pos = BulletRotate(pos, degree, -30.0f, Direct);
				if (Direct)
				{
					if (i == 0)
					{
						pos.x += 150.0f;
					}
					else if (i == 1)
					{
						pos.x += 70.0f;
						pos.y -= 20.0f;
					}
					else if (i == 2)
					{
						pos.y -= 20.0f;
						pos.y += 20.0f;
					}
				}
				else
				{
					if (i == 0)
					{
						pos.x -= 150.0f;
					}
					else if (i == 1)
					{
						pos.x -= 70.0f;
						pos.y -= 20.0f;
					}
					else if (i == 2)
					{
						pos.x += 20.0f;
						pos.y += 20.0f;
					}
				}
				HeavyBullet* heavybullet = object::Instantiate<HeavyBullet>(eLayerType::Effects, pos);
				heavybullet->SetDegree(degree);
				heavybullet->SetDirect(Direct);
				heavybullet->SetDown(Down);
			}
		}

		else if (mheavybullet > 0.0f && mheavybullet < 0.21f)
		{
			playerbottom->SetHeavyBulletCount(-1);
			if (playerbottom->GetHeavyBulletCount() == 0)
			{
				mHeavyBulletCount = false;
				return;
			}
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos += offset;
			float degree = mheavybullet * 428.57f;
			if (Direct == true)
				pos = BulletRotate(pos, degree, 30.0f, Direct);
			else
				pos = BulletRotate(pos, degree, -30.0f, Direct);
			HeavyBullet* heavybullet = object::Instantiate<HeavyBullet>(eLayerType::Effects, pos);
			heavybullet->SetDegree(degree);
			heavybullet->SetDirect(Direct);
			heavybullet->SetDown(Down);
		}
		else if (mheavybullet == 0.21f)
		{
			for (int i = 0; i < 3; i++)
			{
				playerbottom->SetHeavyBulletCount(-1);
				if (playerbottom->GetHeavyBulletCount() == 0)
				{
					mHeavyBulletCount = false;
					return;
				}
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPosition();
				pos += offset;
				float degree = mheavybullet * 428.57f;
				if (Direct == true)
					pos = BulletRotate(pos, degree, 30.0f, Direct);
				else
					pos = BulletRotate(pos, degree, -30.0f, Direct);
				if (Down)
				{
					if (i == 0)
					{
						pos.y += 70.0f;
					}
					else if (i == 1)
					{
						pos.x += 10.0f;
						pos.y += 20.0f;
					}
					else if (i == 2)
					{
						pos.x -= 10.0f;

					}
				}
				else
				{
					if (i == 0)
					{
						pos.y -= 70.0f;
					}
					else if (i == 1)
					{
						pos.x += 10.0f;
						
					}
					else if (i == 2)
					{
						pos.y += 40.0f;
						pos.x -= 10.0f;

					}
				}
				HeavyBullet* heavybullet = object::Instantiate<HeavyBullet>(eLayerType::Effects, pos);
				heavybullet->SetDegree(degree);
				heavybullet->SetDirect(Direct);
				heavybullet->SetDown(Down);
			}
		}
		
	}

	void PlayerTop::CreatEfBomb(eState state)
	{
		Animator* animator = GetComponent<Animator>();
		PlayerBottom* playerbottom = dynamic_cast<PlayerBottom*>(mPlayerBottomOwner);
		if (playerbottom->GetEfBombCount() <= 0)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"PlayerrightbombTAX");
				mState = state;
			}
			else
			{
				animator->PlayAnimation(L"PlayerleftbombTAX");
				mState = state;
			}
			return;
		}
		playerbottom->SetEfBombCount(-1);

		if (mDirect)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x += 30.0f;
			EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
			efbomb->SetDirect(mDirect);
			animator->PlayAnimation(L"PlayerrightbombTAX");
			mState = state;
		}
		else
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x -= 50.0f;
			EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
			efbomb->SetDirect(mDirect);
			animator->PlayAnimation(L"PlayerleftbombTAX");
			mState = state;
		}
	}

	void PlayerTop::CreatHEfBomb(eState state)
	{
		Animator* animator = GetComponent<Animator>();
		PlayerBottom* playerbottom = dynamic_cast<PlayerBottom*>(mPlayerBottomOwner);
		if (playerbottom->GetEfBombCount() <= 0)
		{
			if (mDirect)
			{
				animator->PlayAnimation(L"hPlayerrightbombTAX");
				mState = state;
			}
			else
			{
				animator->PlayAnimation(L"hPlayerleftbombTAX");
				mState = state;
			}
			return;
		}
		playerbottom->SetEfBombCount(-1);
		if (mDirect)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x += 30.0f;
			EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
			efbomb->SetDirect(mDirect);
			animator->PlayAnimation(L"hPlayerrightbombTAX");
			mState = state;
		}
		else
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x -= 50.0f;
			EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
			efbomb->SetDirect(mDirect);
			animator->PlayAnimation(L"hPlayerleftbombTAX");
			mState = state;
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
		at->CreateAnimation(L"hPlayerIdlerightTAX", imagePlayer, Vector2(0.0f, 1936.0f), Vector2(44.0f, 44.0f), 4, Vector2(20.0f, 11.0f));
		at->CreateAnimation(L"hPlayerIdleleftTAX", imagePlayer, Vector2(176.0f, 1936.0f), Vector2(44.0f, 44.0f), 4, Vector2(-35.0f, 11.0f));
		at->CreateAnimation(L"hPlayerrightTAX", imagePlayer, Vector2(0.0f, 1980.0f), Vector2(44.0f, 44.0f), 6, Vector2(5.0f, 11.0f),0.05f);
		at->CreateAnimation(L"hPlayerleftTAX", imagePlayer, Vector2(264.0f, 1980.0f), Vector2(44.0f, 44.0f), 6, Vector2(-13.0f, 11.0f),0.05f);
		at->CreateAnimation(L"hPlayerrightgunTAX", imagePlayer, Vector2(0.0f, 2024.0f), Vector2(88.0f, 44.0f), 4, Vector2(30.0f, 8.0f),0.01f);
		at->CreateAnimation(L"hPlayerleftgunTAX", imagePlayer, Vector2(352.0f, 2024.0f), Vector2(88.0f, 44.0f), 4, Vector2(-40.0f, 8.0f), 0.01f);
		at->CreateAnimation(L"hPlayerrightbombTAX", imagePlayer, Vector2(0.0f, 2068.0f), Vector2(88.0f, 44.0f), 6, Vector2(25.0f, 9.0f), 0.001f);
		at->CreateAnimation(L"hPlayerleftbombTAX", imagePlayer, Vector2(528.0f, 2068.0f), Vector2(88.0f, 44.0f), 6, Vector2(-35.0f, 9.0f), 0.001f); 
		at->CreateAnimation(L"hPlayerrightknifeTAX", imagePlayer, Vector2(0.0f, 2112.0f), Vector2(88.0f, 88.0f), 6, Vector2(-8.0f, 5.0f), 0.001f);
		at->CreateAnimation(L"hPlayerleftknifeTAX", imagePlayer, Vector2(528.0f, 2112.0f), Vector2(88.0f, 88.0f), 6, Vector2(5.0f, 5.0f), 0.001f);
		at->CreateAnimation(L"hPlayerrightUPTAX", imagePlayer, Vector2(0.0f, 2200.0f), Vector2(88.0f, 88.0f), 2, Vector2(3.0f, 10.0f));
		at->CreateAnimation(L"hPlayerleftUPTAX", imagePlayer, Vector2(176.0f, 2200.0f), Vector2(88.0f, 88.0f), 2, Vector2(-15.0f, 10.0f)); 
		at->CreateAnimation(L"hPlayerrightUPidleTAX", imagePlayer, Vector2(0.0f, 2288.0f), Vector2(44.0f, 44.0f), 4, Vector2(0.0f, -20.0f));
		at->CreateAnimation(L"hPlayerleftUPidleTAX", imagePlayer, Vector2(176.0f, 2288.0f), Vector2(44.0f, 44.0f), 4, Vector2(-5.0f, -20.0f)); 
		at->CreateAnimation(L"hPlayerrightUPingattackTAX", imagePlayer, Vector2(0.0f, 2332.0f), Vector2(88.0f, 88.0f), 2, Vector2(0.0f, -20.0f));
		at->CreateAnimation(L"hPlayerleftUPingattackTAX", imagePlayer, Vector2(352.0f, 2332.0f), Vector2(88.0f, 88.0f), 2, Vector2(-10.0f, -20.0f));
		at->CreateAnimation(L"hPlayerrightUPdowningattackTAX", imagePlayer, Vector2(176.0f, 2332.0f), Vector2(88.0f, 88.0f), 2, Vector2(0.0f, -20.0f));
		at->CreateAnimation(L"hPlayerleftUPdowningattackTAX", imagePlayer, Vector2(528.0f, 2332.0f), Vector2(88.0f, 88.0f), 2, Vector2(-10.0f, -20.0f));
		at->CreateAnimation(L"hPlayerrightUPdownTAX", imagePlayer, Vector2(352.0f, 2200.0f), Vector2(88.0f, 88.0f), 2, Vector2(3.0f, 10.0f));
		at->CreateAnimation(L"hPlayerleftUPdownTAX", imagePlayer, Vector2(528.0f, 2200.0f), Vector2(88.0f, 88.0f), 2, Vector2(-15.0f, 10.0f));
		at->CreateAnimation(L"hPlayerrightUPgunTAX", imagePlayer, Vector2(0.0f, 2420.0f), Vector2(88.0f, 88.0f), 10, Vector2(-15.0f, -68.0f),0.01f);
		at->CreateAnimation(L"hPlayerleftUPgunTAX", imagePlayer, Vector2(0.0f, 2508.0f), Vector2(88.0f, 88.0f), 10, Vector2(0.0f, -68.0f),0.01f);
		at->CreateAnimation(L"hPlayerrightjumpdownTAX", imagePlayer, Vector2(0.0f, 2596.0f), Vector2(44.0f, 44.0f), 3, Vector2(-5.0f, 45.0f));
		at->CreateAnimation(L"hPlayerleftjumpdownTAX", imagePlayer, Vector2(132.0f, 2596.0f), Vector2(44.0f, 44.0f), 3, Vector2(-5.0f, 45.0f));
		at->CreateAnimation(L"hPlayerrightjumpdownupTAX", imagePlayer, Vector2(264.0f, 2596.0f), Vector2(44.0f, 44.0f), 3, Vector2(-5.0f, 45.0f));
		at->CreateAnimation(L"hPlayerleftjumpdownupTAX", imagePlayer, Vector2(396.0f, 2596.0f), Vector2(44.0f, 44.0f), 3, Vector2(-5.0f, 45.0f));
		at->CreateAnimation(L"hPlayerrightjumpdowngunTAX", imagePlayer, Vector2(0.0f, 2640.0f), Vector2(44.0f, 88.0f), 4, Vector2(-10.0f, 50.0f),0.01f);
		at->CreateAnimation(L"hPlayerleftjumpdowngunTAX", imagePlayer, Vector2(176.0f, 2640.0f), Vector2(44.0f, 88.0f), 4, Vector2(5.0f, 50.0f),0.01f);
		at->CreateAnimation(L"hPlayerrightdowningattackTAX", imagePlayer, Vector2(0.0f, 2728.0f), Vector2(88.0f, 88.0f), 2, Vector2(-5.0f, 20.0f));
		at->CreateAnimation(L"hPlayerrightdownupTAX", imagePlayer, Vector2(176.0f, 2728.0f), Vector2(88.0f, 88.0f), 2, Vector2(-5.0f, 20.0f));
		at->CreateAnimation(L"hPlayerleftdowningattackTAX", imagePlayer, Vector2(352.0f, 2728.0f), Vector2(88.0f, 88.0f), 2, Vector2(-10.0f, 20.0f));
		at->CreateAnimation(L"hPlayerleftdownupTAX", imagePlayer, Vector2(528.0f, 2728.0f), Vector2(88.0f, 88.0f), 2, Vector2(-10.0f, 20.0f));		
		at->CreateAnimation(L"hPlayerrightdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);
		at->CreateAnimation(L"hPlayerleftdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f); 
		at->CreateAnimation(L"hPlayerrightjumpTAX", imagePlayer, Vector2(0.0f, 3212.0f), Vector2(44.0f, 44.0f), 6, Vector2(10.0f, 20.0f),0.2f);
		at->CreateAnimation(L"hPlayerleftjumpTAX", imagePlayer, Vector2(264.0f, 3212.0f), Vector2(44.0f, 44.0f), 6, Vector2(-13.0f, 20.0f),0.2f);
		at->CreateAnimation(L"PlayerreviveTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 1, Vector2(-13.0f, 20.0f));
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"PlayerIdlerightTAX", true);

	}
}