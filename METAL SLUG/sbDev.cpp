#include "sbDev.h"

#include "sbTransform.h"
#include "sbInput.h"
#include "sbTime.h"

	namespace sb
	{
		Dev::Dev()
		{
		}
		Dev::~Dev()
		{
		}
		void Dev::Initialize()
		{
		}
		void Dev::Update()
		{
			GameObject::Update();

			Transform* tr = GetComponent<Transform>();
			math::Vector2 pos = tr->GetPosition();


			if (Input::GetKey(eKeyCode::W))
			{
				pos.y -= 500.0f * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::A))
			{
				pos.x -= 500.0f * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::S))
			{
				pos.y += 500.0f * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::D))
			{
				pos.x += 500.0f * Time::DeltaTime();
			}

			tr->SetPosition(pos);
		}
		void Dev::Render(HDC hdc)
		{
			GameObject::Render(hdc);
		}
}