#include "sbEndScene.h"
#include "sbSpriteRenderer.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbBackGround.h"
#include "sbInput.h"
#include "sbTransform.h"
#include "sbCamera.h"
#include "sbTitleBackGround.h"
#include "sbGameObject.h"
#include "sbTitleCamera.h"
#include "sbLoadingScene.h"

namespace sb
{
	EndScene::EndScene()
	{
	}
	EndScene::~EndScene()
	{
	}
	void EndScene::Initialize()
	{
		Texture* image = Resources::Load<Texture>(L"EndBackGround"
			, L"..\\Resource\\Title\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - MSX Ending Artwork.bmp");

		TitleBackGround* EndBackGround = object::Instantiate<TitleBackGround>(enums::eLayerType::Backgroud);
		SpriteRenderer* sr = EndBackGround->AddComponent<SpriteRenderer>();
		Transform* tr = EndBackGround->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x = 0.0f;
		pos.y = 0.0f;
		tr->SetPosition(pos);
		sr->SetAffectedCamera(false);
		sr->SetImage(image);
		sr->SetScale(Vector2(3.25f, 2.8f));
		TitleCamera* tc = object::Instantiate<TitleCamera>(enums::eLayerType::Backgroud);
		mCamera = tc;
		Camera::SetTarget(tc);
		Sound* sound = Resources::Load<Sound>(L"EndSound"
			, L"..\\Resource\\Sound\\02-THE-MILITARY-SYSTEM-_Operation-Explanation_-Ranking_.wav");
		mSound = sound;
		mSound->SetVolume(500.0f);
	}
	void EndScene::Update()
	{
		if (LoadingScene::GetSceneLoading())
		{
			mSound->Play(true);
			LoadingScene::SetSceneLoading(false);
		}

		Scene::Update();
		Camera::SetTarget(mCamera);
		Camera::Update();
	}
	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		LoadingScene::Render(hdc);
		if (!LoadingScene::GetSceneNext())
			LoadingScene::SetSceneLoading(false);
	}
}