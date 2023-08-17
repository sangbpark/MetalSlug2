#pragma once
#include "sbGameObject.h"

namespace sb
{
	class MiddleBossSmoke : public GameObject
	{
	public:
		MiddleBossSmoke();
		virtual ~MiddleBossSmoke();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ResourceLoad();

	private:

	};
}