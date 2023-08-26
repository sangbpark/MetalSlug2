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
#include "sbHeavyBullet.h"
#include "sbArabianknife.h"
#include "sbMiddleBossRocket.h"
#include "sbBerserkerKnife.h"
#include "sbCamel.h"
#include "sbCollisionManager.h"
#include "sbBossWing.h"
#include "sbHeavyMachineGun.h"


namespace sb
{
	math::Vector2 PlayerBottom::mPlayposition = {};
	PlayerBottom::PlayerBottom()
		: mKeyUp(false)
		, mRun(false)
		, mFree(false)
		, mLateDirect(true)
		, PBtimecheck(0.0f)
		, mInvincible(0.0f)
		, mDirect(true)
		, mChange(false)
		, mState(eState::Idle)
		, mWeaponState(eWeaponState::normal)
		, mHeavyBulletCount(0)
		, mEfBombCount(10)
		, mStop(false)
		, mRide(false)
		, mVictory(false)
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
		case sb::PlayerBottom::eState::Stopanimator:
			StopAnimator();
			break;
		case sb::PlayerBottom::eState::Stop:
			Stop();
			break;
		case sb::PlayerBottom::eState::Downmove:
			DownMove();
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
		case sb::PlayerBottom::eState::jumpbomb:
			JumpBomb();
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
		case sb::PlayerBottom::eState::revive:
			Revive();
			break;
		case sb::PlayerBottom::eState::RIde:
			Ride();
			break;
		case sb::PlayerBottom::eState::End:
			break;
		case sb::PlayerBottom::eState::Victory:
			Victory();
			break;
		case sb::PlayerBottom::eState::RideVictory:
			RideVictory();
			break;
		default:
			break;
		}
		if (mInvincible != 0.0f)
		{
			mInvincible -= Time::DeltaTime();
			if (mInvincible < 0.0f)
				mInvincible = 0.0f;
		}
	
		Vector2 pos = tr->GetPosition();
		mGround = rb->GetGround();
		mPlayposition = pos;
		mComplete = animator->Getcomplete();
		if(mWeaponState ==eWeaponState::heavy)
		{
			if (mHeavyBulletCount == 0)
			{
				mWeaponState = eWeaponState::normal;
				mChange = true;
			}
		}
		if (mState != eState::Stop
			&& mState != eState::Stopanimator)
		{
			if (mStop == true)
				mState = eState::Stopanimator;
		}


	}
	void PlayerBottom::Render(HDC hdc)
	{
			GameObject::Render(hdc);
	}

	void PlayerBottom::OnCollisionEnter(Collider* other)
	{
		if(mInvincible==0.0f)
		{
			ArabianKnifeColliderEnter(other);
			MiddleRocketColliderEnter(other);
			BerserkerKnifeColliderEnter(other);
			BossWingColliderEnter(other);
		}
	}
	void PlayerBottom::OnCollisionStay(Collider* other)
	{
	}
	void PlayerBottom::OnCollisionExit(Collider* other)
	{
	}

	void PlayerBottom::ArabianKnifeColliderEnter(Collider* other)
	{
		Arabianknife* af = dynamic_cast<Arabianknife*>(other->GetOwner());
		if (af == nullptr)
			return;
		if (mState == eState::Death
			|| mState == eState::revive)
			return;
		Animator* animator = this->GetComponent<Animator>();
		if (mRide)
		{
			mRide = false;
			Rigidbody* rb = GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
		animator->PlayAnimation(L"PlayerdeadBAX");
		this->mState = eState::Death;
	}

	void PlayerBottom::MiddleRocketColliderEnter(Collider* other)
	{
		MiddleBossRocket* mr = dynamic_cast<MiddleBossRocket*>(other->GetOwner());
		if (mr == nullptr
			|| mState == eState::Death
			|| mState == eState::revive
			|| mr->GetMiddleRocketDeath() == true )
			return;

		Animator* animator = this->GetComponent<Animator>();
		if (mRide)
		{
			mRide = false;
			Rigidbody* rb = GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
		animator->PlayAnimation(L"PlayerdeadBAX");
		this->mState = eState::Death;
	}

	void PlayerBottom::BerserkerKnifeColliderEnter(Collider* other)
	{
		BerserkerKnife* bf = dynamic_cast<BerserkerKnife*>(other->GetOwner());
		if (bf == nullptr)
			return;
		if (mState == eState::Death
			|| mState == eState::revive)
			return;
		Animator* animator = this->GetComponent<Animator>();
		if (mRide)
		{
			mRide = false;
			Rigidbody* rb = GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
		animator->PlayAnimation(L"PlayerdeadBAX");
		this->mState = eState::Death;
	}

	void PlayerBottom::BossWingColliderEnter(Collider* other)
	{
		BossWing* bw = dynamic_cast<BossWing*>(other->GetOwner());
		if (bw == nullptr)
			return;
		if (mState == eState::Death
			|| mState == eState::revive)
			return;
		Animator* animator = this->GetComponent<Animator>();
		if (mRide)
		{
			mRide = false;
			Rigidbody* rb = GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
		animator->PlayAnimation(L"PlayerdeadBAX");
		this->mState = eState::Death;
	}

	void PlayerBottom::Idle()
	{
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"PlayerrightBAX", true);
			mState = eState::Move;
			mDirect = true;
			return;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"PlayerleftBAX", true);
			mState = eState::Move;
			mDirect = false;
			return;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (rb->GetGround())
			{
				if (mWeaponState == eWeaponState::normal)
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
				else if (mWeaponState == eWeaponState::heavy)
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"hPlayerrightdownBAX");
						mState = eState::Down;
					}
					else
					{
						animator->PlayAnimation(L"hPlayerleftdownBAX");
						mState = eState::Down;
					}
				}
				return;
			}
		}
		if (Input::GetKeyDown(eKeyCode::A))
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
		Rigidbody* rb = GetComponent<Rigidbody>();
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
			}

		if (Input::GetKey(eKeyCode::LEFT))
			{
				pos.x -= Player_Speed * Time::DeltaTime();
			}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			if (rb->GetGround())
			{
				if (mWeaponState == eWeaponState::normal)
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
				else if (mWeaponState == eWeaponState::heavy)
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"hPlayerrightdownBAX");
						mState = eState::Down;
					}
					else
					{
						animator->PlayAnimation(L"hPlayerleftdownBAX");
						mState = eState::Down;
					}
				}
				return;
			}
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
		pos = CameraOut(pos);
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
		pos = CameraOut(pos);
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
		pos = CameraOut(pos);
		tr->SetPosition(pos);
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mState = eState::jumpdown;
			return;
		}
		if (Input::GetKeyDown(eKeyCode::A))
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
		if (Input::GetKeyDown(eKeyCode::D))
		{
			PBtimecheck = 0.0f;
			int Index = (animator->GetIndex());
			if (mRun)
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightrunjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpbomb;
				}
				else
				{

					animator->PlayAnimation(L"PlayerleftrunjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpbomb;
				}
			}

			else
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpbomb;
				}
				else
				{
					animator->PlayAnimation(L"PlayerleftjumpBAX");
					animator->SetIndex(Index);
					mState = eState::jumpbomb;
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
		if (mWeaponState == eWeaponState::normal)
		{
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
				animator->PlayAnimation(L"PlayerleftdownwalkBAX", true);
				mState = eState::Downmove;
				mDirect = false;
				return;
			}
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				animator->PlayAnimation(L"PlayerrightdownwalkBAX", true);
				mState = eState::Downmove;
				mDirect = true;
				return;
			}

			if (Input::GetKeyDown(eKeyCode::D))
			{
		
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x += 30.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos2);
					efbomb->SetDirect(mDirect);
				
				}
				else
				{
					animator->PlayAnimation(L"PlayerleftdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x -= 50.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos2);
					efbomb->SetDirect(mDirect);
				}
				return;
			}
			if (Input::GetKeyDown(eKeyCode::A))
			{
				if (mDirect)
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x += 30.0f;
					sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos2);
					normalbullet->SetState(sbNormalBullet::eBulletState::Right);
					animator->PlayAnimation(L"PlayerrightdowngunBAX");
					mState = eState::Downattack;
				}
				else
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x -= 40.0f;
					sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos2);
					normalbullet->SetState(sbNormalBullet::eBulletState::Left);
					animator->PlayAnimation(L"PlayerleftdowngunBAX");
					mState = eState::Downattack;
				}
				return;
			}
		}
		else if (mWeaponState == eWeaponState::heavy)
		{
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
			if (animator->Getcomplete())
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownidleBAX", true);
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownidleBAX", true);
				}
			}
			if (Input::GetKey(eKeyCode::LEFT))
			{
				animator->PlayAnimation(L"hPlayerleftdownwalkBAX", true);
				mState = eState::Downmove;
				mDirect = false;
				return;
			}
			if (Input::GetKey(eKeyCode::RIGHT))
			{
				animator->PlayAnimation(L"hPlayerrightdownwalkBAX", true);
				mState = eState::Downmove;
				mDirect = true;
				return;
			}

			if (Input::GetKeyDown(eKeyCode::D))
			{
		
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x += 30.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos2);
					efbomb->SetDirect(mDirect);
		
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x -= 50.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos2);
					efbomb->SetDirect(mDirect);
				}
				return;
			}
			if (Input::GetKeyDown(eKeyCode::A))
			{
				if (mHeavyBulletCount <= 0)
					return;		
				mHeavyBulletCount -= 1;
				if (mDirect)
				{
				
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x += 30.0f;
					HeavyBullet* heavybullet = object::Instantiate<HeavyBullet>(eLayerType::Effects, pos2);
					heavybullet->SetDirect(mDirect);
					animator->PlayAnimation(L"hPlayerrightdowngunBAX");
				}
				else
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x -= 40.0f;
					HeavyBullet* heavybullet = object::Instantiate<HeavyBullet>(eLayerType::Effects, pos2);
					heavybullet->SetDirect(mDirect);
					animator->PlayAnimation(L"hPlayerleftdowngunBAX");
				}
				return;
			}
		}
	
	}
	void PlayerBottom::DownMove()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();
		Vector2 pos = tr->GetPosition();
		if (mWeaponState == eWeaponState::normal)
		{
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

			if (Input::GetKey(eKeyCode::LEFT))
			{
				pos.x -= Player_DownSpeed * Time::DeltaTime();

			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				pos.x += Player_DownSpeed * Time::DeltaTime();
			}
			pos = CameraOut(pos);
			tr->SetPosition(pos);

			if (Input::GetKeyDown(eKeyCode::D))
			{
				
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x += 30.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos2);
					efbomb->SetDirect(mDirect);
				}
				else
				{
					animator->PlayAnimation(L"PlayerleftdownbombBAX");
					mState = eState::DownBomb;
					animator->PlayAnimation(L"PlayerrightdownbombBAX");
					mState = eState::DownBomb;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x -= 50.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos2);
					efbomb->SetDirect(mDirect);
				}
				return;
			}
			if (Input::GetKeyDown(eKeyCode::A))
			{
				if (mDirect)
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x += 30.0f;
					sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos2);
					normalbullet->SetState(sbNormalBullet::eBulletState::Right);
					animator->PlayAnimation(L"PlayerrightdowngunBAX");
					mState = eState::Downattack;
				}
				else
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x -= 40.0f;
					sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos2);
					normalbullet->SetState(sbNormalBullet::eBulletState::Left);
					animator->PlayAnimation(L"PlayerleftdowngunBAX");
					mState = eState::Downattack;
				}
				return;
			}
		}
		else if (mWeaponState == eWeaponState::heavy)
		{
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
			if (Input::GetKeyDown(eKeyCode::A))
			{
				if (mHeavyBulletCount <= 0)
					return;
				mHeavyBulletCount -= 1;
				if (mDirect)
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x += 30.0f;
					HeavyBullet* heavybullet = object::Instantiate<HeavyBullet>(eLayerType::Effects, pos2);
					heavybullet->SetDirect(mDirect);
					animator->PlayAnimation(L"hPlayerrightdowngunBAX");
					mState = eState::Down;
				}
				else
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x -= 40.0f;
					HeavyBullet* heavybullet = object::Instantiate<HeavyBullet>(eLayerType::Effects, pos2);
					heavybullet->SetDirect(mDirect);
					animator->PlayAnimation(L"hPlayerleftdowngunBAX");
					mState = eState::Down;
				}
				return;
			}
			if (Input::GetKeyUp(eKeyCode::LEFT)
				|| Input::GetKeyUp(eKeyCode::RIGHT))
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownidleBAX", true);
					mState = eState::Down;
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownidleBAX", true);
					mState = eState::Down;
				}
				return;
			}

			if (Input::GetKey(eKeyCode::LEFT))
			{
				pos.x -= Player_DownSpeed * Time::DeltaTime();

			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				pos.x += Player_DownSpeed * Time::DeltaTime();
			}
			pos = CameraOut(pos);
			tr->SetPosition(pos);

			if (Input::GetKeyDown(eKeyCode::D))
			{
	
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x += 30.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos2);
					efbomb->SetDirect(mDirect);
	
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos2 = tr->GetPosition();
					pos2.x -= 50.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos2);
					efbomb->SetDirect(mDirect);
			
				}
				return;
			}

		}
	}
	void PlayerBottom::DownAttack()
	{
		Animator* animator = GetComponent<Animator>();
		if (mWeaponState== eWeaponState::normal)
		{
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
				return;
			}
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				animator->PlayAnimation(L"PlayerleftdownwalkBAX", true);
				mState = eState::Down;
				mDirect = false;
				return;
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
				return;
			}
			if (Input::GetKeyDown(eKeyCode::D))
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"PlayerrightdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPosition();
					pos.x += 30.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
					efbomb->SetDirect(mDirect);
		
				}
				else
				{
					animator->PlayAnimation(L"PlayerleftdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPosition();
					pos.x -= 50.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
					efbomb->SetDirect(mDirect);
			
				}
				return;
			}
			if (Input::GetKeyUp(eKeyCode::LEFT)
				|| Input::GetKeyUp(eKeyCode::RIGHT))
			{
				mRun = false;
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

			if (animator->Getcomplete())
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
		else if (mWeaponState == eWeaponState::heavy)
		{
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
				animator->PlayAnimation(L"hPlayerrightdownwalkBAX", true);
				mState = eState::Down;
				mDirect = true;
				return;
			}
			if (Input::GetKeyDown(eKeyCode::LEFT))
			{
				animator->PlayAnimation(L"hPlayerleftdownwalkBAX", true);
				mState = eState::Down;
				mDirect = false;
				return;
			}

			if (Input::GetKeyDown(eKeyCode::A)
				&& animator->GetIndex() > 4)
			{
				if (mHeavyBulletCount <= 0)
					return;
				mHeavyBulletCount -= 1;
				if (mDirect)
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPosition();
					pos.x += 30.0f;
					sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
					normalbullet->SetState(sbNormalBullet::eBulletState::Right);
					animator->PlayAnimation(L"hPlayerrightdowngunBAX");
					mState = eState::Downattack;
				}
				else
				{
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPosition();
					pos.x -= 40.0f;
					sbNormalBullet* normalbullet = object::Instantiate<sbNormalBullet>(eLayerType::Effects, pos);
					normalbullet->SetState(sbNormalBullet::eBulletState::Left);
					animator->PlayAnimation(L"hPlayerleftdowngunBAX");
					mState = eState::Downattack;
				}
				return;
			}
			if (Input::GetKeyDown(eKeyCode::D))
			{
				if (mDirect)
				{
					animator->PlayAnimation(L"hPlayerrightdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPosition();
					pos.x += 30.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
					efbomb->SetDirect(mDirect);
				}
				else
				{
					animator->PlayAnimation(L"hPlayerleftdownbombBAX");
					mState = eState::DownBomb;
					if (mEfBombCount <= 0)
					{
						mEfBombCount = 0;
						return;
					}
					mEfBombCount -= 1;
					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPosition();
					pos.x -= 50.0f;
					EfBomb* efbomb = object::Instantiate<EfBomb>(eLayerType::Effects, pos);
					efbomb->SetDirect(mDirect);

				}
				return;
			}
			if (Input::GetKeyUp(eKeyCode::LEFT)
				|| Input::GetKeyUp(eKeyCode::RIGHT))
			{
				mRun = false;
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

			if (animator->Getcomplete())
			{
				if (mRun)
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"hPlayerrightdownwalkBAX", true);
						mState = eState::Down;
						mDirect = true;

					}
					else
					{
						animator->PlayAnimation(L"hPlayerleftdownwalkBAX", true);
						mState = eState::Down;
						mDirect = false;
					}
				}
				else
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"hPlayerrightdownidleBAX", true);
						mState = eState::Down;

					}
					else
					{
						animator->PlayAnimation(L"hPlayerleftdownidleBAX", true);
						mState = eState::Down;

					}
				}
				return;
			}
		}

	}
	void PlayerBottom::DownBomb()
	{
		Animator* animator = GetComponent<Animator>();
		if (mWeaponState == eWeaponState::normal)
		{
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

			if (animator->Getcomplete())
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
		else if (mWeaponState == eWeaponState::heavy)
		{
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

			if (animator->Getcomplete())
			{
				if (mRun)
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"hPlayerrightdownwalkBAX", true);
						mState = eState::Down;
						mDirect = true;
					}
					else
					{
						animator->PlayAnimation(L"hPlayerleftdownwalkBAX", true);
						mState = eState::Down;
						mDirect = false;
					}
					mRun = false;
				}
				else
				{
					if (mDirect)
					{
						animator->PlayAnimation(L"hPlayerrightdownidleBAX", true);
						mState = eState::Down;
					}
					else if (!mDirect)
					{
						animator->PlayAnimation(L"hPlayerleftdownidleBAX", true);
						mState = eState::Down;
					}
				}
				return;
			}
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
		pos = CameraOut(pos);
		tr->SetPosition(pos);

		if (Input::GetKey(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mDirect = false;

		if (PBtimecheck > 0.17f)
		{
			if (Input::GetKey(eKeyCode::A))

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

				return;
			}
		}
		if (PBtimecheck >= 0.358)
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
	void PlayerBottom::JumpBomb()
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
		pos = CameraOut(pos);
		tr->SetPosition(pos);

		if (Input::GetKey(eKeyCode::RIGHT))
			mDirect = true;
		if (Input::GetKey(eKeyCode::LEFT))
			mDirect = false;

		if (PBtimecheck >= 0.21)
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
			pos.x -= Player_Speed * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += Player_Speed * Time::DeltaTime();
		}
		pos = CameraOut(pos);
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
		pos = CameraOut(pos);
		tr->SetPosition(pos);
	}

	void PlayerBottom::Stop()
	{
		if (mStop == false
			&& mRide == false)
			mState = eState::Idle;
		else if (mRide)
		{
			mState = eState::RIde;
		}
	}

	void PlayerBottom::StopAnimator()
	{
		if(mRide == false)
		{
			Animator* at = GetComponent<Animator>();
			if (mWeaponState == eWeaponState::normal)
			{
				if (mDirect)
				{
					at->PlayAnimation(L"PlayerIdlerightBAX", true);
				}
				else
				{
					at->PlayAnimation(L"PlayerIdleleftBAX", true);
				}
			}
			else if (mWeaponState == eWeaponState::heavy)
			{
				if (mDirect)
				{
					at->PlayAnimation(L"PlayerIdlerightBAX", true);
				}
				else
				{
					at->PlayAnimation(L"PlayerIdleleftBAX", true);
				}
			}
		}
		mState = eState::Stop;
	}

	void PlayerBottom::Ride()
	{

		Transform* tr = GetComponent<Transform>();
		Transform* Vehicltr = mVehicle->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += Player_Speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= Player_Speed * Time::DeltaTime();
		}
		Vector2 pos2 = Vehicltr->GetPosition();
		pos.y = pos2.y - 90.0f;
		pos = CameraOut(pos);
		tr->SetPosition(pos);
	}

	void PlayerBottom::Victory()
	{
	}

	void PlayerBottom::VictoryOn()
	{
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"PlayervitoryBAX", true);
		mState = eState::Victory;
		mVictory = true;
	}

	void PlayerBottom::RideVictory0n()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGround(false);
		if (mDirect)
			at->PlayAnimation(L"PlayerrightjumpBAX");
		else
			at->PlayAnimation(L"PlayerleftjumpBAX");
		mRide = false;
		mState = eState::RideVictory;
	}

	void PlayerBottom::RideVictory()
	{
		Animator* at = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		if(rb->GetGround())
		{
			at->PlayAnimation(L"PlayervitoryBAX", true);
			mState = eState::Victory;
			mVictory = true;
		}
	}

	void PlayerBottom::RideOn()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGround(true);
		at->PlayAnimation(L"PlayerIdlerideAX");
		mState = eState::RIde;

	}

	void PlayerBottom::RideOff()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Rigidbody* rb = GetComponent<Rigidbody>();
		rb->SetGround(false);
		if(mDirect)
			at->PlayAnimation(L"PlayerrightjumpBAX");
		else
			at->PlayAnimation(L"PlayerleftjumpBAX");
		mRide = false;
		mState = eState::jump;
	}

	void PlayerBottom::Revive()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			at->PlayAnimation(L"PlayerIdlerightBAX");
			Clear();
			mInvincible = 5.0f;
		}
	
	}

	void PlayerBottom::Clear()
	{
		mKeyUp = false;
		mRun = false;
		mFree = false;
		mLateDirect = true;
		PBtimecheck = 0.0f;
		mDirect = true;
		mState = eState::Idle;
		mHeavyBulletCount = 0;
		mWeaponState = eWeaponState::normal;
	}
	
	void PlayerBottom::Death()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x += 100.0f;
			HeavyMachineGun* hmg = object::Instantiate<HeavyMachineGun>(eLayerType::Effects, pos);
			at->PlayAnimation(L"PlayerreviveBAX");
			mState = eState::revive;
		}
	}
	void PlayerBottom::ResourceLoad()
	{
		Texture* imagePlayer = Resources::Load<Texture>(L"Player"
			, L"..\\Resource\\Character\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Marco Rossi.bmp");
		Animator* at = this->AddComponent<Animator>();
		Rigidbody* rb = this->AddComponent<Rigidbody>();
		Collider* col = this->AddComponent<Collider>();
		Transform* tr = this->AddComponent<Transform>();
		at->CreateAnimation(L"PlayerIdlerideAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 1);
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
		at->CreateAnimation(L"PlayerrightrunjumpBAX", imagePlayer, Vector2(308.0f, 836.0f), Vector2(44.0f, 44.0f), 6, Vector2(-25.0f, -5.0f));
		at->CreateAnimation(L"PlayerleftrunjumpBAX", imagePlayer, Vector2(308.0f, 924.0f), Vector2(44.0f, 44.0f), 6, Vector2(10.0f, -5.0f));
		at->CreateAnimation(L"PlayerrightdowngunBAX", imagePlayer, Vector2(0.0f, 1320.0f), Vector2(88.0f, 44.0f), 10, Vector2(0.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdowngunBAX", imagePlayer, Vector2(0.0f, 1364.0f), Vector2(88.0f, 44.0f), 10, Vector2(0.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightdownbombBAX", imagePlayer, Vector2(0.0f, 1408.0f), Vector2(44.0f, 44.0f), 6, Vector2(0.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"PlayerleftdownbombBAX", imagePlayer, Vector2(264.0f, 1408.0f), Vector2(44.0f, 44.0f), 6, Vector2(0.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"hPlayerrightdownBAX", imagePlayer, Vector2(0.0f, 2816.0f), Vector2(88.0f, 44.0f), 7, Vector2(-8.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"hPlayerleftdownBAX", imagePlayer, Vector2(0.0f, 2860.0f), Vector2(88.0f, 44.0f), 7, Vector2(-8.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"hPlayerrightdownidleBAX", imagePlayer, Vector2(0.0f, 2904.0f), Vector2(88.0f, 44.0f), 4, Vector2(-8.0f, -18.0f));
		at->CreateAnimation(L"hPlayerleftdownidleBAX", imagePlayer, Vector2(0.0f, 2948.0f), Vector2(88.0f, 44.0f), 4, Vector2(-8.0f, -18.0f));
		at->CreateAnimation(L"hPlayerrightdownwalkBAX", imagePlayer, Vector2(0.0f, 2992.0f), Vector2(88.0f, 44.0f), 7, Vector2(-8.0f, -18.0f));
		at->CreateAnimation(L"hPlayerleftdownwalkBAX", imagePlayer, Vector2(0.0f, 3036.0f), Vector2(88.0f, 44.0f), 7, Vector2(-8.0f, -18.0f));
		at->CreateAnimation(L"hPlayerrightdowngunBAX", imagePlayer, Vector2(0.0f, 3080.0f), Vector2(88.0f, 44.0f), 4, Vector2(35.0f, -18.0f));
		at->CreateAnimation(L"hPlayerleftdowngunBAX", imagePlayer, Vector2(352.0f, 3080.0f), Vector2(88.0f, 44.0f), 4, Vector2(-60.0f, -18.0f));
		at->CreateAnimation(L"hPlayerrightdownbombBAX", imagePlayer, Vector2(0.0f, 3124.0f), Vector2(88.0f, 44.0f), 6, Vector2(35.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"hPlayerleftdownbombBAX", imagePlayer, Vector2(528.0f, 3124.0f), Vector2(88.0f, 44.0f), 6, Vector2(-60.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"hPlayerrightdownknifeBAX", imagePlayer, Vector2(0.0f, 3168.0f), Vector2(88.0f, 44.0f), 7, Vector2(35.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"hPlayerleftdownknifeBAX", imagePlayer, Vector2(616.0f, 3168.0f), Vector2(88.0f, 44.0f), 7, Vector2(-60.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"PlayerreviveBAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(44.0f, 264.0f), 7,Vector2(-15.0f, -460.0f));
		at->CreateAnimation(L"PlayervitoryBAX", imagePlayer, Vector2(0.0f, 1628.0f), Vector2(44.0f, 44.0f), 4, Vector2(0.0f, -20.0f));
		at->PlayAnimation(L"PlayerIdlerightBAX", true);
		at->SetScale(Vector2(4.5f, 4.5f));
		col->SetSize(Vector2(100.0f, 160.0f));
		Vector2 pbpos = tr->GetPosition();
		col->SetPosition(pbpos);
	}
	math::Vector2 PlayerBottom::CameraOut(math::Vector2 value)
	{
		float distance = fabs(value.x - mCameraTransform.x);
		float realdistance = value.x - mCameraTransform.x;
		if (distance >= 670.0f)
		{
			if (realdistance > 0.0f)
			{
				value.x = mCameraTransform.x + 670.0f;
			}
			else
				value.x = mCameraTransform.x - 670.0f;
		}
		return value;
	}
}
