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
			huping,
			hupdowning,
			hjumpdownuping,
			jumpbomb,
			jumpdown,
			hjumpdowning,
			jumpupattack,
			jumpup,
			bomb,
			jump,
			stay,
			revive,
			StopAnimator,
			Stop,
			Ride,
			End,
		};
		enum class eWeaponState
		{
			normal,
			heavy,
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
		void Ride();

		void HIdle();
		void HMove();
		void HBomb();
		void HJump();
		void HDown();
		void HStay();
		void HUp();
		void HUping();
		void HUpDowning();
		void HJumpDown();
		void HJumpDowning();
		void HJumpDownUping();
		void HJumpAttack();
		void HJumpBomb();
		void HJumpDownAttack();
		void HJumpUpAttack();
		void HJumpUp();

		void StopAnimator();
		void Stop();

		void GetPlayerBottomState();
		void Revive();
		void Clear();

		void CreatHeavyBullet(bool Direct ,float mheavybullet, math::Vector2 offset = math::Vector2::Zero, bool Down = false);
		void CreatEfBomb(eState state);
		void CreatHEfBomb(eState state);
		void ResourceLoad();

		void SetPlayerBottomOnwer(GameObject* Owner) { mPlayerBottomOwner = Owner; }
		static bool GetComplete() { return mComplete; }

	private:
		eState mState;
		bool mDirect;
		bool mbGround;
		bool mKeyUp;
		bool mLateDirect;
		bool mHeavyBulletCount;
		bool mRide;
		float ptTimecheck;
		float mHeavyBullet;
		float mHeavyBullettime;

		GameObject* mPlayerBottomOwner;

		eWeaponState mWeaponState;

		static bool mComplete;
	};
}
