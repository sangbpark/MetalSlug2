#pragma once
#include "sbGameObject.h"


namespace sb
{
	class Ui : public GameObject
	{
	public:
		Ui();
		virtual ~Ui();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ResourceLoad();

		void RenderBomb(HDC hdc);
		void RenderHeavyBullet(HDC hdc);

		void SetPlayerBomb(int value) { mPlayerBomb = value; }
		void SetPlayerHeavyBullet(int value) { mPlayerHeavyBullet = value; }

		void GdiTest(HDC hdc);
	private:
		int mPlayerBomb;
		int mPlayerHeavyBullet;
	};
}
