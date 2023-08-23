#pragma once
#include "sbGameObject.h"

namespace sb
{
	class CamelGun : public GameObject
	{
	public:
		CamelGun();
		virtual ~CamelGun();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void ResourseLoad();

		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		GameObject* mOwner;
	};
}