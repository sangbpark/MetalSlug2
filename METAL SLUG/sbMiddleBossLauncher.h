#pragma once
#include "sbGameObject.h"
#include "sbMiddleBossRocket.h"
namespace sb
{
	class MiddleBossLauncher : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Fire,
			Death,
			End
		};
		enum class ePosition
		{
			Left,
			Middle,
			Right,
			End
		};

		MiddleBossLauncher();
		virtual ~MiddleBossLauncher();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Fire();
		void Death();
		MiddleBossRocket::ePosition GetPosition(ePosition position);
		void DeathRocket();

		void Hit();
		void SetLauncherPositon(ePosition position) { mPosition = position; }
		eState GetMiddleBossLauncher() { return mState; }
		void SetmOwner(GameObject* owner) { mOwner = owner; }
		void ResourceLoad();

		void HeavyBulletCollisionEnter(Collider* other);
		void NormalBulletCollisionEnter(Collider* other);

	private:

		float mHp;
		float mFireTime;
		bool mHit;
		std::vector<MiddleBossRocket*> mMiddleBossRocket;
		GameObject* mOwner;
		ePosition mPosition;
		eState mState;
	};
}
