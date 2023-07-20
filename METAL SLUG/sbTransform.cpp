#include "sbTransform.h"
#include "sbTime.h"
#include "sbInput.h"

namespace sb
{
	Transform::Transform()
		: Component(enums::eComponentType::Transform)
		, mRotation(0.0f)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::Render(HDC hdc)
	{
	}
}
