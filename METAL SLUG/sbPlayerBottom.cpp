#include "sbPlayerBottom.h"
#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbAnimator.h"

namespace sb
{
	math::Vector2 PlayerBottom::mPlayposition = {};

	PlayerBottom::PlayerBottom()
	{
	}
	PlayerBottom::~PlayerBottom()
	{
	}
	void PlayerBottom::Initialize()
	{
	}
	void PlayerBottom::Update()
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
			anim->PlayAnimation(L"PlayerrightBAX", true);
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			anim->PlayAnimation(L"PlayerIdlerightBAX", true);
		}

		if (Input::GetKeyDown(eKeyCode::A))
		{
			anim->PlayAnimation(L"PlayerleftBAX", true);
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			anim->PlayAnimation(L"PlayerIdleleftBAX", true);
		}

		if (Input::GetKeyDown(eKeyCode::ZERO))
		{
			anim->PlayAnimation(L"PlayerdeadBAX", true);

		}



		tr->SetPosition(pos);
	
	}
	void PlayerBottom::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}