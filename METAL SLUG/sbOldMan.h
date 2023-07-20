#pragma once
#include "sbGameObject.h"

namespace sb
{
	class OldMan : public GameObject
	{
	public:
		OldMan();
		virtual ~OldMan();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}
