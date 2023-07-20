#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BGbossCanopi : public GameObject
	{
	public:
		BGbossCanopi();
		virtual ~BGbossCanopi();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}
