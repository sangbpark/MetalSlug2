#include "sbHOldMan.h"
#include "sbTransform.h"
#include "sbResources.h"
#include "sbTexture.h"
#include "sbAnimator.h"
#include "sbRigidbody.h"
#include "sbCollider.h"
#include "sbNormalBullet.h"
#include "sbHeavyBullet.h"
#include "sbEfBomb.h"
#include "sbHeavyMachineGun.h"
#include "sbSupply.h"
#include "sbObject.h"
#include "sbPlayerBottom.h"
#include "sbSound.h"

namespace sb
{
	HOldMan::HOldMan()
		:mState(eState::Idle)
		, mPlayerDistance(0.0f)
	{
		ResourceLoad();
	}
	HOldMan::~HOldMan()
	{
	}
	void HOldMan::Initialize()
	{
	}
	void HOldMan::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayerDistance = fabs(pos.x - PlayerBottom::GetPlayerPosition().x);
		if (mPlayerDistance > 2000.0f)
			return;
		GameObject::Update();
		switch (mState)
		{
		case::sb::HOldMan::eState::Idle:
			Idle();
			break;
		case::sb::HOldMan::eState::Free:
			Free();
			break;
		case::sb::HOldMan::eState::Item:
			Item();
			break;
		case::sb::HOldMan::eState::death:
			Death();
			break;

		}
	}
	void HOldMan::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayerDistance = fabs(pos.x - PlayerBottom::GetPlayerPosition().x);
		if (mPlayerDistance > 2000.0f)
			return;
		GameObject::Render(hdc);
	}

	void HOldMan::Idle()
	{
	}

	void HOldMan::Free()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			mState = eState::Item;
			at->PlayAnimation(L"NpcOldManitemAX");
		}
	}

	void HOldMan::Item()
	{
		Animator* at = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x -= 80.0f;
		if (at->Getcomplete())
		{
			if (mItems == eItems::Heavy)
			{
				HeavyMachineGun* hmg = object::Instantiate<HeavyMachineGun>(eLayerType::Effects, pos);
			}
			else
			{
				Supply* sy = object::Instantiate<Supply>(eLayerType::Effects, pos);
			}
			mState = eState::death;
			at->PlayAnimation(L"NpcOldMandeadAX");
		}
	}

	void HOldMan::Death()
	{
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			Destroy(this);
		}
	}

	void HOldMan::OnCollisionEnter(Collider* other)
	{
		if (mState == eState::Idle)
		{
			NormalBulletCollsionEnter(other);
			HeavyBulletCollsionEnter(other);
			EfBombCollsionEnter(other);
		}
	}
	void HOldMan::OnCollisionStay(Collider* other)
	{
	}
	void HOldMan::OnCollisionExit(Collider* other)
	{
	}

	void HOldMan::NormalBulletCollsionEnter(Collider* other)
	{
		sbNormalBullet* normalbullet = dynamic_cast<sbNormalBullet*>(other->GetOwner());
		Animator* ar = GetComponent<Animator>();
		if (normalbullet == nullptr)
			return;
		else
		{
			mState = eState::Free;
			ar->PlayAnimation(L"NpcOldManfreeAX");
			Sound* sound = Resources::Load<Sound>(L"ty"
				, L"..\\Resource\\sound\\metal-slug-thank-you-tenkiu.wav");
			sound->Play(false);
		}

	}
	void HOldMan::HeavyBulletCollsionEnter(Collider* other)
	{
		HeavyBullet* heavybullet = dynamic_cast<HeavyBullet*>(other->GetOwner());
		Animator* ar = GetComponent<Animator>();
		if (heavybullet == nullptr)
			return;
		else
		{
			mState = eState::Free;
			ar->PlayAnimation(L"NpcOldManfreeAX");
			Sound* sound = Resources::Load<Sound>(L"ty"
				, L"..\\Resource\\sound\\metal-slug-thank-you-tenkiu.wav");
			sound->Play(false);
		}
	}
	void HOldMan::EfBombCollsionEnter(Collider* other)
	{
		EfBomb* efbomb = dynamic_cast<EfBomb*>(other->GetOwner());
		Animator* ar = this->GetComponent<Animator>();
		if (efbomb == nullptr)
			return;
		else
		{
			mState = eState::Free;
			ar->PlayAnimation(L"NpcOldManfreeAX");
			Sound* sound = Resources::Load<Sound>(L"ty"
				, L"..\\Resource\\sound\\metal-slug-thank-you-tenkiu.wav");
			sound->Play(false);
		}

	}
	void HOldMan::ResourceLoad()
	{

		Texture* imageNpcOldMan = Resources::Load<Texture>(L"NpcOldMan"
			, L"..\\Resource\\Npc\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - POWs Helpful NPCs.bmp");
		Transform* tr = AddComponent<Transform>();
		Rigidbody* rd = AddComponent<Rigidbody>();
		Animator* at = AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();
		at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 0.0f), Vector2(44.0f, 44.0f), 2,Vector2(10.0f, -20.0f));
		at->CreateAnimation(L"NpcOldManfreeAX", imageNpcOldMan, Vector2(0.0f, 0.0f), Vector2(44.0f, 44.0f), 9, Vector2(10.0f, -20.0f));
		at->CreateAnimation(L"NpcOldManitemAX", imageNpcOldMan, Vector2(0.0f, 44.0f), Vector2(88.0f, 44.0f), 11, Vector2(10.0f, -50.0f));
		at->CreateAnimation(L"NpcOldMandeadAX", imageNpcOldMan, Vector2(0.0f, 88.0f), Vector2(44.0f, 44.0f), 14, Vector2(10.0f, -50.0f));
		at->SetScale(Vector2(4.5f, 4.5f));
		col->SetSize(Vector2(100.0f, 100.0f));
		at->PlayAnimation(L"NpcOldManIdleAX",true);

	}
}