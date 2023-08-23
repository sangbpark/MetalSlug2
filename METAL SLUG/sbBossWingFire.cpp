#include "sbBossWingFire.h"
#include "sbTransform.h"
#include "sbAnimator.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbPlayerBottom.h"
#include "sbTime.h"
#include "sbBoss.h"
namespace sb
{
	BossWingFire::BossWingFire()
		:mState(eBossWingFireState::Create)
	{
		ResourceLoad();
	}
	BossWingFire::~BossWingFire()
	{
	}
	void BossWingFire::Initialize()
	{
	}
	void BossWingFire::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::BossWingFire::eBossWingFireState::Create:
			Create();
			break;
		case sb::BossWingFire::eBossWingFireState::Idle:
			Idle();
			break;
		case sb::BossWingFire::eBossWingFireState::Death:
			Death();
			break;
		default:
			break;
		}

	}
	void BossWingFire::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void BossWingFire::Create()
	{
		Boss* boss = dynamic_cast<Boss*>(mOwner);
		Transform* bosstr = boss->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = bosstr->GetPosition();
		Animator* at = GetComponent<Animator>();
		if (mPositon == eBossWingFirePosition::Left)
		{
			pos.x -= 415.0f;
			at->PlayAnimation(L"wingfireLeftAX",true);
		}
		else
		{
			pos.x += 415.0f;
			at->PlayAnimation(L"wingfirerightAX",true);
		}

		pos.y += 100.0f;
		mState = eBossWingFireState::Idle;
		tr->SetPosition(pos);
	}
	void BossWingFire::Idle()
	{
		Boss* boss = dynamic_cast<Boss*>(mOwner);
		Transform* bosstr = boss->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = bosstr->GetPosition();
		if (mPositon == eBossWingFirePosition::Left)
			pos.x -= 415.0f;
		else
			pos.x += 415.0f;

		pos.y += 100.0f;

		if (boss->GetBossStage() == Boss::eBossStage::Death)
			mState = eBossWingFireState::Death;
		tr->SetPosition(pos);
	}
	void BossWingFire::Death()
	{
		this->Pause();
	}
	void BossWingFire::ResourceLoad()
	{
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Texture* image = Resources::Load<Texture>(L"Fire",
			L"..\\Resource\\effect\\bosswing.bmp");
		at->CreateAnimation(L"wingfireLeftAX", image, Vector2(0.0f, 0.0f), Vector2(88.0f, 88.0f), 6, Vector2(0.0f, 0.0f));
		at->CreateAnimation(L"wingfirerightAX", image, Vector2(0.0f, 88.0f), Vector2(88.0f, 88.0f), 6, Vector2(0.0f, 0.0f));
		at->SetScale(Vector2(4.5f, 4.5f));

	}
}