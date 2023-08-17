#pragma once
#include "sbGameObject.h"

namespace sb
{
	class MiddleBossRocket : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Create,
			Rockon,
			Death,
			End
		};
		enum class ePosition
		{
			Left,
			Middle,
			Right,
			end
		};
		MiddleBossRocket();
		virtual ~MiddleBossRocket();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void HeavyBulletCollisionEnter(Collider* other);
		void NormalBulletCollisionEnter(Collider* other);
		void EfBombCollisionEnter(Collider* other);
		void PlayerCollisionEnter(Collider* other);
		void FloorCollisionEnter(Collider* other);

		void SetMiddleBossRockeDeath();

		void SetMiddleRocketPosition(ePosition position) { mPosition = position; }
		eState GetMiddleRocketState() { return mState; }

		bool GetMiddleRocketDeath() { return mDeath; }

		void Idle();
		void Create();
		void RockOn();
		void Death();


		void ResourceLoad();

	private:
		float mHp;
		float mRockOnTime;
		float mRotation;
		bool mDeath;

		eState mState;
		ePosition mPosition;
	};
}