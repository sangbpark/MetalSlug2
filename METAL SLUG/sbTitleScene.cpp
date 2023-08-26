#include "sbTitleScene.h"
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
#include "sbSound.h"
namespace sb
{
	using namespace math;
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Texture* image = Resources::Load<Texture>(L"TitleBackGround"
			, L"..\\Resource\\Title\\Metal Slug 2 Title Screen.png");
		
		TitleBackGround* TitlebackGround = object::Instantiate<TitleBackGround>(enums::eLayerType::Backgroud);
		SpriteRenderer* sr = TitlebackGround->AddComponent<SpriteRenderer>();
		Transform* tr = TitlebackGround->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x = 15.0f;
		pos.y = 365.0f;
		tr->SetPosition(pos);
		sr->SetAffectedCamera(false);
		sr->SetImage(image);
		sr->SetScale(Vector2(1.0f, 0.95f));
		TitleCamera* tc = object::Instantiate<TitleCamera>(enums::eLayerType::Backgroud);
		mCamera = tc;
		Camera::SetTarget(tc);
		Sound* sound = Resources::Load<Sound>(L"titlesound"
			, L"..\\Resource\\Sound\\01-TITLE-_Opening_.wav");
		mSound = sound;
		mSound->SetVolume(500.0f);
	}
	void TitleScene::Update()
	{
		if (LoadingScene::GetSceneLoading())
			mSound->Play(true);

		Scene::Update();
		Camera::SetTarget(mCamera);
		Camera::Update();
		LoadingScene::SetSceneNext(false);
		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			mSound->Stop(false);
			SceneManager::LoadScene(L"Mission1");
			LoadingScene::SetSceneLoading(true);
			LoadingScene::SetSceneNext(true);
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		LoadingScene::Render(hdc);
		if (!LoadingScene::GetSceneNext())
			LoadingScene::SetSceneLoading(false);
	}
}