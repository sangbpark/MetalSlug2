#include "sbCamelGun.h"
#include "sbTransform.h"
#include "sbCollider.h"
#include "sbAnimator.h"
#include "sbRigidbody.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbTime.h"
#include "sbCamel.h"

namespace sb
{
	CamelGun::CamelGun()
	{
		ResourseLoad();
	}
	CamelGun::~CamelGun()
	{
	}
	void CamelGun::Initialize()
	{
	}
	void CamelGun::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Transform* ownertr = mOwner->GetComponent<Transform>();
		Vector2 pos = ownertr->GetPosition();
		Camel* ca = dynamic_cast<Camel*>(mOwner);
		tr->SetRotation(ca->GetCamelRotate());
		if(ca->GetCamelState() == Camel::eCamelState::Ready)
		{
			pos.x -= 80.0f;
			pos.y += 50.0f;
			tr->SetPosition(pos);
		}
		else
		{
			pos.x -= 80.0f;
			pos.y -= 20.0f;
			tr->SetPosition(pos);
		}
	}
	void CamelGun::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CamelGun::OnCollisionEnter(Collider* other)
	{
	}
	void CamelGun::OnCollisionStay(Collider* other)
	{
	}
	void CamelGun::OnCollisionExit(Collider* other)
	{
	}
	void CamelGun::ResourseLoad()
	{
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Texture* image = Resources::Load<Texture>(L"CamelGun",
			L"..\\Resource\\Vehicle\\camelbullet.png");
		at->CreateAnimation(L"camelbulletIdleAX", image, Vector2(0.0f, 0.0f), Vector2(176.0f, 176.0f), 1, Vector2(0.0f, -20.0f));
		at->CreateAnimation(L"camelbulletGunAX", image, Vector2(0.0f, 176.0f), Vector2(176.0f, 176.0f), 4, Vector2(0.0f, -20.0f));
		at->SetScale(Vector2(3.5f, 3.5f));
		at->PlayAnimation(L"camelbulletIdleAX", true);
	}
}