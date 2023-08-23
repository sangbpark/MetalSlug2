#include "sbBoss.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbRigidbody.h"
#include "sbInput.h"
#include "sbBossWing.h"
#include "sbNormalBullet.h"
#include "sbHeavyBullet.h"
#include "sbEfBomb.h"
#include "sbCamelBullet.h"
#include "sbBossFloor.h"
#include "sbArabian.h"
#include "sbBossWingFire.h"

namespace sb
{
	Boss::Boss()
		: mBossStage(eBossStage::Meet)
		, mSpeed(120.0f)
		, mUpDown(false)
		, mCount(0)
		, mDirect(false)
		, mHp(150.0f)
		, mHit(false)
		, mStage2On(false)
		, mArabianTime(0.0f)
	{
		ResourceLoad();
	}
	Boss::~Boss()
	{
	}
	void Boss::Initialize()
	{
	}
	void Boss::Update()
	{
		GameObject::Update();
		switch (mBossStage)
		{
		case sb::Boss::eBossStage::Meet:
			Meet();
			break;
		case sb::Boss::eBossStage::Stage1:
			Stage1();
			break;
		case sb::Boss::eBossStage::Stage2:
			Stage2();
			break;
		case sb::Boss::eBossStage::Death:
			Death();
			break;
		case sb::Boss::eBossStage::Ready:
			Ready();
			break;
		case sb::Boss::eBossStage::Attack:
			Attack();
			break;
		case sb::Boss::eBossStage::Rest:
			Rest();
			break;
		default:
			break;
		}
		Hit();
	}
	void Boss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Boss::Meet()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();;
		pos.y += mSpeed * Time::DeltaTime();
		mSpeed -= 12.0f * Time::DeltaTime();
		if (pos.y >= 100.0f)
		{
			pos.y = 100.0f;
			mBossStage = eBossStage::Stage1;
			mSpeed = 50.0f;
		}
		tr->SetPosition(pos);
	}
	void Boss::Stage1()
	{
		mArabianTime -= Time::DeltaTime();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();;
		if (mUpDown)
		{
			pos.y -= mSpeed * Time::DeltaTime();
		}
		else
		{
			pos.y += mSpeed * Time::DeltaTime();
		}
		mSpeed -= 20.0f * Time::DeltaTime();
		if (pos.y >= 130.0f)
		{
			pos.y = 130.0f;
			mUpDown = true;
			mSpeed = 50.0f;
		}
		else if (pos.y <= 70.0f)
		{
			pos.y = 70.0f;
			mUpDown = false;
			mSpeed = 50.0f;
		}

		if(mArabianTime <= 0.0f)
		{
			CreateArabian(true);
			CreateArabian(false);
			mArabianTime = 4.0f;
		}
		tr->SetPosition(pos);
	}
	void Boss::Stage2()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();;
		pos.y -= 80.0f * Time::DeltaTime();
		if (pos.y <= 0.0f)
		{
			pos.y = 0.0f;
			mBossStage = eBossStage::Ready;
		}
		tr->SetPosition(pos);
	}
	void Boss::Death()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();;
		pos.y += 100.0f * Time::DeltaTime();
		if (pos.y >= 300.0f)
		{
			pos.y = 300.0f;
			this->Pause();
		}
		tr->SetPosition(pos);
	}
	void Boss::Ready()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();;
		if (mUpDown)
		{
			pos.y -= mSpeed * Time::DeltaTime();
		}
		else
		{
			pos.y += mSpeed * Time::DeltaTime();
		}
		mSpeed -= 20.0f * Time::DeltaTime();
		if (pos.y >= 20.0f)
		{
			pos.y = 20.0f;
			mUpDown = true;
			mSpeed = 50.0f;
		}
		else if (pos.y <= -20.0f)
		{
			pos.y = -20.0f;
			mUpDown = false;
			mSpeed = 50.0f;
		}

		tr->SetPosition(pos);
	}
	void Boss::Attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();;
		if (mCount!=3)
		{
			if (mDirect)
				pos.x += 300.0f * Time::DeltaTime();
			else
				pos.x -= 300.0f * Time::DeltaTime();
			if (pos.x <= 16000.0f)
			{
				pos.x = 16000.0f;
				mDirect = true;
				mCount++;
			}
			else if (pos.x >= 16800.0f)
			{
				pos.x = 16800.0f;
				mDirect = false;
				mCount++;
			}
		}
		else if (mCount == 3)
		{
			if (mDirect)
				pos.x += 300.0f * Time::DeltaTime();
			else
				pos.x -= 300.0f * Time::DeltaTime();
			if (pos.x >= 16400.0f
				&& pos.x <= 16440.0f)
			{
				pos.x = 16420.0f;
				mCount = 0;
				mDirect = false;
				mBossStage = eBossStage::Rest;
			}
		}
		tr->SetPosition(pos);
	}
	void Boss::Rest()
	{
	}
	void Boss::OnCollisionEnter(Collider* other)
	{
		if (mBossStage != eBossStage::Meet
			&& mBossStage != eBossStage::Death)
		{
			NormalBulletCollsionEnter(other);
			HeavyBulletCollsionEnter(other);
			EfBombCollsionEnter(other);
			CamelBulletCollisionEnter(other);
			if (mBossStage == eBossStage::Stage1
				&& mHp <= 100.0f)
			{
				Animator* at = GetComponent<Animator>();
				at->PlayAnimation(L"bossstage2AX");
				mBossStage = eBossStage::Stage2;
				BossWingFire* bwf = object::Instantiate<BossWingFire>(enums::eLayerType::Floor);
				bwf->SetBossWingFirePosition(BossWingFire::eBossWingFirePosition::Left);
				bwf->SetOwner(this);
				BossWingFire* bwf2 = object::Instantiate<BossWingFire>(enums::eLayerType::Floor);
				bwf2->SetBossWingFirePosition(BossWingFire::eBossWingFirePosition::Right);
				bwf2->SetOwner(this);
			}
			else if (mBossStage == eBossStage::Stage2
				&& mHp <= 50.0f
				&& mStage2On == false)
			{
				Animator* at = GetComponent<Animator>();
				at->PlayAnimation(L"bossstage3AX");
				mStage2On = true;
			}
			else if (mHp <= 0.0f)
			{
				Animator* at = GetComponent<Animator>();
				at->PlayAnimation(L"bossstage4AX");
				mBossStage = eBossStage::Death;
			}
		}
	}
	void Boss::OnCollisionStay(Collider* other)
	{
	}
	void Boss::OnCollisionExit(Collider* other)
	{
	}
	void Boss::CreateArabian(bool direct)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if(direct)
		{
			pos.x += 80.0f;
			pos.y -= 30.0f;
			Arabian* arabian = object::Instantiate<Arabian>(enums::eLayerType::Monster,pos);
			arabian->SetArabianDirecet(direct);
			arabian->SetArabianCreate(Arabian::eArabianCreate::Boss);
		}
		else
		{
			pos.x -= 80.0f;
			pos.y -= 30.0f;
			Arabian* arabian = object::Instantiate<Arabian>(enums::eLayerType::Monster, pos);
			arabian->SetArabianDirecet(direct);
			arabian->SetArabianCreate(Arabian::eArabianCreate::Boss);
		}
	}
	void Boss::Hit()
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
	void Boss::NormalBulletCollsionEnter(Collider* other)
	{
		sbNormalBullet* normalbullet = dynamic_cast<sbNormalBullet*>(other->GetOwner());
		if (normalbullet == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 1.0f;
		}

	}
	void Boss::HeavyBulletCollsionEnter(Collider* other)
	{
		HeavyBullet* heavybullet = dynamic_cast<HeavyBullet*>(other->GetOwner());
		if (heavybullet == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 0.7f;
		}
	}
	void Boss::EfBombCollsionEnter(Collider* other)
	{
		EfBomb* efbomb = dynamic_cast<EfBomb*>(other->GetOwner());
		if (efbomb == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 5.0f;
		}
	}
	void Boss::CamelBulletCollisionEnter(Collider* other)
	{
		CamelBullet* camelbullet = dynamic_cast<CamelBullet*>(other->GetOwner());
		if (camelbullet == nullptr)
			return;
		else
		{
			mHit = true;
			mHp -= 1.0f;
		}
	}
	void Boss::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"boss"
			, L"..\\Resource\\Monster\\boss.bmp");
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		at->CreateAnimation(L"bossstage1AX", image, Vector2(0.0f, 0.0f), Vector2(352.0f, 176.0f), 1, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"bossstage2AX", image, Vector2(352.0f, 0.0f), Vector2(352.0f, 176.0f), 1, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"bossstage3AX", image, Vector2(704.0f, 0.0f), Vector2(352.0f, 176.0f), 1, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"bossstage4AX", image, Vector2(1056.0f, 0.0f), Vector2(352.0f, 176.0f), 1, Vector2(0.0f, 0.0f));
		at->SetScale(Vector2(4.5f, 3.5f));
		at->PlayAnimation(L"bossstage1AX");
		col->SetSize(Vector2(800.0f, 400.0f));
		BossWing* bosswingleft = object::Instantiate<BossWing>(enums::eLayerType::Effects);
		bosswingleft->SetWingOwner(this);
		bosswingleft->SetWingPosition(BossWing::eWingPosition::Left);
		BossWing* bosswingright = object::Instantiate<BossWing>(enums::eLayerType::Effects);
		bosswingright->SetWingOwner(this);
		bosswingright->SetWingPosition(BossWing::eWingPosition::Right);
		BossFloor* floor = object::Instantiate<BossFloor>(enums::eLayerType::Floor);
		floor->SetBossFloorOwner(this);
		Collider* flcol = floor->AddComponent<Collider>();
		flcol->SetSize(Vector2(600.0f, 25.0f));

	}
}