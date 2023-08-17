#include "sbArabianknife.h"
#include "sbTransform.h"
#include "sbCollider.h"
#include "sbArabian.h"
#include "sbTime.h"


namespace sb
{
	Arabianknife::Arabianknife()
		:mDeathTime(0.000001f)
	{
		Transform* tr = this->AddComponent<Transform>();
		Collider* col = this->AddComponent<Collider>();
		col->SetSize(Vector2(120.0f, 200.0f));
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
		mDeathTime -= Time::DeltaTime();

		if (mDeathTime <= 0.0f)
		{
			Destroy(this);
		}

	}
	void Arabianknife::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}


	void Arabianknife::OnCollisionEnter(Collider* other)
	{
	
	}
	void Arabianknife::OnCollisionStay(Collider* other)
	{
	}
	void Arabianknife::OnCollisionExit(Collider* other)
	{
	}
}