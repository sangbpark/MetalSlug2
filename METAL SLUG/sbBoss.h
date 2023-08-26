#pragma once
#include "sbGameObject.h"

namespace sb
{
	class Boss : public GameObject
	{
	public:
		enum class eBossStage
		{
			Meet,
			Stage1,
			Stage2,
			Death,
			Ready,
			Attack,
			Rest
		};

		Boss();
		virtual ~Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Meet();
		void Stage1();
		void Stage2();
		void Death();
		void Ready();
		void Attack();
		void Rest();

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;



		eBossStage GetBossStage() { return mBossStage; }
		void SetBossStage(eBossStage bossstage) { mBossStage = bossstage; }
		void CreateArabian(bool direct);
		void ResourceLoad();

		void Hit();
		void HeavyBulletCollsionEnter(Collider* other);
		void NormalBulletCollsionEnter(Collider* other);
		void EfBombCollsionEnter(Collider* other);
		void CamelBulletCollisionEnter(Collider* other);

	private:
		eBossStage mBossStage;
		float mHp;
		float mSpeed;
		bool mUpDown;
		int mCount;
		bool mDirect;
		bool mHit;
		bool mStage2On;
		float mArabianTime;
		float mDestroy;
	};
}

