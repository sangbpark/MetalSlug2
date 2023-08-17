#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BackGroundLast : public GameObject
	{
	public:

		BackGroundLast();
		virtual ~BackGroundLast();

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

