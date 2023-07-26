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
<<<<<<< HEAD
			stay,
=======
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
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
<<<<<<< HEAD
		void Down();
		void Stay();
=======
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77

		static math::Vector2 GetPlayerPosition() { return mPlayposition; }

	private:
		static math::Vector2 mPlayposition;
		eState mState;
		bool mDirect;
		bool mbGround;
	};
}
