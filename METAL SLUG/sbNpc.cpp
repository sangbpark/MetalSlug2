#include "sbNpc.h"

namespace sb
{
	Npc::Npc()
	{
	}
	Npc::~Npc()
	{
	}
	void Npc::Initialize()
	{
	}
	void Npc::Update()
	{
		GameObject::Update();
	}
	void Npc::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}