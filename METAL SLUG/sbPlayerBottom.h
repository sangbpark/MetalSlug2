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
			Downmove,
			Death,
			attack,
			jumpattack,
			jumpbomb,
			jumpdownattack,
			jumpdown,
			bomb,
			jump,
			Downattack,
			DownBomb,
			revive,
			Stopanimator,
			Stop,
			RIde,
			Victory,
			RideVictory,
			End,
		};

		enum class eWeaponState
		{
			normal,
			heavy,
			End
		};


		PlayerBottom();
		virtual ~PlayerBottom();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void ArabianKnifeColliderEnter(Collider* other);
		void MiddleRocketColliderEnter(Collider* other);
		void BerserkerKnifeColliderEnter(Collider* other);
		void BossWingColliderEnter(Collider* other);

		void Idle();
		void Move();
		void Death();
		void Jump();
		void Attack();
		void Bomb();
		void Down();
		void DownMove();
		void DownAttack();
		void DownBomb();
		void JumpAttack();
		void JumpBomb();
		void JumpDownAttack();
		void JumpDown();
		void Stop();
		void StopAnimator();
		void Ride();
		void Victory();

		void VictoryOn();
		void RideVictory0n();
		void RideVictory();

		void RideOn();
		void RideOff();

		void Revive();
		void Clear();
		void ResourceLoad();
		



		static math::Vector2 GetPlayerPosition() { return mPlayposition; }
		bool Getground() { return mGround; }
		bool GetComplete() { return mComplete; }
		bool GetDirect() { return mDirect; }
		eState GetState() { return mState; }
		eWeaponState GetWeaponState() { return mWeaponState; }
		bool GetChange() {return mChange;}
		void SetChange(bool change) { mChange = change; }
		void SetWeaponState(eWeaponState weaponsatate) { mWeaponState = weaponsatate; }
		void SetHeavyBulletCount(int bullet) { mHeavyBulletCount += bullet; }
		void SetEfBombCount(int count) { mEfBombCount += count; }
		int GetHeavyBulletCount() { return mHeavyBulletCount; }
		int GetEfBombCount() { return mEfBombCount; }
		void SetCameraTransform(math::Vector2 value) { mCameraTransform = value; }
		bool GetStopState() { return mStop; }
		void SetStopState(bool stop) { mStop = stop; }
		void SetPlayerRide(bool ride) { mRide = ride; }
		bool GetRide() { return mRide; }
		void SetInvincible(float value) { mInvincible = value; }
		void SetVehicle(GameObject* vehicle) { mVehicle = vehicle; }
		bool GetVictory() { return mVictory; }
		//class Texture* mFloorTexture;
	
		math::Vector2 CameraOut(math::Vector2 value);
	private:
		static math::Vector2 mPlayposition;
		eState mState;
		bool mDirect;
		bool mChange;
		bool mKeyUp;
		bool mFree;
		bool mRun;
		bool mLateDirect;
		int mHeavyBulletCount;
		int mEfBombCount;
		float PBtimecheck;
		float mInvincible;
		eWeaponState mWeaponState;
		bool mComplete;
		bool mGround;
		bool mStop;
		bool mRide;
		bool mVictory;
		GameObject* mVehicle;
		math::Vector2 mCameraTransform;

	};
}