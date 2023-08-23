#pragma once
#include "sbGameObject.h"

namespace sb
{
	class Camel : public GameObject
	{
	public:
		enum class eCamelState
		{
			Ready,
			Idle,
			Move,
			Jump,
			Death,
		};
		Camel();
		virtual ~Camel();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Ready();
		void Idle();
		void Move();
		void Death();
		void Jump();

		void PlayerCollisionEnter(Collider* other);
		void PlayerStateCheck(Collider* other);

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void ResourceLoad();

		void CreatHeavyBullet(float Rotation, math::Vector2 offset = math::Vector2::Zero, bool Down = false);
		eCamelState GetCamelState() { return mState; }
		float GetCamelRotate() { return mRotate; }

	private:
		eCamelState mState;
		bool mRideOn;
		GameObject* mOwner;
		GameObject* mGun;
		float mRotate;
		float mBulletTime;
		float mRideTime;
	};
}