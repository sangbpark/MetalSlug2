#pragma once
#include "sbGameObject.h"

namespace sb
{
	class PlayerTop : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Down,
			Death,
			attack,
			bomb,
			jump,
			stay,
			End,
		};


		PlayerTop();
		virtual ~PlayerTop();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Move();
		void Death();
		void Attack();
		void Bomb();
		void Jump();
		void Down();
		void Stay();

		static math::Vector2 GetPlayerPosition() { return mPlayposition; }

	private:
		static math::Vector2 mPlayposition;
		eState mState;
		bool mDirect;
		bool mbGround;

	};
}
