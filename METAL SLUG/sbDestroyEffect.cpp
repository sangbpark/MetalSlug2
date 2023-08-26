#include "sbDestroyEffect.h"
#include "sbTransform.h"
#include "sbAnimator.h"
#include "sbTexture.h"
#include "sbResources.h"

namespace sb
{
	DestroyEffect::DestroyEffect()
	{
		ResourseLoad();
	}
	DestroyEffect::~DestroyEffect()
	{
	}
	void DestroyEffect::Initialize()
	{
	}
	void DestroyEffect::Update()
	{
		GameObject::Update();
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			this->Pause();
		}
	}
	void DestroyEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DestroyEffect::ResourseLoad()
	{
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Texture* image = Resources::Load<Texture>(L"DestoryEffect",
			L"..\\Resource\\effect\\middlebossdeath.bmp");
		at->CreateAnimation(L"DestroyAX", image, Vector2(0.0f, 0.0f), Vector2(44.0f, 44.0f), 28, Vector2(0.0f, 0.0f));
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"DestroyAX");
	}
}