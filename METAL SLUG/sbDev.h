#pragma once
#include "sbGameObject.h"

namespace sb
{
	class Dev : public GameObject
	{
	public:
		Dev();
		virtual ~Dev();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}