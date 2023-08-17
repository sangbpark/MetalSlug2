#include "sbBerserkerKnife.h"
#include "sbTransform.h"
#include "sbCollider.h"
#include "sbBerserker.h"

namespace sb
{
	BerserkerKnife::BerserkerKnife()
	{
		Transform* tr = AddComponent<Transform>();
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(150.0f, 180.0f));
	}
	BerserkerKnife::~BerserkerKnife()
	{
	}
	void BerserkerKnife::Initialize()
	{
	}
	void BerserkerKnife::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
	}
	void BerserkerKnife::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BerserkerKnife::Death()
	{
		Destroy(this);
	}
	void BerserkerKnife::OnCollisionEnter(Collider* other)
	{
	}
	void BerserkerKnife::OnCollisionStay(Collider* other)
	{
	}
	void BerserkerKnife::OnCollisionExit(Collider* other)
	{
	}
}
