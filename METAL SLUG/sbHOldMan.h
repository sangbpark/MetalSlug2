#pragma once
#include "sbGameObject.h"

namespace sb
{
	class HOldMan : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Free,
			Item,
			death,
			end
		};
		enum class eItems
		{
			Heavy,
			Supply,
			end
		};
		HOldMan();
		virtual ~HOldMan();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Free();
		void Item();
		void Death();

		void ResourceLoad();

		void SetItems(eItems items) { mItems = items; }
		eState GetHOldManState() { return mState; }


		void HeavyBulletCollsionEnter(Collider* other);
		void EfBombCollsionEnter(Collider* other);
		void NormalBulletCollsionEnter(Collider* other);

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		eState mState;
		eItems mItems;
		float mPlayerDistance;
	};
}
