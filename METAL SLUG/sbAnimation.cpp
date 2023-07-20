#include "sbAnimation.h"
#include "sbTexture.h"
#include "sbAnimator.h"
#include "sbTime.h"
#include "sbTransform.h"
#include "sbGameObject.h"
#include "sbCamera.h"

namespace sb
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;

			if (mIndex < mSpriteSheet.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}
	void Animation::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			return;

		Sprite sprite = mSpriteSheet[mIndex];
		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Animator* animator = mAnimator;

		mTexture->Render(hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, sprite.offset
			, animator->GetScale()
			, animator->GetAlpha()
			, tr->GetRotation());

	}
	void Animation::Create(const std::wstring& name
			, Texture* texture, Vector2 leftTop, Vector2 size
			, Vector2 offset, UINT spriteLength, float duration)
	{
		mTexture = texture;
		std::wstring ext // bmp png ±¸ºÐ
			= name.substr(name.find_last_of(L"A") );

		if(ext ==L"AX")
		{
			for (size_t i = 0; i < spriteLength; i++)
			{
				Sprite sprite = {};

				sprite.leftTop.x = leftTop.x + (size.x * i);
				sprite.leftTop.y = leftTop.y;
				sprite.size = size;
				sprite.offset = offset;
				sprite.duration = duration;
				mSpriteSheet.push_back(sprite);
			}
		}
		else if (ext == L"AY")
		{
			for (size_t i = 0; i < spriteLength; i++)
			{
				Sprite sprite = {};

				sprite.leftTop.x = leftTop.x;
				sprite.leftTop.y = leftTop.y + (size.y * i);
				sprite.size = size;
				sprite.offset = offset;
				sprite.duration = duration;
				mSpriteSheet.push_back(sprite);
			}
		}
	
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}