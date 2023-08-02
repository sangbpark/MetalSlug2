#include "sbArabian.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbRigidbody.h"
#include "sbNormalBullet.h"
#include "sbEfBomb.h"
#include "sbPlayerBottom.h"

namespace sb
{
	Arabian::Arabian()
		:mState(Arabianstate::idle)
		,mDirect(false)
		,mMoveDistance(0.0f)
		,mPatrolCount(0)
		,mPlayerDistance(0.0f)
		,mTimecheck(0.0f)
	{
		ResourceLoad();
	}
	Arabian::~Arabian()
	{
	}
	void Arabian::Initialize()
	{
	}
	void Arabian::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::Arabian::Arabianstate::idle:
			Idle();
			break;
		case sb::Arabian::Arabianstate::rockon:
			RockOn();
			break;
		case sb::Arabian::Arabianstate::attack:
			Attack();
			break;
		case sb::Arabian::Arabianstate::prepare:
			Prepare();
			break;
		case sb::Arabian::Arabianstate::death:
			Death();
			break;
		case sb::Arabian::Arabianstate::patrol:
			Patrol();
			break;
		default:
			break;
		}
	}
	void Arabian::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Arabian::Idle()
	{
		mTimecheck += Time::DeltaTime();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* ar = GetComponent<Animator>();
		mPlayerDistance = pos.x - PlayerBottom::GetPlayerPosition().x;

		if (mTimecheck > 3.0f)
		{
			if (mDirect)
			{
				ar->PlayAnimation(L"arabianrightmoveAX", true);
			}
			else
			{
				ar->PlayAnimation(L"arabianleftmoveAX", true);
			}
			mState = Arabianstate::patrol;
			mTimecheck = 0.0f;
		}

		if (fabs(mPlayerDistance) < Scale + 250.0f)
		{
			if (mPlayerDistance >= 0 )
			{
				ar->PlayAnimation(L"arabianleftmoveAX", true);
				mDirect = false;
			}
			else
			{
				ar->PlayAnimation(L"arabianrightmoveAX", true);
				mDirect = true;
			}
			mState = Arabianstate::rockon;
			mTimecheck = 0.0f;
		}
	}

	void Arabian::Death()
	{
		Animator* ar = this->GetComponent<Animator>();
		if (ar->Getcomplete())
		{
			Destroy(this);
		}
	}

	void Arabian::RockOn()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* ar = GetComponent<Animator>();
		mPlayerDistance = pos.x - PlayerBottom::GetPlayerPosition().x;

		if (mDirect)
		{
			pos.x += 300 * Time::DeltaTime();
		}
		else
		{
			pos.x -= 300 * Time::DeltaTime();
		}


		if (fabs(mPlayerDistance) <= Scale)
		{
			if (mDirect)
			{
				ar->PlayAnimation(L"arabianrightidleAX", true);
			}
			else
			{
				ar->PlayAnimation(L"arabianleftidleAX", true);
			}
			mState = Arabianstate::prepare;
			mTimecheck = 0.0f;
		}
		
		tr->SetPosition(pos);
	}

	void Arabian::Patrol()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* ar = GetComponent<Animator>();
		mPlayerDistance = pos.x - PlayerBottom::GetPlayerPosition().x;

		if (mDirect)
		{
			pos.x += 200.0f * Time::DeltaTime();
			mMoveDistance += 200.0f * Time::DeltaTime();
			if (mPatrolCount == 0)
			{
				if (mMoveDistance > 250.0f)
				{
					mDirect = false;
					mMoveDistance = 0.0f;
					mPatrolCount++;
					ar->PlayAnimation(L"arabianleftmoveAX", true);
				}
			}
			else
			{
				if (mMoveDistance > 500.0f)
				{
					mDirect = false;
					mMoveDistance = 0.0f;
					mPatrolCount++;
					ar->PlayAnimation(L"arabianleftmoveAX", true);
				}
			}
		}
		else
		{
			pos.x -= 200.0f * Time::DeltaTime();
			mMoveDistance -= 200.0f * Time::DeltaTime();
			if (mPatrolCount == 0)
			{
				if (mMoveDistance < -250.0f)
				{
					mDirect = true;
					mMoveDistance = 0.0f;
					mPatrolCount++;
					ar->PlayAnimation(L"arabianrightmoveAX", true);
				}
			}
			else
			{
				if (mMoveDistance < -500.0f)
				{
					mDirect = true;
					mMoveDistance = 0.0f;
					mPatrolCount++;
					ar->PlayAnimation(L"arabianrightmoveAX", true);
				}
			}
		}

		if (mPatrolCount == 4)
		{
			mMoveDistance = 0.0f;
			mPatrolCount = 0;
			mState = Arabianstate::idle;
			if (mDirect)
			{
				ar->PlayAnimation(L"arabianrightidleAX", true);
			}
			else
			{
				ar->PlayAnimation(L"arabianleftidleAX", true);
			}
		}

		tr->SetPosition(pos);

		if (fabs(mPlayerDistance) < Scale + 250.0f)
		{
			if (mPlayerDistance >= 0)
			{
				ar->PlayAnimation(L"arabianleftmoveAX", true);
				mDirect = false;
			}
			else
			{
				ar->PlayAnimation(L"arabianrightmoveAX", true);
				mDirect = true;
			}
			mState = Arabianstate::rockon;
			mTimecheck = 0.0f;
			mMoveDistance = 0.0f;
			mPatrolCount = 0;
		}
	}

	void Arabian::Prepare()
	{
		mTimecheck += Time::DeltaTime();
		Animator* ar = GetComponent<Animator>();
		if (mTimecheck > 1.0f)
		{
			if (mDirect)
			{
				ar->PlayAnimation(L"arabianrightattackAX");
			}
			else
			{
				ar->PlayAnimation(L"arabianleftattackAX");
			}
			mTimecheck = 0.0f;
			mState = Arabianstate::attack;
		}
	}

	void Arabian::Attack()
	{
		Animator* ar = GetComponent<Animator>();

		if (ar->Getcomplete())
		{
			if (mDirect)
			{
				ar->PlayAnimation(L"arabianrightidleAX", true);
			}
			else
			{
				ar->PlayAnimation(L"arabianleftidleAX", true);
			}
			mState = Arabianstate::idle;
		}
	}

	void Arabian::OnCollisionEnter(Collider* other)
	{
		NormalBulletCollsionEnter(other);
		EfBombCollsionEnter(other);
	}
	void Arabian::OnCollisionStay(Collider* other)
	{
	}
	void Arabian::OnCollisionExit(Collider* other)
	{
	}
	void Arabian::NormalBulletCollsionEnter(Collider* other)
	{
		sbNormalBullet* normalbullet = dynamic_cast<sbNormalBullet*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (normalbullet == nullptr)
			return;
		else
		{
			if (mDirect)
				ar->PlayAnimation(L"arabianrightdeadAX");
			else
				ar->PlayAnimation(L"arabianleftdeadAX");

			mState = Arabianstate::death;
		}
			
	}
	void Arabian::EfBombCollsionEnter(Collider* other)
	{
		EfBomb* efbomb = dynamic_cast<EfBomb*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (efbomb == nullptr)
			return;
		else
		{
			if (mDirect)
				ar->PlayAnimation(L"arabianrightdeadAX");
			else
				ar->PlayAnimation(L"arabianleftdeadAX");
			mState = Arabianstate::death;
		}

	}
	void Arabian::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"Arabian"
			, L"..\\Resource\\Monster\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Arabian.bmp");

		Animator* ar = this->AddComponent<Animator>();
		Rigidbody* rb = this->AddComponent<Rigidbody>();
		Collider* col = this->AddComponent<Collider>();
		Transform* tr = this->AddComponent<Transform>();
		ar->CreateAnimation(L"arabianleftidleAX", image, Vector2(0.0f, 352.0f), Vector2(88.0f, 88.0f), 4, Vector2(0.0f, -10.0f));
		ar->CreateAnimation(L"arabianrightidleAX", image, Vector2(352.0f, 352.0f), Vector2(88.0f, 88.0f), 4,Vector2(0.0f,-10.0f));
		ar->CreateAnimation(L"arabianlefdeadAX", image, Vector2(0.0f, 616.0f), Vector2(88.0f, 88.0f), 11, Vector2(0.0f, -10.0f));
		ar->CreateAnimation(L"arabianrightdeadAX", image, Vector2(.0f, 704.0f), Vector2(88.0f, 88.0f), 11, Vector2(0.0f, -10.0f));
		ar->CreateAnimation(L"arabianleftmoveAX", image, Vector2(0.0f, 88.0f), Vector2(88.0f, 88.0f), 11, Vector2(20.0f, -10.0f));
		ar->CreateAnimation(L"arabianrightmoveAX", image, Vector2(.0f, 176.0f), Vector2(88.0f, 88.0f), 11, Vector2(-20.0f, -10.0f));
		ar->CreateAnimation(L"arabianlefattackAX", image, Vector2(0.0f, 440.0f), Vector2(88.0f, 88.0f), 8, Vector2(-55.0f, -10.0f));
		ar->CreateAnimation(L"arabianrightattackAX", image, Vector2(.0f, 528.0f), Vector2(88.0f, 88.0f), 8, Vector2(55.0f, -10.0f));
		ar->PlayAnimation(L"arabianleftidleAX",true);
		ar->SetScale(Vector2(4.0f, 4.0f));
		col->SetSize(Vector2(90.0f, 150.0f));
		col->SetPosition(tr->GetPosition());
	}
}