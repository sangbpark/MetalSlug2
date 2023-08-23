#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>
#include <bitset>

#include <assert.h>


#include "framework.h"
#include "sbMath.h"

#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

namespace sb::enums
{
	enum class eLayerType
	{
		Backgroud,
		Floor,
		Monster,
		BossMonster,
		Vehicle,
		Npc,
		Player,
		Effects,
		FrontBackGround,
		UI,
		ControlTower,
		End,
	};
	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		Rigidbody,
		End,
	};
}