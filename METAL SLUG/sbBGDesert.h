#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BGDesert : public GameObject
	{
	public:
		BGDesert();
		virtual ~BGDesert();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}
