#pragma once
#include "sbGameObject.h"

namespace sb
{
	class Truck : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Drive,
			Drop,
			Destroy,
			Death,
			Create,
			End
		};
		Truck();
		virtual ~Truck();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void Idle();
		void Drive();
		void Drop();
		void Destroy();
		void Death();
		void Create();

		void Hit();

		eState GetTruckState() { return mState; }

		void NormalBulletCollsionEnter(Collider* other);
		void HeavyBulletCollsionEnter(Collider* other);
		void EfBombCollsionEnter(Collider* other);


		void CreateBerserker();
		void ResourceLoad();
	private:
		eState mState;
		float mHp;
		float mCreateBerserkerTime;
		bool mHit;
		int mBerserkerCount;
	};
}