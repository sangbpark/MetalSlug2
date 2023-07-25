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

	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}