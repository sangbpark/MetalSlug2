#include "sbCameraPlayer.h"
#include "sbTransform.h"
#include "sbPlayerTop.h"
#include "sbInput.h"
#include "sbTime.h"



namespace sb
{
	
	CameraPlayer::CameraPlayer()
	{
	}
	CameraPlayer::~CameraPlayer()
	{
	}
	void CameraPlayer::Initialize()
	{
	}
	void CameraPlayer::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = PlayerTop::GetPlayerPosition();
		math::Vector2 pos2 = tr->GetPosition();

		pos.y = pos2.y;

		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 300.0f * Time::DeltaTime();	
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 300.0f * Time::DeltaTime();
		}
		
		tr->SetPosition(pos);
	}
	void CameraPlayer::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}