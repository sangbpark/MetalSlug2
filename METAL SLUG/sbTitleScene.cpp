#include "sbTitleScene.h"
#include "sbPlayer.h"
#include "sbSpriteRenderer.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbBackGround.h"
#include "sbInput.h"
#include "sbTransform.h"
#include "sbCamera.h"

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
		
		BackGround* TitleBackGround = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		SpriteRenderer* sr = TitleBackGround->AddComponent<SpriteRenderer>();
		Transform* tr = TitleBackGround->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x = 690.0f;
		pos.y = 650.0f;
		tr->SetPosition(pos);
		sr->SetAffectedCamera(false);
		sr->SetImage(image);
		sr->SetScale(Vector2(0.92f, 0.7f));

		Camera::SetTarget(TitleBackGround);
	}
	void TitleScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::ESC))
		{
			SceneManager::LoadScene(L"Mission1");
		}
		Camera::Update();
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}