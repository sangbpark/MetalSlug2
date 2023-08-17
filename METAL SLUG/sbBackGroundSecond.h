#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BackGroundSecond : public GameObject
	{
	public:

		BackGroundSecond();
		virtual ~BackGroundSecond();

		void Create();
		void Idle();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ResourceLoad();

	private:
		float mPlayerDistance;
	};
}

