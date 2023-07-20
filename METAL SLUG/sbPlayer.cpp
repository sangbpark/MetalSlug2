#include "sbPlayer.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"

namespace sb
{
	math::Vector2 Player::mPlayposition = {};
	Player::Player()
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
	}
	void Player::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();


		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 300.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 300.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
		mPlayposition = pos;
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}