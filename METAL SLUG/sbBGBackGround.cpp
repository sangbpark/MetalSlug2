#include "sbBGBackGround.h"
#include "sbPlayerBottom.h"
#include "sbTransform.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbTransform.h"
#include "sbAnimator.h"


namespace sb
{
	BGBackGround::BGBackGround()
		:mPlayerDistance(0.0f)
	{
		ResourseLoad();
	}
	BGBackGround::~BGBackGround()
	{
	}
	void BGBackGround::Initialize()
	{
	}
	void BGBackGround::Update()
	{

		GameObject::Update();

	}
	void BGBackGround::Render(HDC hdc)
	{

		GameObject::Render(hdc);

	}
	void BGBackGround::ResourseLoad()
	{
		Texture* imageBGboss = Resources::Load<Texture>(L"Mission1bossbackground"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1 bossground.bmp");
		Transform* tr = AddComponent<Transform>();
		Animator* at = AddComponent<Animator>();
		at->CreateAnimation(L"mission1bossbackgroundAX", imageBGboss
			, Vector2(0.0f, 0.0f), Vector2(307.0f, 208.0f), 4);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"mission1bossbackgroundAX", true);
	}
}