#pragma once
#include "sbEntity.h"
#include "sbGameObject.h"

namespace sb
{
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameobj)
		{
			mGameObjects.push_back(gameobj);
		}

		std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }
	private:
		std::vector<GameObject*> mGameObjects;
	};

}
