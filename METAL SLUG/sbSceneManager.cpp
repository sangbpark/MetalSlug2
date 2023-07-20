#include "sbSceneManager.h"
#include "sbMission1.h"
#include "sbTitleScene.h"
#include "sbInput.h"


namespace sb
{
	std::map<std::wstring, Scene* > SceneManager::mScene = {};
	Scene* SceneManager::mActiveScene = nullptr;


	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<Mission1>(L"Mission1");

		LoadScene(L"Mission1");
	}

	void SceneManager::Update()
	{
	
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScene.find(name);

		if (iter == mScene.end())
			return nullptr;

		mActiveScene = iter->second;

		return iter->second;
	}
}