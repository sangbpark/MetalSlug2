#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BerserkerKnife : public GameObject
	{
	public:
		BerserkerKnife();
		virtual ~BerserkerKnife();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Death();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		
	};
}

