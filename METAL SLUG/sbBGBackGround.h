#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BGBackGround : public GameObject
	{
	public:
		BGBackGround();
		virtual ~BGBackGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ResourseLoad();

	private:

		float mPlayerDistance;
	};
}