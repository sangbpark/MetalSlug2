#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BackGround : public GameObject
	{
	public:
		enum class eStage
		{
			First,
			Second,
			Last,
			End
		};
		BackGround();
		virtual ~BackGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void RenderBackGround();
		void SetStage(eStage stage) { mStage = stage; }

	private:
		float mPlayerDistance;
		bool mRender;
		eStage mStage;
	};
}

