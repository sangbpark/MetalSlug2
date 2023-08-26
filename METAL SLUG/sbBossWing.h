#pragma once
#include "sbGameObject.h"
#include "sbSound.h"

namespace sb
{
	class BossWing : public GameObject
	{
	public:
		enum class eWingState
		{
			Create,
			Idle,
			Charge,
			Attack,
			Rest
		};
		enum class eWingPosition
		{
			Left,
			Right
		};
		BossWing();
		virtual ~BossWing();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Create();
		void Idle();
		void Charge();
		void Attack();
		void Rest();

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetWingState(eWingState wingstate) { mWingState = wingstate; }
		void SetWingPosition(eWingPosition wingposition) { mWingPosition = wingposition; }
		void SetWingOwner(GameObject* owner) { mOwner = owner; }

		void ResourceLoad();

	private:
		eWingState mWingState;
		eWingPosition mWingPosition;
		GameObject* mOwner;
		Sound* mSound;
		Sound* mAttackSound;
	};
}
