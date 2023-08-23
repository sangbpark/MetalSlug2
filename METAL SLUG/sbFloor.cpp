#include "sbFloor.h"
#include "sbPlayerBottom.h"
#include "sbPlayerTop.h"
#include "sbRigidbody.h"
#include "sbCollider.h"
#include "sbTransform.h"
#include "sbEfBomb.h"
#include "sbArabian.h"
#include "sbObject.h"
#include "sbHOldMan.h"
#include "sbHeavyMachineGun.h"
#include "sbSupply.h"
#include "sbBerserker.h"
#include "sbTruck.h"
#include "sbCamel.h"


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
		HoldManColliderEnter(other);
		HeavyMachineGunColliderEnter(other);
		SupplyColliderEnter(other);
		BerserkerColliderEnter(other);
		TruckColliderEnter(other);
		CamelColliderEnter(other);
	}

	void Floor::OnCollisionStay(Collider* other)
	{

	}
	void Floor::OnCollisionExit(Collider* other)
	{
		PlayerColliderExit(other);
		EfBombColliderExit(other);
		ArabianColliderExit(other);
		HoldManColliderExit(other);
		HeavyMachineGunColliderExit(other);
		SupplyColliderExit(other);
		BerserkerColliderExit(other);
		TruckColliderExit(other);
		CamelColliderExit(other);
	}

	void Floor::PlayerColliderEnter(Collider* other)
	{
		PlayerBottom* playerb = dynamic_cast<PlayerBottom*>(other->GetOwner());
		if (playerb == nullptr
			|| playerb->GetRide() == true)
			return;	
		else
		{
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

	}

	void Floor::PlayerColliderExit(Collider* other)
	{
		PlayerBottom* playerb = dynamic_cast<PlayerBottom*>(other->GetOwner());
		if (playerb == nullptr
			|| playerb->GetRide() == true)
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

	void Floor::HoldManColliderEnter(Collider* other)
	{
		HOldMan* holdman = dynamic_cast<HOldMan*>(other->GetOwner());

		if (holdman == nullptr)
			return;
		else
		{
			Transform* tr = holdman->GetComponent<Transform>();
			Rigidbody* rb = holdman->GetComponent<Rigidbody>();

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

	void Floor::HoldManColliderExit(Collider* other)
	{
		HOldMan* holdman = dynamic_cast<HOldMan*>(other->GetOwner());
		if (holdman == nullptr)
			return;
		else
		{
			Rigidbody* rb = holdman->GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
	}

	void Floor::BerserkerColliderEnter(Collider* other)
	{
		Berserker* berserker = dynamic_cast<Berserker*>(other->GetOwner());

		if (berserker == nullptr)
			return;
		else
		{
			Transform* tr = berserker->GetComponent<Transform>();
			Rigidbody* rb = berserker->GetComponent<Rigidbody>();

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

	void Floor::BerserkerColliderExit(Collider* other)
	{
		Berserker* berserker = dynamic_cast<Berserker*>(other->GetOwner());
		if (berserker == nullptr)
			return;
		else
		{
			Rigidbody* rb = berserker->GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
	}

	void Floor::TruckColliderEnter(Collider* other)
	{
		Truck* truck = dynamic_cast<Truck*>(other->GetOwner());

		if (truck == nullptr)
			return;
		else
		{
			Transform* tr = truck->GetComponent<Transform>();
			Rigidbody* rb = truck->GetComponent<Rigidbody>();

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

	void Floor::TruckColliderExit(Collider* other)
	{
		Truck* truck = dynamic_cast<Truck*>(other->GetOwner());
		if (truck == nullptr)
			return;
		else
		{
			Rigidbody* rb = truck->GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
	}

	void Floor::CamelColliderEnter(Collider* other)
	{
		Camel* camel = dynamic_cast<Camel*>(other->GetOwner());

		if (camel == nullptr)
			return;
		else
		{
			Transform* tr = camel->GetComponent<Transform>();
			Rigidbody* rb = camel->GetComponent<Rigidbody>();

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

	void Floor::CamelColliderExit(Collider* other)
	{
		Camel* camel = dynamic_cast<Camel*>(other->GetOwner());
		if (camel == nullptr)
			return;
		else
		{
			Rigidbody* rb = camel->GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
	}

	void Floor::HeavyMachineGunColliderEnter(Collider* other)
	{
		HeavyMachineGun* hmg = dynamic_cast<HeavyMachineGun*>(other->GetOwner());

		if (hmg == nullptr)
			return;
		else
		{
			Transform* tr = hmg->GetComponent<Transform>();
			Rigidbody* rb = hmg->GetComponent<Rigidbody>();

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

	void Floor::HeavyMachineGunColliderExit(Collider* other)
	{
		HeavyMachineGun* hmg = dynamic_cast<HeavyMachineGun*>(other->GetOwner());
		if (hmg == nullptr)
			return;
		else
		{
			Rigidbody* rb = hmg->GetComponent<Rigidbody>();
			rb->SetGround(false);
		}
	}

	void Floor::SupplyColliderEnter(Collider* other)
	{
		Supply* sy = dynamic_cast<Supply*>(other->GetOwner());

		if (sy == nullptr)
			return;
		else
		{
			Transform* tr = sy->GetComponent<Transform>();
			Rigidbody* rb = sy->GetComponent<Rigidbody>();

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

	void Floor::SupplyColliderExit(Collider* other)
	{
		Supply* sy = dynamic_cast<Supply*>(other->GetOwner());
		if (sy == nullptr)
			return;
		else
		{
			Rigidbody* rb = sy->GetComponent<Rigidbody>();
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