#include "sbBackGroundFirst.h"
#include "sbTransform.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbAnimator.h"
#include "sbPlayerBottom.h"

namespace sb
{
	BackGroundFirst::BackGroundFirst()
		: mPlayerDistance(0.0f)
	{
		ResourceLoad();
	}
	BackGroundFirst::~BackGroundFirst()
	{
	}
	void BackGroundFirst::Create()
	{
	}
	void BackGroundFirst::Idle()
	{
	}
	void BackGroundFirst::Initialize()
	{
	}
	void BackGroundFirst::Update()
	{
		GameObject::Update();
	}
	void BackGroundFirst::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BackGroundFirst::ResourceLoad()
	{
		Texture* imageBG = Resources::Load<Texture>(L"Mission1BackGround"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1d1.bmp");
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		Transform* tr = AddComponent<Transform>();
		sr->SetImage(imageBG);
		sr->SetScale(Vector2(4.5f, 4.5f));
	}
}