#pragma once
#include "sbGameObject.h"

namespace sb
{
	class sbNormalBullet : public GameObject
	{
	public:
		enum class eBulletState
		{
			Up,
			Down,
			Left,
			Right,
			death,
		};
		sbNormalBullet();
		virtual ~sbNormalBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ResourceLoad();

		void SetState(eBulletState state) { mState = state; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void ArabianDeath(Collider* other);
		void MiddleBossLauncherEnter(Collider* other);
		void FloorEnter(Collider* other);
		void HOldManEnter(Collider* other);
		void TruckCollisionEnter(Collider* other);
		void BerserkerCollisionEnter(Collider* other);
	private:
		eBulletState mState;
		float mDeathTime;
		bool mCreat;
	};
}