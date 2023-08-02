#include "sbNormalBullet.h"
#include "sbTransform.h"
#include "sbTime.h"
#include "sbObject.h"
#include "sbTexture.h"
#include "sbSpriteRenderer.h"
#include "sbResources.h"
#include "sbCollider.h"

namespace sb
{
	sbNormalBullet::sbNormalBullet()
		:mDeathTime(2.0f)
	{
		ResourceLoad();
	}
	sbNormalBullet::~sbNormalBullet()
	{
	}
	void sbNormalBullet::Initialize()
	{
	}
	void sbNormalBullet::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (mState == eBulletState::Right)
		{
			pos.x += 1000.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			mDeathTime -= Time::DeltaTime();
			if (mDeathTime < 0.0f)
			{
				Destroy(this);
			}
		}
		else if (mState == eBulletState::Left)
		{
			pos.x -= 1000.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			mDeathTime -= Time::DeltaTime();
			if (mDeathTime < 0.0f)
			{
				Destroy(this);
			}
		}
		else if (mState == eBulletState::Up)
		{
			pos.y -= 1000.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			mDeathTime -= Time::DeltaTime();
			if (mDeathTime < 0.0f)
			{
				Destroy(this);
			}
		}
		else if (mState == eBulletState::Down)
		{
			pos.y += 1000.0f * Time::DeltaTime();
			tr->SetPosition(pos);

			mDeathTime -= Time::DeltaTime();
			if (mDeathTime < 0.0f)
			{
				Destroy(this);
			}
		}

	}
	void sbNormalBullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void sbNormalBullet::OnCollisionEnter(Collider* other)
	{
		Destroy(this);
	}
	void sbNormalBullet::OnCollisionStay(Collider* other)
	{
	
	}
	void sbNormalBullet::OnCollisionExit(Collider* other)
	{
	
	}
	void sbNormalBullet::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"NormalBullet",
			L"..\\Resource\\effect\\DS DSi - Metal Slug 7 Metal Slug XX - Weapon SFXNormal.bmp");
		Texture* images = Resources::Load<Texture>(L"NormalBulletY",
			L"..\\Resource\\effect\\DS DSi - Metal Slug 7 Metal Slug XX - Weapon SFXNormalUp.bmp");
		SpriteRenderer* sr = this->AddComponent<SpriteRenderer>();
		Collider* col = this->AddComponent<Collider>();
		Transform* tr = this->AddComponent<Transform>();
		if (mState == eBulletState::Up
			|| mState == eBulletState::Down)
		{
			sr->SetImage(images);
			col->SetSize(Vector2(20.0f, 30.0f));
		}
		else
		{
			sr->SetImage(image);
			col->SetSize(Vector2(30.0f, 20.0f));
		}
		sr->SetScale(Vector2(3.5f, 2.5f));
	}
}