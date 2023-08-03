#pragma once
#include "sbGameObject.h"

namespace sb
{
	class Arabianknife : public GameObject
	{
	public:
		Arabianknife();
		virtual ~Arabianknife();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
	};
}
