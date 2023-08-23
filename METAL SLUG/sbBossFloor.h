#pragma once
#include "sbGameObject.h"

namespace sb
{
#define Size_Error 40.0f
	class BossFloor :public GameObject
	{
	public:
		BossFloor();
		~BossFloor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetBossFloorOwner(GameObject* owner) { mOwner = owner; }

		void ArabianColliderEnter(Collider* other);
		void ArabianColliderExit(Collider* other);
	private:
		GameObject* mOwner;
	};
}