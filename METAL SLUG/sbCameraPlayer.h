#pragma once
#include "sbGameObject.h"
#include "sbUi.h"
#include "sbControlTower.h"
#include "sbSound.h";

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
			StageClear,
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
		void StageClear();

		void SearchControlTower();
		void SearchControlTowerTarget();
		void UiSetting();

		void SetOwner(GameObject* owner) { mOwner = owner; }
		Sound* GetSound() { return mSound; }
		void SetSound(Sound* sound) { mSound = sound; }
		static bool GetStageClear() { return mStageClear; }

	private:
		GameObject* mOwner;
		Ui* mUi;
		std::vector<ControlTower*> mControlTower;
		eState mState;
		eStage mStage;
		Sound* mSound;

		static bool mStageClear;
		float mTime;
	};
}
