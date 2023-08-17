#include "sbBerserker.h"
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
#include "sbHeavyBullet.h"



namespace sb
{
	Berserker::Berserker()
		: mState(eState::Attack)
		, mHp(2.0f)
		, mDirect(false)
	{
		ResourseLoad();
	}
	Berserker::~Berserker()
	{
	}
	void Berserker::Initialize()
	{
	}
	void Berserker::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::Berserker::eState::Idle:
			break;
		case sb::Berserker::eState::Rest:
			break;
		case sb::Berserker::eState::Attack:
			Attack();
			break;
		case sb::Berserker::eState::Death:
			Death();
			break;
		case sb::Berserker::eState::End:
			break;
		default:
			break;
		}

	}
	void Berserker::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Berserker::OnCollisionEnter(Collider* other)
	{
		if (!(mState == eState::Death))
		{
			NormalBulletCollsionEnter(other);
			HeavyBulletCollsionEnter(other);
			EfBombCollsionEnter(other);
			if (mHp <= 0.0f)
			{
				Animator* at = GetComponent<Animator>();
				if (mDirect)
					at->PlayAnimation(L"berserkerdeathrightAX");
				else
					at->PlayAnimation(L"berserkerdeathleftAX");
				mState = eState::Death;
			}
		}

	}
	void Berserker::OnCollisionStay(Collider* other)
	{
	}
	void Berserker::OnCollisionExit(Collider* other)
	{
	}

	void Berserker::Idle()
	{
	}
	void Berserker::Rest()
	{
	}
	void Berserker::Attack()
	{
		BerserkerKnife* bsk = dynamic_cast<BerserkerKnife*>(mberserkerknife);
		Transform* bsktr = bsk->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();
		mPlayerDistance = pos.x - PlayerBottom::GetPlayerPosition().x;

		if (fabs(mPlayerDistance) >= 500.0f)
		{
			if(mPlayerDistance <0.0f)
			{
				mDirect = true;
				at->PlayAnimation(L"berserkerattackrightAX", true);
			}
			else
			{
				mDirect = false;
				at->PlayAnimation(L"berserkerattackleftAX", true);
			}
		}

		if (mDirect)
		{
			pos.x += 300 * Time::DeltaTime();
		}
		else
		{
			pos.x -= 300 * Time::DeltaTime();
		}

		tr->SetPosition(pos);
		if (mDirect)
			pos.x += 50.0f;
		else
			pos.x -= 50.0f;
		if (bsktr == nullptr)
			return;
		bsktr->SetPosition(pos);
	}
	void Berserker::Death()
	{
		BerserkerKnife* bsk = dynamic_cast<BerserkerKnife*>(mberserkerknife);
		if(bsk != nullptr)
			bsk->Death();
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			Destroy(this);
		}
	}
	void Berserker::NormalBulletCollsionEnter(Collider* other)
	{
		sbNormalBullet* normalbullet = dynamic_cast<sbNormalBullet*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (normalbullet == nullptr)
			return;
		else
		{
			mHp -= 1.0f;
		}

	}
	void Berserker::HeavyBulletCollsionEnter(Collider* other)
	{
		HeavyBullet* heavybullet = dynamic_cast<HeavyBullet*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (heavybullet == nullptr)
			return;
		else
		{
			mHp -= 0.7f;
		}
	}
	void Berserker::EfBombCollsionEnter(Collider* other)
	{
		EfBomb* efbomb = dynamic_cast<EfBomb*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (efbomb == nullptr)
			return;
		else
		{
			mHp -= 5.0f;
		}

	}
	void Berserker::ResourseLoad()
	{
		Texture* image = Resources::Load<Texture>(L"Berserker"
			, L"..\\Resource\\Monster\\berserker.bmp");
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		Rigidbody* rb = AddComponent<Rigidbody>();
		at->CreateAnimation(L"berserkerrestAX", image, Vector2(0.0f, 0.0f), Vector2(44.0f, 44.0f), 4, Vector2(0.0f, -15.0f));
		at->CreateAnimation(L"berserkeridlerightAX", image, Vector2(0.0f, 88.0f), Vector2(88.0f, 44.0f), 6, Vector2(0.0f, -15.0f));
		at->CreateAnimation(L"berserkeridleleftAX", image, Vector2(0.0f, 44.0f), Vector2(88.0f, 44.0f), 6, Vector2(0.0f, -15.0f));
		at->CreateAnimation(L"berserkerattackrightAX", image, Vector2(0.0f, 220.0f), Vector2(88.0f, 88.0f), 6, Vector2(0.0f, -20.0f));
		at->CreateAnimation(L"berserkerattackleftAX", image, Vector2(0.0f, 132.0f), Vector2(88.0f, 88.0f), 6, Vector2(0.0f, -20.0f));
		at->CreateAnimation(L"berserkerdeathrightAX", image, Vector2(0.0f, 396.0f), Vector2(88.0f, 88.0f), 9, Vector2(0.0f, -20.0f));
		at->CreateAnimation(L"berserkerdeathleftAX", image, Vector2(0.0f, 308.0f), Vector2(88.0f, 88.0f), 9, Vector2(0.0f, -20.0f));
		at->SetScale(Vector2(4.0f, 4.0f));
		at->PlayAnimation(L"berserkerattackleftAX",true);
		
		BerserkerKnife* berserkerknife = object::Instantiate<BerserkerKnife>(eLayerType::Effects, tr->GetPosition());
		mberserkerknife = berserkerknife;
		col->SetSize(Vector2(100.0f, 150.0f));
	}
}