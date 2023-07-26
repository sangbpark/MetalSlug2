#pragma once
#include "sbGameObject.h"

namespace sb
{
	
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
			bomb,
			jump,
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
<<<<<<< HEAD
		void Down();

		static math::Vector2 GetPlayerPosition() { return mPlayposition; }
		static bool Getground() { return mGround; }
=======
		
		static math::Vector2 GetPlayerPosition() { return mPlayposition; }
	
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
	private:
		static math::Vector2 mPlayposition;
		eState mState;
		bool mDirect;
<<<<<<< HEAD
		static bool mGround;
=======
		
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
	};
}