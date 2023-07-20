#pragma once
#include "Commoninclude.h"
#include "sbScene.h"

namespace sb
{
	using namespace math;
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();

		HWND GetHwnd() { return mHwnd; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() {	return mHdc;}

	private:
		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;

		HDC mBackHdc;
		HBITMAP mBackBuffer;
	
	};
}

