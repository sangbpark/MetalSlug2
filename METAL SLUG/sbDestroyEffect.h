#pragma once
#include "sbGameObject.h"

namespace sb
{
	class DestroyEffect : public GameObject
	{
	public:
		DestroyEffect();
		virtual ~DestroyEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ResourseLoad();

	private:
	};
}
