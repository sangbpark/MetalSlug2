#include "sbUi.h"
#include "sbTexture.h"
#include "sbResources.h"
#include "sbSpriteRenderer.h"
#include "sbTransform.h"

namespace sb
{
	Ui::Ui()
	{
		ResourceLoad();
	}
	Ui::~Ui()
	{
	}
	void Ui::Initialize()
	{
	}
	void Ui::Update()
	{
		GameObject::Update();

	}
	void Ui::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		RenderBomb(hdc);
		RenderHeavyBullet(hdc);
		//GdiTest(hdc);
	}
	void Ui::ResourceLoad()
	{
		Texture* image = Resources::Load<Texture>(L"Ui"
			, L"..\\Resource\\Ui\\Ui.bmp");
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		Transform* tr = AddComponent<Transform>();
		sr->SetAffectedCamera(false);
		sr->SetImage(image);
		sr->SetScale(Vector2(4.5f, 4.5f));
	}
	void Ui::RenderBomb(HDC hdc)
	{
	
		wchar_t szFloat[50] = {};
		HFONT hFONT = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("±¼¸²Ã¼"));
		HFONT OldFont = (HFONT)SelectObject(hdc, hFONT);
		swprintf_s(szFloat, 50, L"%d", mPlayerBomb);
		int strLen = wcsnlen_s(szFloat, 50);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 520, 80, szFloat, strLen);
		SelectObject(hdc, OldFont);
		DeleteObject(hFONT);
	}
	void Ui::RenderHeavyBullet(HDC hdc)
	{
		wchar_t szFloat[50] = {};
		HFONT hFONT = CreateFont(35, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("±¼¸²Ã¼"));
		HFONT OldFont = (HFONT)SelectObject(hdc, hFONT);
		swprintf_s(szFloat, 50, L"%d", mPlayerHeavyBullet);
		int strLen = wcsnlen_s(szFloat, 50);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 410, 80, szFloat, strLen);
		SelectObject(hdc, OldFont);
		DeleteObject(hFONT);
	}
	void Ui::GdiTest(HDC hdc)
	{
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"%d", mPlayerBomb);
		int strLen = wcsnlen_s(szFloat, 50);
		
		AddFontResourceW(L"..\\Resource\\Ui\\metalslugfont.fnt");

		Gdiplus::Graphics graphics(hdc);
		
		Gdiplus::FontFamily fontFamily(L"metalslugfont");
		
		Gdiplus::Font F(&fontFamily, 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

		Gdiplus::PointF P(520.0f, 80.0f);

		Gdiplus::SolidBrush B(Gdiplus::Color(0, 0, 255));

		graphics.DrawString(szFloat, -1, &F, P, &B);
	}
}
