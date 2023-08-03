#include "sbArabianknife.h"
#include "sbTransform.h"
#include "sbCollider.h"
#include "sbArabian.h"
#include "sbTime.h"

namespace sb
{
	Arabianknife::Arabianknife()
	{
		Transform* tr = this->AddComponent<Transform>();
		Collider* col = this->AddComponent<Collider>();
		col->SetSize(Vector2(50.0f, 10.0f));
	}
	Arabianknife::~Arabianknife()
	{
	}
	void Arabianknife::Initialize()
	{
	}
	void Arabianknife::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		pos.y += 20.0f * Time::DeltaTime();


	}
	void Arabianknife::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Arabianknife::OnCollisionEnter(Collider* other)
	{
		Arabian* ab = dynamic_cast<Arabian*>(other->GetOwner());
		if (ab->GetArabianState() == Arabian::Arabianstate::death
			|| !(ab->GetArabianState() == Arabian::Arabianstate::attack))
		{
			Destroy(this);
		}
	}
	void Arabianknife::OnCollisionStay(Collider* other)
	{
	}
	void Arabianknife::OnCollisionExit(Collider* other)
	{
	}
}