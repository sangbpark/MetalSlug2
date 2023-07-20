#pragma once
#include "sbGameObject.h"

namespace sb
{
	class Npc : public GameObject
	{
	public:
		Npc();
		virtual ~Npc();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}
