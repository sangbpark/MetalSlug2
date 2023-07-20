#pragma once
#include "Commoninclude.h"

namespace sb
{
	class Time
	{
	public:

		static void Initailize();
		static void Update();
		static void Render(HDC hdc);
		
		__forceinline static float DeltaTime() { return mDeltaTime; }
	private:

		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;
	};
}

