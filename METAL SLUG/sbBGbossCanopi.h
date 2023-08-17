#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BGbossCanopi : public GameObject
	{
	public:
		enum class ePosition
		{
			Left,
			Right,
			End
		};
		enum class eState
		{
			Create,
			Idle,
			End
		};
		BGbossCanopi();
		virtual ~BGbossCanopi();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Create();
		void Idle();

		void ResourseLoad();

		void SetCanopiPosition(ePosition position) { mPosition = position; }

	private:

		ePosition mPosition;
		eState mState;
		float mPlayerDistance;
	};
}
