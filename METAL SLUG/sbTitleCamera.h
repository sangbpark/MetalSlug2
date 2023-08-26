
#pragma once
#include"sbGameObject.h"
namespace sb
{
	class TitleCamera : public GameObject
	{
	public:
		TitleCamera();
		virtual ~TitleCamera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}