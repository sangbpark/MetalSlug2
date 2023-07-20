#pragma once
#include "sbGameObject.h"

namespace sb
{
	class MiddleBoss : public GameObject
	{
	public:
		MiddleBoss();
		virtual ~MiddleBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}

