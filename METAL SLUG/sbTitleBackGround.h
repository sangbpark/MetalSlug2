#pragma once
class TitleBackGround
{
};

#pragma once
#include "sbGameObject.h"

namespace sb
{
	class TitleBackGround : public GameObject
	{
	public:

		TitleBackGround();
		virtual ~TitleBackGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		
	};
}
