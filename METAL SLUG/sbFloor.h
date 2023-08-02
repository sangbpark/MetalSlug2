#pragma once
#include "sbGameObject.h"

namespace sb
{
#define Size_Error 40.0f
	class Floor :public GameObject
	{
	public:
		Floor();
		~Floor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void ResourceLoad();

		void PlayerColliderEnter(Collider* other);
		void PlayerColliderExit(Collider* other);
		void EfBombColliderEnter(Collider* other);
		void EfBombColliderExit(Collider* other);
		void ArabianColliderEnter(Collider* other);
		void ArabianColliderExit(Collider* other);


	};
}

