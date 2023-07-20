#pragma once
#include "sbGameObject.h"

namespace sb
{
	class FrontBackGround : public GameObject
	{
	public:
		FrontBackGround();
		virtual ~FrontBackGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}