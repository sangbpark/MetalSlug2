#include "sbBGbossCanopi.h"
#include "sbTransform.h"
#include "sbAnimator.h"
#include "sbCollider.h"
#include "sbTexture.h"
#include "sbResources.h"

namespace sb
{
	//Vector2(15740.0f, 230.0f)
	//Vector2(16960.0f, 250.0f)
	BGbossCanopi::BGbossCanopi()
		:mPlayerDistance(0.0f)
		, mState(eState::Create)
	{
		ResourseLoad();
	}
	BGbossCanopi::~BGbossCanopi()
	{
	}
	void BGbossCanopi::Initialize()
	{
	}
	void BGbossCanopi::Update()
	{

		GameObject::Update();
		switch (mState)
		{
		case sb::BGbossCanopi::eState::Create:
			break;
		case sb::BGbossCanopi::eState::Idle:
			break;
		case sb::BGbossCanopi::eState::End:
			break;
		default:
			break;
		}

	}
	void BGbossCanopi::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}
	void BGbossCanopi::Create()
	{
		Animator* at = AddComponent<Animator>();
		if (mPosition == ePosition::Left)
		{
			at->PlayAnimation(L"bosscanopiAY", true);
		}
		else
		{
			at->PlayAnimation(L"bosscanopi2AY", true);
		}
		mState == eState::Idle;
	}
	void BGbossCanopi::Idle()
	{
	}
	void BGbossCanopi::ResourseLoad()
	{
		Texture* imageBGbossCanopi = Resources::Load<Texture>(L"BossCanopi"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1canopy.bmp");
		Animator* at = AddComponent<Animator>();
		at->CreateAnimation(L"bosscanopiAY", imageBGbossCanopi
			, Vector2(0.0f, 0.0f), Vector2(180.0f, 63.0f), 3);
		at->CreateAnimation(L"bosscanopi2AY", imageBGbossCanopi
			, Vector2(825.0f, 0.0f), Vector2(89.0f, 63.0f), 3);
		at->SetScale(Vector2(4.5f, 4.5f));
	}
}