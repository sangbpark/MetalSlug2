#include "sbSceneManager.h"
#include "sbMission1.h"
#include "sbTitleScene.h"
#include "sbInput.h"


namespace sb
{
	std::map<std::wstring, Scene* > SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;


	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<Mission1>(L"Mission1");

		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
	
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;

		return iter->second;
	}
}