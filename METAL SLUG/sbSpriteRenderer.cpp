#include "sbSpriteRenderer.h"
#include "sbTransform.h"
#include "sbGameObject.h"
#include "sbCamera.h"

namespace sb
{
	SpriteRenderer::SpriteRenderer()
		:Component(enums::eComponentType::SpriteRenderer)
		, mTexture(nullptr)
		, mScale(Vector2::One)
		, mbAffectCamera(true)
		, mAlpha(1.0f)
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			return;

		GameObject* gameObj = GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		mTexture->Render(hdc
			, tr->GetPosition()
			, Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, Vector2(0.0f, 0.0f)
			, Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, Vector2::Zero
			, mScale
			, mAlpha
			, tr->GetRotation());
	}
}