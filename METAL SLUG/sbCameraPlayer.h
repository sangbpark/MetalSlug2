#pragma once
#include "sbGameObject.h"

namespace sb
{
	class CameraPlayer : public GameObject
	{
	public:
		CameraPlayer();
		virtual ~CameraPlayer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		
	};
}
