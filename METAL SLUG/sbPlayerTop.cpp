#include "sbPlayerTop.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimator.h"

namespace sb
{
	math::Vector2 PlayerTop::mPlayposition = {};

	PlayerTop::PlayerTop()
	{
	}
	PlayerTop::~PlayerTop()
	{
	}
	void PlayerTop::Initialize()
	{
	}
	void PlayerTop::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent <Animator>();

		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 1000.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 1000.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 1000.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{

			pos.x += 1000.0f * Time::DeltaTime();
		
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			anim->PlayAnimation(L"PlayerrightTAX", true);
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			anim->PlayAnimation(L"PlayerIdlerightTAX", true);
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			anim->PlayAnimation(L"PlayerleftTAX", true);
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			anim->PlayAnimation(L"PlayerIdleleftTAX", true);
		}

		if (Input::GetKeyDown(eKeyCode::ZERO))
		{
			anim->PlayAnimation(L"PlayerdeadTAX", true);

		}
		
		tr->SetPosition(pos);
		mPlayposition = pos;
	}
	void PlayerTop::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}