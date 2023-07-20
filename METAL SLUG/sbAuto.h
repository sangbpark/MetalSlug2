#pragma once
#include "Commoninclude.h"
#include "sbTime.h"
#include <stdlib.h>
#include <time.h>

namespace sb
{

	enum class DisplayResolution
	{
		startDisplayx = 0,
		startDisplayy = 0,
		endDisplayx = 1600,
		endDisplayy = 900,

	};

	enum class SizeError
	{
		left = 0,
		right = 15,
		top = 0,
		bottom = 15,
	};
	enum class EllipseSize
	{
		Size = 100,
	};

	class Auto
	{
	public:
		struct Direct
		{
			bool Directx;
			bool Directy;
		};

		struct FirstPosition
		{
			float FirstPositionleft;
			float FirstPositionright;
			float FirstPositiontop;
			float FirstPositionbottom;
		};

		void Initailize();
		void Update();
		void Render(HDC hdc);
	private:
		static std::vector<Direct> mDirect;
		static std::vector< FirstPosition> mFirstPosition;
		static std::vector<math::Vector2> mAuto;
	};
}


