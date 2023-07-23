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
			Death,
			attack,
			bomb,
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
		void Dead();
		void Attack();
		void Bomb();
		
		static math::Vector2 GetPlayerPosition() { return mPlayposition; }

	private:
		static math::Vector2 mPlayposition;
		eState mState;
		bool mDirect;
	};
}