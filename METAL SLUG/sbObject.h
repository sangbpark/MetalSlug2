#pragma once
#include "sbScene.h"
#include "sbGameObject.h"
#include "sbSceneManager.h"
#include "sbTransform.h"

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

	template <typename T>
	static __forceinline T* Instantiate(eLayerType type, math::Vector2 position)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);
		gameObject->Initialize();
		gameObject->GetComponent<Transform>()->SetPosition(position);

		return gameObject;
	}
}