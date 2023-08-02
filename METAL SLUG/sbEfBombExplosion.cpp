#include "sbEfBombExplosion.h"
#include "sbTransform.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbAnimator.h"
namespace sb
{
	EfBombExplosion::EfBombExplosion()
	{
		Texture* images = Resources::Load<Texture>(L"PlayerBombDeath",
			L"..\\Resource\\effect\\Bombexplosion.bmp");
		Animator* ar = this->AddComponent<Animator>();
		ar->CreateAnimation(L"BombDeathAX", images, Vector2(0.0f, 0.0f), Vector2(88.0f, 122.0f), 20, Vector2(0.0f, -100.0f), 0.05f);
		ar->SetScale(Vector2(2.0f,2.0f));
		ar->PlayAnimation(L"BombDeathAX");
		Transform* tr = this->AddComponent<Transform>();
	}
	EfBombExplosion::~EfBombExplosion()
	{
	}
	void EfBombExplosion::Initialize()
	{
	}
	void EfBombExplosion::Update()
	{
		GameObject::Update();
		Animator* ar = GetComponent<Animator>();
		if (ar->Getcomplete())
		{
			Destroy(this);
		}

	}
	void EfBombExplosion::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}