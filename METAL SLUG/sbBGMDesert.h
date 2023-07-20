#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BGMDesert : public GameObject
	{
	public:
		BGMDesert();
		virtual ~BGMDesert();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}

class BGMDesert
{
};
