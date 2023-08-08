#pragma once
#include "CommonInclude.h"


namespace sb
{
	class SoundManager
	{
	public:
		static bool Initialize();
		static LPDIRECTSOUND8 GetDevice() { return mSoundDevice; }

	private:
		static LPDIRECTSOUND8 mSoundDevice;
	};
}