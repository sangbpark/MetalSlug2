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
			Up,
			Move,
			Down,
			Death,
			attack,
			Jumpattack,
			jumpdownattack,
			Upattack,
			jumpbomb,
			jumpdown,
			jumpupattack,
			jumpup,
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
		void Up();
		void UpAttack();
		void JumpDown();
		void JumpAttack();
		void JumpBomb();
		void JumpDownAttack();
		void JumpUpAttack();
		void JumpUp();
	
		void ResourceLoad();

		static math::Vector2 GetPlayerPosition() { return mPlayposition; }
		static bool GetComplete() { return mComplete; }

	private:
		static math::Vector2 mPlayposition;
		eState mState;
		bool mDirect;
		bool mbGround;
		bool mKeyUp;
		bool mLateDirect;

		static bool mComplete;
	};
}
