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
		//switch (mState)
		//{
		//case sb::Npc::eState::death:
		//	Death();
		//	break;
		//case sb::Npc::eState::Idle:
		//	Idle();
		//	break;
		//case sb::Npc::eState::rockon:
		//	RockOn();
		//	break;
		//case sb::Npc::eState::attack:
		//	Attack();
		//	break;
		//case sb::Npc::eState::prepare:
		//	Prepare();
		//	break;
		//case sb::Npc::eState::patrol:
		//	Patrol();
		//	break;
		//default:
		//	break;
		//}
	}
	void Npc::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}