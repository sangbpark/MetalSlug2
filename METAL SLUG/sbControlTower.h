#pragma once
#include "sbGameObject.h"
#include "sbTruck.h"

namespace sb
{
	class ControlTower : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Create,
			Detection,
			End
		};
		enum class eStage
		{
			Idle,
			Truck,
			MiddleBoss,
			Wall,
			Helicopter,
			Boss,
			End
		};
		ControlTower();
		virtual ~ControlTower();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Create();
		void Detection();

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetStage(eStage stage) { mStage = stage; }
		eStage GetStage() { return mStage; }
		bool GetActive() { return mActive; }
		bool GetTargetLive() { return mTargetlive; }
		void SetActive(bool value) { mActive = value; }
		void SetTargetlive(bool value) { mTargetlive = value; }
		void SetControlTowerState(eState state) { mState = state; }

	private:
		GameObject* mTarget;
		bool mActive;
		bool mTargetlive;
		bool mEnter;

		eStage mStage;
		eState mState;
	};
}

