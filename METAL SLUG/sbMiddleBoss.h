#pragma once
#include "sbGameObject.h"
#include "sbMiddleBossColumn.h"

namespace sb
{
	class MiddleBoss : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Death,
			End
		};
		MiddleBoss();
		virtual ~MiddleBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Death();

		void ResourseLoad();

		eState GetMiddleBossState() { return mState; }
		void SetControlTowerActive(bool value) { mControlTowerActive = value; }
		bool GetControlTowerActive() { return mControlTowerActive; }

	private:
		bool mControlTowerActive;

		std::vector<MiddleBossColumn*> mMiddleBossColumn;
		eState mState;
		float mPlayerDistance;
	};
}

