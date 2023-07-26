#pragma once
#include "sbGameObject.h"

namespace sb
{
	class OldMan : public GameObject
	{
	public:
		OldMan();
		virtual ~OldMan();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
	};
}
