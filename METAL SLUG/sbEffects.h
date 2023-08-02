#pragma once
#include "sbGameObject.h"

namespace sb
{
	class Effects : public GameObject
	{
	public:
		Effects();
		virtual ~Effects();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}