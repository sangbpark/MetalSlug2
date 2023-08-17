#include "sbMiddleBoss.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbTransform.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbObject.h"
#include "sbPlayerBottom.h"
#include "sbControlTower.h"


namespace sb
{
	MiddleBoss::MiddleBoss()
		:mState(eState::Idle)
		, mPlayerDistance(0.0f)
	{
		ResourseLoad();
	}
	MiddleBoss::~MiddleBoss()
	{
	}
	void MiddleBoss::Initialize()
	{
	}
	void MiddleBoss::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayerDistance = fabs(pos.x - PlayerBottom::GetPlayerPosition().x);
		if (mPlayerDistance > 2000.0f)
			return;
		GameObject::Update();
		switch (mState)
		{
		case sb::MiddleBoss::eState::Idle:
			Idle();
			break;
		case sb::MiddleBoss::eState::Death:
			Death();
			break;
		default:
			break;
		}
	}
	void MiddleBoss::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayerDistance = fabs(pos.x - PlayerBottom::GetPlayerPosition().x);
		if (mPlayerDistance > 2000.0f)
			return;
		GameObject::Render(hdc);
	}
	void MiddleBoss::Idle()
	{
		int ColumnDeathCount = 0;
		for (auto iter = mMiddleBossColumn.begin()
			; iter != mMiddleBossColumn.end();)
		{
			if ((*iter)->GetMiddleBossColumnState() == MiddleBossColumn::eState::Death)
				ColumnDeathCount++;
			iter++;
		}
		if (ColumnDeathCount == 3)
		{
			Animator* at = GetComponent<Animator>();
			at->PlayAnimation(L"MiddleBossIdledeathAX");
			mState = eState::Death;
		}
	}
	void MiddleBoss::Death()
	{
		Transform* tr = GetComponent<Transform>();
		if (PlayerBottom::GetPlayerPosition().x - tr->GetPosition().x > 2000.0f)
			Destroy(this);
	}
	void MiddleBoss::ResourseLoad()
	{
		Texture* imagePlayer = Resources::Load<Texture>(L"MiddleBoss"
			, L"..\\Resource\\Monster\\middle boss.bmp");
		Animator* at = this->AddComponent<Animator>();
		Transform* tr = this->AddComponent<Transform>();
		at->CreateAnimation(L"MiddleBossIdleAX", imagePlayer, Vector2(0.0f, 1232.0f), Vector2(396.0f, 175.0f), 1);
		at->CreateAnimation(L"MiddleBossIdledeathAX", imagePlayer, Vector2(396.0f, 1232.0f), Vector2(396.0f, 175.0f), 1);
		at->PlayAnimation(L"MiddleBossIdleAX");
		at->SetScale(Vector2(4.5f, 4.5f));
		MiddleBossColumn* middlebosscolumn1 = object::Instantiate<MiddleBossColumn>(eLayerType::BossMonster,Vector2(8835.0f, 150.0f));
		middlebosscolumn1->SetColumnPositon(MiddleBossColumn::ePosition::Left);
		mMiddleBossColumn.push_back(middlebosscolumn1);
		MiddleBossColumn* middlebosscolumn2 = object::Instantiate<MiddleBossColumn>(eLayerType::BossMonster, Vector2(9254.0f, 150.0f));
		middlebosscolumn2->SetColumnPositon(MiddleBossColumn::ePosition::Middle);
		mMiddleBossColumn.push_back(middlebosscolumn2);
		MiddleBossColumn* middlebosscolumn3 = object::Instantiate<MiddleBossColumn>(eLayerType::BossMonster, Vector2(9675.0f, 150.0f));
		middlebosscolumn3->SetColumnPositon(MiddleBossColumn::ePosition::Right);
		mMiddleBossColumn.push_back(middlebosscolumn3);
	}
}