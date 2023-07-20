#pragma once
#include "sbGameObject.h"

namespace sb
{
	class PlayerTop : public GameObject
	{
	public:
		PlayerTop();
		virtual ~PlayerTop();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		static math::Vector2 GetPlayerPosition() { return mPlayposition; }

	private:
		static math::Vector2 mPlayposition;
	};

}
