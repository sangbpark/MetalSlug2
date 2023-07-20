#include "sbGameObject.h"
#include "sbTransform.h"
#include "sbSpriteRenderer.h"

namespace sb
{
	GameObject::GameObject()
	{
		//mComponents.push_back(new Transform());
		//mComponents[0]->SetOwner(this);
		AddComponent<Transform>();
		//mComponents.push_back(new SpriteRenderer());
		//mComponents[1]->SetOwner(this);
	}
	
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}
	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			comp->Render(hdc);
		}
	}
	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
}