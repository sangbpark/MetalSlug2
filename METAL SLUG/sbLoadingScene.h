#pragma once
#include "sbEntity.h"
class LoadingScene
{
};

namespace sb

{
	class LoadingScene : public Entity
	{
	public:
		LoadingScene();
		 ~LoadingScene();

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static void SetSceneLoading(bool value) { mSceneLoading = value; }
		static bool GetSceneLoading() { return mSceneLoading; }

		static void SetSceneNext(bool value) { mSceneNext = value; }
		static bool GetSceneNext() { return mSceneNext; }

	private:
		static bool mSceneLoading;
		static bool mSceneNext;
	};
}