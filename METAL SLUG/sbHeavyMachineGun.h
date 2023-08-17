#pragma once
#include "sbGameObject.h"

namespace sb
{
	class HeavyMachineGun : public GameObject
	{
	public:
		HeavyMachineGun();
		virtual ~HeavyMachineGun();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void ResourseLoad();

	private:
		float mDeathTime;
	};
}
