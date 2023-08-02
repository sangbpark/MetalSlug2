#pragma once
#include "sbGameObject.h"

namespace sb
{
	class EfBombExplosion : public GameObject
	{
	public:
		EfBombExplosion();
		virtual ~EfBombExplosion();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}