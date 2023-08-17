#include "sbMiddleBossSmoke.h"
#include "sbTransform.h"
#include "sbAnimator.h"
#include "sbTexture.h"
#include "sbResources.h"

namespace sb
{
	MiddleBossSmoke::MiddleBossSmoke()
	{
		ResourceLoad();
	}
	MiddleBossSmoke::~MiddleBossSmoke()
	{
	}
	void MiddleBossSmoke::Initialize()
	{
	}
	void MiddleBossSmoke::Update()
	{
		GameObject::Update();
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
			Destroy(this);
	}
	void MiddleBossSmoke::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void MiddleBossSmoke::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"middlebosssmoke",
			L"..\\Resource\\effect\\MiddleRocketSmoke.bmp");
		Transform* tr = this->AddComponent<Transform>();
		Animator* at = AddComponent<Animator>();
		at->CreateAnimation(L"middlerocketAX", image, Vector2(0.0f, 0.0f), Vector2(88.0f, 88.0f), 26);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"middlerocketAX");
	}
}
