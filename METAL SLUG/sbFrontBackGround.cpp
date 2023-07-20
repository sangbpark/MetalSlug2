#include "sbFrontBackGround.h"

namespace sb
{
	FrontBackGround::FrontBackGround()
	{
	}
	FrontBackGround::~FrontBackGround()
	{
	}
	void FrontBackGround::Initialize()
	{
	}
	void FrontBackGround::Update()
	{
		GameObject::Update();
	}
	void FrontBackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}