#include "sbBackGround.h"
#include "sbTransform.h"
#include "sbPlayerBottom.h"

namespace sb
{
	BackGround::BackGround()
		:mRender(false)
	{
	}
	BackGround::~BackGround()
	{
	}
	void BackGround::Initialize()
	{
	}
	void BackGround::Update()
	{
		if(mRender)
		{
			GameObject::Update();
		}
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayerDistance = pos.x - PlayerBottom::GetPlayerPosition().x;
		RenderBackGround();
		if (mPlayerDistance <= -4500.0f)
			Destroy(this);
		
	}
	void BackGround::Render(HDC hdc)
	{
		if(mRender)
		{
			GameObject::Render(hdc);
		}
	}
	void BackGround::RenderBackGround()
	{
		if (mStage == eStage::First)
		{
			mRender = true;
		}
		else if (mStage == eStage::Second
			|| mStage == eStage::Last)
		{		
			if (mPlayerDistance <= 4500.0f)
				mRender = true;
		}
	}
}