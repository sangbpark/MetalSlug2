#include "sbBossDeath.h"
#include "sbTransform.h"
#include "sbAnimator.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbSound.h"

namespace sb
{
	BossDeath::BossDeath()
	{
		ResourseLoad();
	}
	BossDeath::~BossDeath()
	{
	}
	void BossDeath::Initialize()
	{
	}
	void BossDeath::Update()
	{
		GameObject::Update();
		Animator* at = GetComponent<Animator>();
		if (at->Getcomplete())
		{
			this->Pause();
		}
	}
	void BossDeath::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossDeath::ResourseLoad()
	{
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Texture* image = Resources::Load<Texture>(L"BossDeath",
			L"..\\Resource\\effect\\bossbomb.bmp");
		at->CreateAnimation(L"bossdeathAX", image, Vector2(0.0f, 0.0f), Vector2(88.0f, 88.0f), 23, Vector2(0.0f, 0.0f));
		at->SetScale(Vector2(8.5f, 5.5f));
		at->PlayAnimation(L"bossdeathAX");
		Sound* sound = Resources::Load<Sound>(L"bossdeath"
			, L"..\\Resource\\sound\\bossDeath (2).wav");
		sound->Play(false);
		sound->SetVolume(60.0f);
	}
}