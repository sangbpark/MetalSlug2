#include "sbFloor.h"
#include "sbPlayerBottom.h"
#include "sbPlayerTop.h"
#include "sbRigidbody.h"
#include "sbCollider.h"
#include "sbTransform.h"
#include "sbEfBomb.h"
#include "sbArabian.h"
#include "sbObject.h"

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
		PlayerColliderEnter(other);
		EfBombColliderEnter(other);
		ArabianColliderEnter(other);
	}

	void Floor::OnCollisionStay(Collider* other)
	{


	}
	void Floor::OnCollisionExit(Collider* other)
	{
		PlayerColliderExit(other);
		EfBombColliderExit(other);
		ArabianColliderExit(other);
	}

	void Floor::PlayerColliderEnter(Collider* other)
	{
		PlayerBottom* playerb = dynamic_cast<PlayerBottom*>(other->GetOwner());
	
		if (playerb == nullptr)
			return;	
		else
		{
			Transform* tr = playerb->GetComponent<Transform>();

			Rigidbody* rb = playerb->GetComponent<Rigidbody>();
			float underothery = (other->GetPosition().y + other->GetSize().y / 2.0f - Size_Error);
			float overthisy = (this->GetComponent<Collider>()->GetPosition().y - this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (underothery - overthisy > 1)
			{

			}
			else
			{
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

	}

	void Floor::PlayerColliderExit(Collider* other)
	{
		PlayerBottom* playerb = dynamic_cast<PlayerBottom*>(other->GetOwner());
		if (playerb == nullptr)
			return;
		else
		{
			Rigidbody* rb = playerb->GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
	}

	void Floor::EfBombColliderEnter(Collider* other)
	{
		EfBomb* eb = dynamic_cast<EfBomb*>(other->GetOwner());
		if (eb == nullptr)
			return;
		else
		{
			Transform* tr = eb->GetComponent<Transform>();

			Rigidbody* rb = eb->GetComponent<Rigidbody>();
			float underothery = (other->GetPosition().y + other->GetSize().y / 2.0f - Size_Error);
			float overthisy = (this->GetComponent<Collider>()->GetPosition().y - this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (underothery - overthisy > 1)
			{

			}
			else
			{
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
	}

	void Floor::EfBombColliderExit(Collider* other)
	{
		EfBomb* eb = dynamic_cast<EfBomb*>(other->GetOwner());
		if (eb == nullptr)	
			return;
		else 
		{
			Rigidbody* rb = eb->GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
	}

	void Floor::ArabianColliderEnter(Collider* other)
	{
		Arabian* arabian = dynamic_cast<Arabian*>(other->GetOwner());

		if (arabian == nullptr)
			return;
		else
		{
			Transform* tr = arabian->GetComponent<Transform>();

			Rigidbody* rb = arabian->GetComponent<Rigidbody>();
			float underothery = (other->GetPosition().y + other->GetSize().y / 2.0f - Size_Error);
			float overthisy = (this->GetComponent<Collider>()->GetPosition().y - this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (underothery - overthisy > 1)
			{

			}
			else
			{
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
	}

	void Floor::ArabianColliderExit(Collider* other)
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


	void Floor::ResourceLoad()
	{
		Rigidbody* rb = this->AddComponent<Rigidbody>();
		Collider* col = this->AddComponent<Collider>();
		Transform* tr = this->AddComponent<Transform>();
	}

}