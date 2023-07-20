#pragma once
#include "sbEntity.h"

namespace sb
{
	class Component : public Entity
	{
	public:
		Component(enums::eComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
	
		void SetOwner(class GameObject* owner) { mOwner = owner; }
		class GameObject* GetOwner() { return mOwner; }

	private:
		const enums::eComponentType mType;
		class GameObject* mOwner;
	};
}

