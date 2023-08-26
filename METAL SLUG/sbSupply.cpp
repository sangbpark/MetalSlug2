#include "sbSupply.h"
#include "sbTransform.h"
#include "sbCollider.h"
#include "sbAnimator.h"
#include "sbRigidbody.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbPlayerBottom.h"
#include "sbTime.h"
#include "sbSound.h"

namespace sb
{
	Supply::Supply()
		:mDeathTime(10.0f)
	{
		ResourseLoad();
	}
	Supply::~Supply()
	{
	}
	void Supply::Initialize()
	{
	}
	void Supply::Update()
	{
		GameObject::Update();
	}

	void Supply::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		mDeathTime -= Time::DeltaTime();
		if (mDeathTime <= 0)
		{
			Destroy(this);
		}
	}

	void Supply::OnCollisionEnter(Collider* other)
	{
		PlayerBottom* player = dynamic_cast<PlayerBottom*>(other->GetOwner());
		if (player == nullptr)
			return;
		else
		{
			player->SetEfBombCount(10);
			Destroy(this);
			Sound* sound = Resources::Load<Sound>(L"supply"
				, L"..\\Resource\\sound\\ok-metal-slug-sound.wav");
			sound->Play(false);
		}
	}

	void Supply::OnCollisionStay(Collider* other)
	{
	}

	void Supply::OnCollisionExit(Collider* other)
	{
	}

	void Supply::ResourseLoad()
	{
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		Rigidbody* rb = AddComponent<Rigidbody>();
		Texture* image = Resources::Load<Texture>(L"Supply",
			L"..\\Resource\\Items\\items1.bmp");
		at->CreateAnimation(L"SupplyAX", image, Vector2(0.0f, 0.0f), Vector2(44.0f, 44.0f), 6,Vector2(0.0f,-20.0f));
		at->SetScale(Vector2(3.5f, 3.5f));
		at->PlayAnimation(L"SupplyAX",true);

		col->SetSize(Vector2(70.0f, 70.0f));
	}


}
