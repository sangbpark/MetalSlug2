#pragma once
#include "sbGameObject.h"
#include "sbBerserkerKnife.h"
namespace sb
{
	class Berserker : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Rest,
			Attack,
			Death,
			End
		};
		Berserker();
		virtual ~Berserker();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void ResourseLoad();

		eState GetBerserkerState() { return mState; }
		void Idle();
		void Rest();
		void Attack();
		void Death();

		void NormalBulletCollsionEnter(Collider* other);
		void HeavyBulletCollsionEnter(Collider* other);
		void EfBombCollsionEnter(Collider* other);


	private:
		eState mState;
		float mHp;
		bool mDirect;
		float mPlayerDistance;

		BerserkerKnife* mberserkerknife;
	};
}

