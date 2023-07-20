#include "sbBackGround.h"

namespace sb
{
	BackGround::BackGround()
	{
	}
	BackGround::~BackGround()
	{
	}
	void BackGround::Initialize()
	{
	}
	void BackGround::Update()
	{
		GameObject::Update();
	}
	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}