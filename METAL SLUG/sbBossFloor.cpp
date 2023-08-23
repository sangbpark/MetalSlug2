#include "sbBossFloor.h"
#include "sbArabian.h"
#include "sbRigidbody.h"
#include "sbCollider.h"
#include "sbTransform.h"
#include "sbBoss.h"

namespace sb
{
	BossFloor::BossFloor()
	{
	}
	BossFloor::~BossFloor()
	{
	}
	void BossFloor::Initialize()
	{
	}
	void BossFloor::Update()
	{
		GameObject::Update();
		Boss* boss = dynamic_cast<Boss*>(mOwner);
		Transform* bosstr = boss->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = bosstr->GetPosition();
		pos.y -= 20.0f;
		tr->SetPosition(pos);

	}
	void BossFloor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossFloor::OnCollisionEnter(Collider* other)
	{
		ArabianColliderEnter(other);
	}
	void BossFloor::OnCollisionStay(Collider* other)
	{
	}
	void BossFloor::OnCollisionExit(Collider* other)
	{
		ArabianColliderExit(other);
	}

	void BossFloor::ArabianColliderEnter(Collider* other)
	{
		Arabian* arabian = dynamic_cast<Arabian*>(other->GetOwner());

		if (arabian == nullptr)
			return;
		else
		{
			Transform* tr = arabian->GetComponent<Transform>();

			Rigidbody* rb = arabian->GetComponent<Rigidbody>();
			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (len < scale)
			{
				Vector2 playerPos = tr->GetPosition();
				playerPos.y -= (scale - len) - 1.0f;
				tr->SetPosition(playerPos);
			}
			rb->SetGround(true);

		}
	}

	void BossFloor::ArabianColliderExit(Collider* other)
	{
		Arabian* arabian = dynamic_cast<Arabian*>(other->GetOwner());
		if (arabian == nullptr)
			return;
		else
		{
			Rigidbody* rb = arabian->GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
	}
}
