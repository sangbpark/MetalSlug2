#include "sbLoadingScene.h"
#include "sbApplication.h"

extern sb::Application application;
namespace sb
{
	bool LoadingScene::mSceneLoading = true;
	bool LoadingScene::mSceneNext = false;
	LoadingScene::LoadingScene()
	{
	}
	LoadingScene::~LoadingScene()
	{
	}
	void LoadingScene::Initialize()
	{
	}
	void LoadingScene::Update()
	{
	}
	void LoadingScene::Render(HDC hdc)
	{
		if(mSceneLoading)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
			Rectangle(hdc, -1, -1, application.GetWidth() + 1, application.GetHeight() + 1);
			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
	}
}
