#pragma once
#include "sbGameObject.h"

namespace sb
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		static math::Vector2 GetPlayerPosition() { return mPlayposition; }

	private:
		static math::Vector2 mPlayposition;
	};
}

