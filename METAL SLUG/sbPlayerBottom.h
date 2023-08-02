#pragma once
#include "sbGameObject.h"

namespace sb
{
#define Player_Speed 400.0f
#define Player_DownSpeed 200.0f
	class PlayerBottom : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Down,
			Death,
			attack,
			jumpattack,
			jumpdownattack,
			jumpdown,
			bomb,
			jump,
			Downattack,
			DownBomb,
			End,
		};


		PlayerBottom();
		virtual ~PlayerBottom();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Move();
		void Death();
		void Jump();
		void Attack();
		void Bomb();
		void Down();
		void DownAttack();
		void DownBomb();
		void JumpAttack();
		void JumpDownAttack();
		void JumpDown();

		void ResourceLoad();

		static math::Vector2 GetPlayerPosition() { return mPlayposition; }
		static bool Getground() { return mGround; }
		static bool GetComplete() { return mComplete; }
		class Texture* mFloorTexture;
	

	private:
		static math::Vector2 mPlayposition;
		eState mState;
		bool mDirect;
		bool mKeyUp;
		bool mFree;
		bool mRun;
		bool mLateDirect;

		static bool mComplete;
		static bool mGround;

	};
}