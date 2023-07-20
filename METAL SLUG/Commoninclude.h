#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>
#include <bitset>

#include "framework.h"
#include "sbMath.h"

#pragma comment(lib, "Msimg32.lib")

namespace sb::enums
{
	enum class eLayerType
	{
		Backgroud,
		Monster,
		Npc,
		Player,
		Effect,
		FrontBackGround,
		UI,
		End,
	};
	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		End,
	};
}