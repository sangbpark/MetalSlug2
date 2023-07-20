#pragma once
#include "sbScene.h"
#include "sbGameObject.h"
#include "sbSceneManager.h"

namespace sb::object
{
	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);

		return gameObject;
	}
}