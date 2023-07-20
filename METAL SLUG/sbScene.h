#pragma once
#include "sbEntity.h"
#include "sbLayer.h"

namespace sb

{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddGameObject(enums::eLayerType type, GameObject* gameObj)
		{
			mLayers[(int)type].AddGameObject(gameObj);
		}

		Layer& GetLayer(enums::eLayerType type) { return mLayers[(UINT)type]; }

	private:
		std::vector<Layer> mLayers;
	};
}

