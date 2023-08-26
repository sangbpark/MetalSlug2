#include "sbHeavyMachineGun.h"
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
	HeavyMachineGun::HeavyMachineGun()
		:mDeathTime(10.0f)
	{
		ResourseLoad();
	}
	HeavyMachineGun::~HeavyMachineGun()
	{
	}
	void HeavyMachineGun::Initialize()
	{
	}
	void HeavyMachineGun::Update()
	{
		GameObject::Update();

	}
	void HeavyMachineGun::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		mDeathTime -= Time::DeltaTime();
		if (mDeathTime <= 0)
		{
			Destroy(this);
		}
	}

	void HeavyMachineGun::OnCollisionEnter(Collider* other)
	{
		PlayerBottom* player = dynamic_cast<PlayerBottom*>(other->GetOwner());
		if (player == nullptr)
			return;
		else
		{
			player->SetWeaponState(PlayerBottom::eWeaponState::heavy);
			player->SetChange(true);
			player->SetHeavyBulletCount(200);
			Destroy(this);
			Sound* sound = Resources::Load<Sound>(L"HeavyMachine"
				, L"..\\Resource\\sound\\heavy-machine-gun.wav");
			sound->Play(false);
		}
	}

	void HeavyMachineGun::OnCollisionStay(Collider* other)
	{
	}

	void HeavyMachineGun::OnCollisionExit(Collider* other)
	{
	}

	void HeavyMachineGun::ResourseLoad()
	{
		Animator* at = AddComponent<Animator>();
		Transform* tr = AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		Rigidbody* rb = AddComponent<Rigidbody>();
		Texture* image = Resources::Load<Texture>(L"HeavyMachineGun",
			L"..\\Resource\\Items\\items1.bmp");
		at->CreateAnimation(L"HeavyMachineAX", image, Vector2(0.0f, 44.0f), Vector2(44.0f, 44.0f), 4);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"HeavyMachineAX",true);
	
		col->SetSize(Vector2(70.0f, 70.0f));
	}


}
