#pragma once
#include "sbGameObject.h"
#include "sbUi.h"
#include "sbControlTower.h"

namespace sb
{
	class CameraPlayer : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Rock,
			Resetting,
			End,
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
		CameraPlayer();
		virtual ~CameraPlayer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Move();
		void Rock();
		void Resetting();

		void SearchControlTower();
		void SearchControlTowerTarget();
		void UiSetting();

		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		GameObject* mOwner;
		Ui* mUi;
		std::vector<ControlTower*> mControlTower;
		eState mState;
		eStage mStage;

		float mTime;
	};
}
