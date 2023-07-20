#include "sbAuto.h"


namespace sb
{
	
	std::vector<Auto::Direct> Auto::mDirect = {};
	std::vector<math::Vector2> Auto::mAuto = {};
	std::vector<Auto::FirstPosition> Auto::mFirstPosition;
	float timecheck = 0.0f;
	int cyclecount = 0;

	void Auto::Initailize()
	{
		srand(time(NULL));
		int RandomDirectx = 0;
		int RandomDirecty = 0;
	

		RandomDirectx = rand();
		RandomDirecty = rand();

		Direct Direct = {};

		if (RandomDirectx % 2 == 0)
			Direct.Directx = false;
		else
			Direct.Directx = true;

		if (RandomDirecty % 2 == 0)
			Direct.Directy = false;
		else
			Direct.Directy = true;

		mDirect.push_back(Direct);

		math::Vector2 Auto = {};
		Auto.x;
		Auto.y;
		mAuto.push_back(Auto);

		FirstPosition RF;
		RF.FirstPositionleft = (rand() % 100) * 10 / 2;
		RF.FirstPositionright = RF.FirstPositionleft + 100;
		RF.FirstPositiontop = RF.FirstPositionleft;
		RF.FirstPositionbottom = RF.FirstPositionleft + 100;

		mFirstPosition.push_back(RF);


	}

	void Auto::Update()
	{
				
		timecheck += Time::DeltaTime();

		if (timecheck > 3.0f)
		{
			srand(time(NULL));
			int RandomDirectx = 0;
			int RandomDirecty = 0;

			RandomDirectx = rand();
			RandomDirecty = rand();
			
			Direct Direct = {};

			if (RandomDirectx % 2 == 0)
				Direct.Directx = false;
			else
				Direct.Directx = true;

			if (RandomDirecty % 2 == 0)
				Direct.Directy = false;
			else
				Direct.Directy = true;

			mDirect.push_back(Direct);

			math::Vector2 Auto = {};
			Auto.x;
			Auto.y;
			mAuto.push_back(Auto);

			FirstPosition RF;
			RF.FirstPositionleft = (rand() % 100) * 10 / 2;
			RF.FirstPositionright = RF.FirstPositionleft + (int)EllipseSize::Size;
			RF.FirstPositiontop = RF.FirstPositionleft;
			RF.FirstPositionbottom = RF.FirstPositionleft + (int)EllipseSize::Size;

			mFirstPosition.push_back(RF);

			cyclecount += 1;
			timecheck = 0.0f;
		}

		for (size_t i = 0; i <= cyclecount; i++) 
		{
			for (size_t e = 0; e <=	 cyclecount - i; e++) // °¡¼Ó
			{
				if (mFirstPosition[i].FirstPositionright + (int)SizeError::right + mAuto[i].x > (int)DisplayResolution::endDisplayx)
					mDirect[i].Directx = true;
				if (mFirstPosition[i].FirstPositionleft + (int)SizeError::left + mAuto[i].x < (int)DisplayResolution::startDisplayx)
					mDirect[i].Directx = false;
				if (mFirstPosition[i].FirstPositionbottom + (int)SizeError::bottom + mAuto[i].y >(int)DisplayResolution::endDisplayy)
					mDirect[i].Directy = true;
				if (mFirstPosition[i].FirstPositiontop + (int)SizeError::top + mAuto[i].y < (int)DisplayResolution::startDisplayy)
					mDirect[i].Directy = false;

				if (mDirect[i].Directx == true)
					mAuto[i].x -= 300.0f * Time::DeltaTime();
				if (mDirect[i].Directy == true)
					mAuto[i].y -= 200.0f * Time::DeltaTime();
				if (mDirect[i].Directx == false)
					mAuto[i].x += 300.0f * Time::DeltaTime();
				if (mDirect[i].Directy == false)
					mAuto[i].y += 300.0f * Time::DeltaTime();
			}
		}

	}

	void Auto::Render(HDC hdc)
	{
		int ballcount = 0;
		ballcount = cyclecount + 1;
		wchar_t szFloat[50] = {};

		swprintf_s(szFloat, 50, L"ball : %d", ballcount);
		int strLen = wcsnlen_s(szFloat, 50);

		TextOut(hdc, 10, 10, szFloat, strLen);

		for (size_t i = 0; i <= cyclecount; i++)
		{
			Ellipse(hdc, mFirstPosition[i].FirstPositionleft + mAuto[i].x, mFirstPosition[i].FirstPositiontop + mAuto[i].y
				, mFirstPosition[i].FirstPositionright + mAuto[i].x, mFirstPosition[i].FirstPositionbottom + mAuto[i].y);
		}
	}
}