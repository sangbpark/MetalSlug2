#include "sbEffects.h"

namespace sb
{
	Effects::Effects()
	{
	}
	Effects::~Effects()
	{
	}
	void Effects::Initialize()
	{
	}
	void Effects::Update()
	{
		GameObject::Update();
	}
	void Effects::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}