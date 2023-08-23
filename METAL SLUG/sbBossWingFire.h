#pragma once
#include "sbGameObject.h"

namespace sb
{
	class BossWingFire : public GameObject
	{
	public:
		enum class eBossWingFirePosition
		{
			Left,
			Right
		};
		enum class eBossWingFireState
		{
			Create,
			Idle,
			Death,
		};
		BossWingFire();
		virtual ~BossWingFire();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Create();
		void Idle();
		void Death();

		void ResourceLoad();
		void SetOwner(GameObject* owner) { mOwner = owner; }
		void SetBossWingFirePosition(eBossWingFirePosition position) { mPositon = position; }
	private:
		GameObject* mOwner;
		eBossWingFirePosition mPositon;
		eBossWingFireState mState;
	};
}