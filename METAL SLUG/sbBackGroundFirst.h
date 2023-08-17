#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BackGroundFirst : public GameObject
	{
	public:

		BackGroundFirst();
		virtual ~BackGroundFirst();

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
