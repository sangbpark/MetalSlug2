#pragma once
#include "sbGameObject.h"

namespace sb
{
#define Scale 95.0f
	class Arabian : public GameObject
	{
	public:
		enum class Arabianstate
		{
			idle,
			patrol,
			rockon,
			prepare,
			attack,
			death,
		};
		Arabian();
		virtual ~Arabian();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Death();
		void RockOn();
		void Patrol();
		void Prepare();
		void Attack();

		void ResourceLoad();

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void NormalBulletCollsionEnter(Collider* other);
		void EfBombCollsionEnter(Collider* other);
	private:
		bool mDirect;
		float mMoveDistance;
		float mTimecheck;
		float mPlayerDistance;
		int mPatrolCount;
		Arabianstate mState;
	};
}

