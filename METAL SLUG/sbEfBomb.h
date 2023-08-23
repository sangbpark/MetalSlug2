
#pragma once
#include "sbGameObject.h"

namespace sb
{
#define EfBomb1_Jump -600.0f
#define EfBomb2_Speed 300.0f
#define EfBomb2_Jump -400.0f
	class EfBomb : public GameObject
	{
	public:
		enum class BombState
		{
			first,
			move,
			second,
			secondMove,
			death,

		};
		EfBomb();
		virtual ~EfBomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetDirect(bool BombDirect) { mBombDirect = BombDirect; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void First();
		void Move();
		void Second();
		void SecondMove();
		void Death();

		void FloorCollisionEnter(Collider* other);
		void HOldManCollisionEnter(Collider* other);
		void ArabianCollisionEnter(Collider* other);
		void MiddleBossRocketCollisionEnter(Collider* other);
		void TruckCollisionEnter(Collider* other);
		void BossCollisionEnter(Collider* other);

	private:
		bool mBombDirect;
		float mEfBomb1Speed;
		float mDeathTime;
		int mCount;
		BombState mState;
	};
}