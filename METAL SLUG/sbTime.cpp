#include "sbTime.h"

namespace sb
{

	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f;


	void Time::Initailize()
	{
		QueryPerformanceFrequency(&mCpuFrequency);

		QueryPerformanceCounter(&mPrevFrequency);
	}
	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequency
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}
	void Time::Render(HDC hdc)
	{
		static float timeCheck = 0.0f;

		timeCheck += mDeltaTime;
		if (timeCheck >= 1.0f)
		{
			wchar_t szFloat[50] = {};
			float fps = 1.0f / mDeltaTime;

			swprintf_s(szFloat, 50, L"fps : %f", fps);
			int strLen = wcsnlen_s(szFloat, 50);

			TextOut(hdc, 10, 10, szFloat, strLen);

			timeCheck = 0.0f;
		}
	}
}

