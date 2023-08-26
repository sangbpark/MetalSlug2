#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BossDeath : public GameObject
	{
	public:
		BossDeath();
		virtual ~BossDeath();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ResourseLoad();

	private:
	};
}
