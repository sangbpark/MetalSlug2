#include "sbLayer.h"

namespace sb
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			delete obj;
			obj = nullptr;
		}
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetState() == GameObject::eGameObjectState::Pause)
				continue;

			obj->Update();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetState() == GameObject::eGameObjectState::Pause)
				continue;

			obj->Render(hdc);
		}

		//std::vector<GameObject*> deathObjs = {};
		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->GetState() == GameObject::eGameObjectState::Dead)
			{
				GameObject* deadObj = *iter;
				delete deadObj;
				deadObj = nullptr;
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}