#pragma once
#include "sbEntity.h"
#include "sbComponent.h"

namespace sb
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		template <typename T>
		T* GetComponent()
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				comp = dynamic_cast<T*>(c);
				if (comp != nullptr)
					return comp;
			}

			return comp;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			mComponents.push_back(comp);
			comp->SetOwner(this);

			return comp;

		}
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		std::vector<Component*> mComponents;
	};
}

