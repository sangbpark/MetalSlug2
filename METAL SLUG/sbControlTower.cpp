#include "sbControlTower.h"
#include "sbCollider.h"
#include "sbTransform.h"
#include "sbPlayerBottom.h"
#include "sbObject.h"
#include "sbCameraPlayer.h"
#include "sbMiddleBoss.h"

namespace sb
{
	ControlTower::ControlTower()
		: mActive(false)
		, mTargetlive(true)
		, mState(eState::Idle)
		, mEnter(false)
	{
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(50.0f, 1000.0f));
		col->SetPosition(Vector2(10000.0f,100.0f));
	}
	ControlTower::~ControlTower()
	{
	}
	void ControlTower::Initialize()
	{
	}
	void ControlTower::Update()
	{
		GameObject::Update();
		switch (mState)
		{
		case sb::ControlTower::eState::Idle:
			Idle();
			break;
		case sb::ControlTower::eState::Create:
			Create();
			break;
		case sb::ControlTower::eState::Detection:
			Detection();
			break;
		case sb::ControlTower::eState::End:
			break;
		default:
			break;
		}
	}
	void ControlTower::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ControlTower::Idle()
	{
		if (mActive == true)
		{
			mState = eState::Create;

		}
	}
	void ControlTower::Create()
	{
		if(mStage == eStage::Truck)
		{
			Truck* truck = object::Instantiate<Truck>(eLayerType::Monster, Vector2(8300.0f, 500.0f));
			mTarget = truck;
			mState = eState::Detection;
		}
		else if (mStage == eStage::MiddleBoss)
		{
			MiddleBoss* middleboss = object::Instantiate<MiddleBoss>(eLayerType::BossMonster, Vector2(9070.0f, 310.0f));
			mTarget = middleboss;
			mState = eState::Detection;
		}
	}
	void ControlTower::Detection()
	{	
		
		if (mStage == eStage::Truck)
		{
			Truck* truck = dynamic_cast<Truck*>(mTarget);
			if (truck->GetTruckState() == Truck::eState::Destroy)
			{
				mTargetlive = false;
				mState = eState::Idle;
				mStage = eStage::Idle;
			}
		}
		else if (mStage == eStage::MiddleBoss)
		{
			MiddleBoss* middleboss = dynamic_cast<MiddleBoss*>(mTarget);
			if (middleboss->GetMiddleBossState() == MiddleBoss::eState::Death)
			{
				mTargetlive = false;
				mState = eState::Idle;
				mStage = eStage::Idle;
			}
		}
	}

	void ControlTower::OnCollisionEnter(Collider* other)
	{
		if (mEnter == true)
			return;
		else if(mActive == false)
		{
			PlayerBottom* pb = dynamic_cast<PlayerBottom*>(other->GetOwner());
			if (pb == nullptr)
				return;
			else
			{
				mActive = true;
				mEnter = true;
			}
		}
	}
	void ControlTower::OnCollisionStay(Collider* other)
	{
	}
	void ControlTower::OnCollisionExit(Collider* other)
	{
	}

}
