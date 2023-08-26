#pragma once
#include "sbScene.h"
#include "sbSound.h"
namespace sb
{
	class Mission1 : public Scene
	{
	public:
		Mission1();
		virtual ~Mission1();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		float mEndTime;
		bool mColliderRender;
		GameObject* mCamera;
		Sound* mSound;
	};
}

