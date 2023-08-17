#include "sbBGMDesert.h"
#include "sbTransform.h"
#include "sbPlayerBottom.h"
namespace sb
{
	BGMDesert::BGMDesert()
	{

	}
	BGMDesert::~BGMDesert()
	{

	}
	void BGMDesert::Initialize()
	{
	}
	void BGMDesert::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		mPlayerDistance = fabs(pos.x - PlayerBottom::GetPlayerPosition().x);
		if (mPlayerDistance > 1500.0f)
			return;
	}
	void BGMDesert::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}