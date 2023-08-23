#include "sbBossWing.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbCollider.h"
#include "sbAnimator.h"
#include "sbBoss.h"

namespace sb
{
	BossWing::BossWing()
		:mWingState(eWingState::Create)
	{
		ResourceLoad();
	}
	BossWing::~BossWing()
	{
	}
	void BossWing::Initialize()
	{
	}
	void BossWing::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Transform* bosstr = mOwner->GetComponent<Transform>();
		Vector2 pos = bosstr->GetPosition();
		if (mWingPosition == eWingPosition::Left)
			pos.x -= 415.0f;
		else
			pos.x += 415.0f;
		
		pos.y += 550.0f;

		tr->SetPosition(pos);
	}
	void BossWing::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		switch (mWingState)
		{
		case sb::BossWing::eWingState::Create:
			Create();
			break;
		case sb::BossWing::eWingState::Idle:
			Idle();
			break;
		case sb::BossWing::eWingState::Charge:
			Charge();
			break;
		case sb::BossWing::eWingState::Attack:
			Attack();
			break;
		case sb::BossWing::eWingState::Rest:
			Rest();
			break;
		default:
			break;
		}
		Boss* boss = dynamic_cast<Boss*>(mOwner);
		if (boss->GetBossStage() == Boss::eBossStage::Death)
		{
			this->Pause();
		}
	}
	void BossWing::Create()
	{
		Animator* at = GetComponent<Animator>();
		if (mWingPosition == eWingPosition::Left)
			at->PlayAnimation(L"WingIdleleftAX", true);
		else
			at->PlayAnimation(L"WingIdlerightAX", true);
		mWingState = eWingState::Idle;
	}
	void BossWing::Idle()
	{
		Boss* boss = dynamic_cast<Boss*>(mOwner);
		if (boss->GetBossStage() == Boss::eBossStage::Ready)
		{
			Animator* at = GetComponent<Animator>();

			if (mWingPosition == eWingPosition::Left)
				at->PlayAnimation(L"WingChargeleftAX");
			else
				at->PlayAnimation(L"WingChargerightAX");
			mWingState = eWingState::Charge;
		}
	}
	void BossWing::Charge()
	{
		Animator* at = GetComponent<Animator>(); 
		if (at->Getcomplete())
		{
			Boss* boss = dynamic_cast<Boss*>(mOwner);
			boss->SetBossStage(Boss::eBossStage::Attack);
			Collider* col = GetComponent<Collider>();
			col->SetSize(Vector2(160.0f, 550.0f));
			if (mWingPosition == eWingPosition::Left)
				at->PlayAnimation(L"WingAttackleftAX", true);
			else
				at->PlayAnimation(L"WingAttackrightAX", true);
			mWingState = eWingState::Attack;
		}
	}
	void BossWing::Attack()
	{
		Boss* boss = dynamic_cast<Boss*>(mOwner);
		if (boss->GetBossStage() == Boss::eBossStage::Rest)
		{
			Animator* at = GetComponent<Animator>();
			Collider* col = GetComponent<Collider>();
			col->SetSize(Vector2(0.0f, 0.0f));
			if (mWingPosition == eWingPosition::Left)
				at->PlayAnimation(L"WingRestleftAX");
			else
				at->PlayAnimation(L"WingRestrightAX");
			mWingState = eWingState::Rest;
		}
	}
	void BossWing::Rest()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			Boss* boss = dynamic_cast<Boss*>(mOwner);
			boss->SetBossStage(Boss::eBossStage::Ready);
			Collider* col = GetComponent<Collider>();
			if (mWingPosition == eWingPosition::Left)
				at->PlayAnimation(L"WingChargeleftAX");
			else
				at->PlayAnimation(L"WingChargerightAX");
			mWingState = eWingState::Charge;
		}
	}
	void BossWing::OnCollisionEnter(Collider* other)
	{
	}
	void BossWing::OnCollisionStay(Collider* other)
	{
	}
	void BossWing::OnCollisionExit(Collider* other)
	{
	}
	void BossWing::ResourceLoad()
	{
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		Texture* image = Resources::Load<Texture>(L"Wing",
			L"..\\Resource\\effect\\bosswingattack.bmp");
		at->CreateAnimation(L"WingIdleleftAX", image, Vector2(0.0f, 528.0f), Vector2(88.0f, 176.0f), 4, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"WingChargeleftAX", image, Vector2(0.0f, 0.0f), Vector2(88.0f, 176.0f), 25, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"WingAttackleftAX", image, Vector2(0.0f, 176.0f), Vector2(88.0f, 176.0f), 6, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"WingRestleftAX", image, Vector2(0.0f, 352.0f), Vector2(88.0f, 176.0f), 16, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"WingIdlerightAX", image, Vector2(0.0f, 1232.0f), Vector2(88.0f, 176.0f), 4, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"WingChargerightAX", image, Vector2(0.0f, 704.0f), Vector2(88.0f, 176.0f), 25, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"WingAttackrightAX", image, Vector2(0.0f, 880.0f), Vector2(88.0f, 176.0f), 6, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"WingRestrightAX", image, Vector2(0.0f, 1056.0f), Vector2(88.0f, 176.0f), 16, Vector2(0.0f, 0.0f));	
		at->SetScale(Vector2(4.5f, 4.5f));
	}
}