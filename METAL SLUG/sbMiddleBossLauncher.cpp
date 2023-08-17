#include "sbMiddleBossLauncher.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbTransform.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbTime.h"
#include "sbHeavyBullet.h"
#include "sbNormalBullet.h"
#include "sbMiddleBossColumn.h"
#include "sbMiddleBossSmoke.h"
#include "sbObject.h"

namespace sb
{
	MiddleBossLauncher::MiddleBossLauncher()
		:mHp(15.0f)
		,mFireTime(3.0f)
		,mState(eState::Idle)
		,mHit(false)
	{
		ResourceLoad();
	}
	MiddleBossLauncher::~MiddleBossLauncher()
	{
	}
	void MiddleBossLauncher::Initialize()
	{
	}
	void MiddleBossLauncher::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::MiddleBossLauncher::eState::Idle:
			Idle();
			break;
		case sb::MiddleBossLauncher::eState::Fire:
			Fire();
			break;
		case sb::MiddleBossLauncher::eState::Death:
			Death();
			break;
		case sb::MiddleBossLauncher::eState::End:
			break;
		default:
			break;
		}
		Hit();
	}
	void MiddleBossLauncher::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MiddleBossLauncher::OnCollisionEnter(Collider* other)
	{
		if (!(mState == eState::Death))
		{
			HeavyBulletCollisionEnter(other);
			NormalBulletCollisionEnter(other);
			if (mHp <= 0.0f)
			{
				MiddleBossColumn* mdc = dynamic_cast<MiddleBossColumn*>(mOwner);
				mdc->SetMiddleBossColumn(MiddleBossColumn::eState::Death);
				Animator* at = GetComponent<Animator>();
				at->PlayAnimation(L"MiddleBossLauncherdeathAX");
				DeathRocket();
				mState = eState::Death;
			}
		}
	}
	void MiddleBossLauncher::OnCollisionStay(Collider* other)
	{
	}
	void MiddleBossLauncher::OnCollisionExit(Collider* other)
	{
	}
	void MiddleBossLauncher::Idle()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		mFireTime -= Time::DeltaTime();

		if (mFireTime <= 0.0f)
		{
			Vector2 pos = tr->GetPosition();
			pos.y += 10.0f;
			MiddleBossSmoke* mbs = object::Instantiate<MiddleBossSmoke>(eLayerType::Effects, pos);
			MiddleBossRocket* mbr = object::Instantiate<MiddleBossRocket>(eLayerType::Effects, pos);
			mbr->SetMiddleRocketPosition(GetPosition(mPosition));
			mMiddleBossRocket.push_back(mbr);
			at->PlayAnimation(L"MiddleBossLauncherfireAX");
			mState = eState::Fire;
		}
	}
	void MiddleBossLauncher::Fire()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			at->PlayAnimation(L"MiddleBossLauncheridleAX");
			mState = eState::Idle;
			mFireTime = 3.0f;
		}
	}
	void MiddleBossLauncher::Death()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			Destroy(this);
		}
	}
	MiddleBossRocket::ePosition MiddleBossLauncher::GetPosition(ePosition position)
	{
		if (mPosition == ePosition::Left)
			return MiddleBossRocket::ePosition::Left;

		else if (mPosition == ePosition::Middle)
			return MiddleBossRocket::ePosition::Middle;

		else if (mPosition == ePosition::Right)
			return MiddleBossRocket::ePosition::Right;
	}
	void MiddleBossLauncher::DeathRocket()
	{
		for (auto iter = mMiddleBossRocket.begin()
			; iter != mMiddleBossRocket.end()
			; iter++)
		{
			auto middlebossrocket = *iter;
			if (middlebossrocket == nullptr)
				continue;
			if (middlebossrocket->GetMiddleRocketState() != MiddleBossRocket::eState::Death)
			{
				middlebossrocket->SetMiddleBossRockeDeath();
			}
		}
	}
	void MiddleBossLauncher::Hit()
	{
		if (mHit)
		{
			Animator* at = GetComponent<Animator>();
			float alpha = at->GetAlpha();
			alpha = 0.8f;
			at->SetAlpha(alpha);
			mHit = false;
		}
		else
		{
			Animator* at = GetComponent<Animator>();
			float alpha = at->GetAlpha();
			alpha = 1.0f;
			at->SetAlpha(alpha);
		}
	}
	void MiddleBossLauncher::ResourceLoad()
	{
		Texture* imagePlayer = Resources::Load<Texture>(L"MiddleBossLauncher"
			, L"..\\Resource\\Monster\\middle boss rokect1.bmp");
		Texture* image = Resources::Load<Texture>(L"MiddleBossLauncherdeath"
			, L"..\\Resource\\effect\\middlebossdeath1.bmp");
		Animator* at = this->AddComponent<Animator>();
		Transform* tr = this->AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		at->CreateAnimation(L"MiddleBossLauncheridleAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(44.0f, 44.0f), 1);
		at->CreateAnimation(L"MiddleBossLauncherfireAX", imagePlayer, Vector2(0.0f, 44.0f), Vector2(44.0f, 44.0f), 5);
		at->CreateAnimation(L"MiddleBossLauncherdeathAX", image, Vector2(0.0f, 0.0f), Vector2(88.0f, 88.0f), 28);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"MiddleBossLauncheridleAX");
		col->SetSize(Vector2(150.0f, 150.0f));
	}
	void MiddleBossLauncher::HeavyBulletCollisionEnter(Collider* other)
	{
		HeavyBullet* hb = dynamic_cast<HeavyBullet*>(other->GetOwner());
		if (hb == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 0.7;
		}
	}
	void MiddleBossLauncher::NormalBulletCollisionEnter(Collider* other)
	{
		sbNormalBullet* nb = dynamic_cast<sbNormalBullet*>(other->GetOwner());
		if (nb == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 1;
		}
	}
}