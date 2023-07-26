#include "sbFloor.h"
#include "sbPlayerBottom.h"
#include "sbPlayerTop.h"
#include "sbRigidbody.h"
#include "sbCollider.h"
#include "sbTransform.h"

namespace sb
{
	Floor::Floor()
	{
	}
	Floor::~Floor()
	{
	}
	void Floor::Initialize()
	{
	}
	void Floor::Update()
	{
		GameObject::Update();
	}
	void Floor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Floor::OnCollisionEnter(Collider* other)
	{
		PlayerBottom* playerb = dynamic_cast<PlayerBottom*>(other->GetOwner());
		Transform* tr = playerb->GetComponent<Transform>();
		Rigidbody* rb = playerb->GetComponent<Rigidbody>();


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

	void Floor::OnCollisionStay(Collider* other)
	{
	
	}
	void Floor::OnCollisionExit(Collider* other)
	{
		PlayerBottom* playerb = dynamic_cast<PlayerBottom*>(other->GetOwner());
		Rigidbody* rb = playerb->GetComponent<Rigidbody>();
		rb->SetGround(false);
	}
}