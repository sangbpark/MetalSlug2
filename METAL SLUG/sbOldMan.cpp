#include "sbOldMan.h"

namespace sb
{
	OldMan::OldMan()
	{
	}
	OldMan::~OldMan()
	{
	}
	void OldMan::Initialize()
	{
	}
	void OldMan::Update()
	{
		GameObject::Update();
	}
	void OldMan::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void OldMan::OnCollisionEnter(Collider* other)
	{
	}
	void OldMan::OnCollisionStay(Collider* other)
	{
	}
	void OldMan::OnCollisionExit(Collider* other)
	{
	}
}