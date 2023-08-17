#pragma once
#include "sbGameObject.h"
#include "sbMiddleBossLauncher.h"

namespace sb
{
	class MiddleBossColumn : public GameObject
	{
	public:
		enum class ePosition
		{
			Left,
			Middle,
			Right,
			End,
		};
		enum class eState
		{
			Create,
			Idle,
			Encounter,
			Animation,
			Find,
			Death,
			End

		};
		MiddleBossColumn();
		virtual ~MiddleBossColumn();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Create();
		void Encounter();
		void Animation();
		void Find();
		void Death();
		MiddleBossLauncher::ePosition LauncherPosition(ePosition mPosition);

		void ResourseLoad();
		void SetColumnPositon(ePosition position) { mPosition = position; }
		void SetMiddleBossColumn(eState state) { mState = state; }
		eState GetMiddleBossColumnState() { return mState; }
		ePosition GetColunmPositon() { return mPosition; }

	private:
		bool mCreatLauncher;
		float mPlayerDistance;
		eState mState;
		ePosition mPosition;

		float mTime;
	};
}