#pragma once
#include "sbGameObject.h"

namespace sb
{
	class CamelBullet : public GameObject
	{
	public:
		enum class eCamelBulletState
		{
			Idle,
			Death
		};
		CamelBullet();
		virtual ~CamelBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ResourceLoad();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Idle();
		void Death();

		void SetDegree(float Degree) { mDegree = Degree; }
		void SetDirect(bool direct) { mDirect = direct; }
		void SetDown(bool down) { mDown = down; }


		void ArabianDeath(Collider* other);
		void FloorEnter(Collider* other);
		void HOldManEnter(Collider* other);
		void MiddleBossLauncherEnter(Collider* other);
		void TruckCollisionEnter(Collider* other);
		void BerserkerCollisionEnter(Collider* other);
		void BossCollisionEnter(Collider* other);

	private:
		eCamelBulletState mState;
		float mDeathTime;
		float mDegree;
		bool mDirect;
		bool mDown;
	};
}