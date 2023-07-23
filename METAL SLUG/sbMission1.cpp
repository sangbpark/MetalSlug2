#include "sbMission1.h"
#include "sbObject.h"
#include "sbSpriteRenderer.h"
#include "sbPlayerTop.h"
#include "sbPlayerBottom.h"
#include "sbResources.h"
#include "sbBackGround.h"
#include "sbTransform.h"
#include "sbGameObject.h"
#include "sbBGDesert.h"
#include "sbBGMDesert.h"
#include "sbCamera.h"
#include "sbDev.h"
#include "sbFrontBackGround.h"
#include "sbMiddleBoss.h"
#include "sbOldMan.h"
#include "sbCameraPlayer.h"
#include "sbAnimator.h"
#include "sbBGbossCanopi.h"
#include "sbCollider.h"
#include "sbCollisionManager.h"

namespace sb
{
	Mission1::Mission1()
	{
	}
	Mission1::~Mission1()
	{
	}
	void Mission1::Initialize()
	{
		Texture* imagesky = Resources::Load<Texture>(L"Mission1BackGroundSky"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission sky.bmp");
		BackGround* M1BackGroundSky = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		SpriteRenderer* skysr = M1BackGroundSky->AddComponent<SpriteRenderer>();
		Transform* skytr = M1BackGroundSky->GetComponent<Transform>();
		skytr->SetPosition(Vector2(4000.0f, 100.0f));
		skysr->SetImage(imagesky);
		skysr->SetScale(Vector2(4.5f, 4.5f));
	

		Texture* imagebosssky = Resources::Load<Texture>(L"Mission1BackGroundbossSky"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1bosssky.bmp");
		BackGround* M1BackGroundBossSky = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		SpriteRenderer* Bskysr = M1BackGroundBossSky->AddComponent<SpriteRenderer>();
		Transform* Bskytr = M1BackGroundBossSky->GetComponent<Transform>();
		Bskytr->SetPosition(Vector2(16000.0f, 70.0f));
		Bskysr->SetImage(imagebosssky);
		Bskysr->SetScale(Vector2(7.0f, 9.0f));

		Texture* imageMDesert = Resources::Load<Texture>(L"Mission1BackGroundMDesert"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1-mbackdesert.bmp");
		BGMDesert* M1BackGroundMDesert1 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		Transform* BGDMtr1 = M1BackGroundMDesert1->GetComponent<Transform>();
		BGDMtr1->SetPosition(Vector2(500.0f, 325.0f));
		Animator* BGDat1 = M1BackGroundMDesert1->AddComponent<Animator>();
		BGDat1->CreateAnimation(L"Mission1BackGroundMDesert1AY", imageMDesert
			, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		BGDat1->SetScale(Vector2(4.5f, 4.5f));
		BGDat1->PlayAnimation(L"Mission1BackGroundMDesert1AY",true);
		BGMDesert* M1BackGroundMDesert2 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		Transform* BGDMtr2 = M1BackGroundMDesert2->GetComponent<Transform>();
		BGDMtr2->SetPosition(Vector2(1580.0f, 325.0f));
		Animator* BGDat2 = M1BackGroundMDesert2->AddComponent<Animator>();
		BGDat2->CreateAnimation(L"Mission1BackGroundMDesert2AY", imageMDesert
			, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		BGDat2->SetScale(Vector2(4.5f, 4.5f));
		BGDat2->PlayAnimation(L"Mission1BackGroundMDesert2AY", true);
		BGMDesert* M1BackGroundMDesert3 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		Transform* BGDMtr3 = M1BackGroundMDesert3->GetComponent<Transform>();
		BGDMtr3->SetPosition(Vector2(2670.0f, 325.0f));
		Animator* BGDat3 = M1BackGroundMDesert3->AddComponent<Animator>();
		BGDat3->CreateAnimation(L"Mission1BackGroundMDesert3AY", imageMDesert
			, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		BGDat3->SetScale(Vector2(4.5f, 4.5f));
		BGDat3->PlayAnimation(L"Mission1BackGroundMDesert3AY", true);
		BGMDesert* M1BackGroundMDesert4 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		Transform* BGDMtr4 = M1BackGroundMDesert4->GetComponent<Transform>();
		BGDMtr4->SetPosition(Vector2(3750.0f, 325.0f));
		Animator* BGDat4 = M1BackGroundMDesert4->AddComponent<Animator>();
		BGDat4->CreateAnimation(L"Mission1BackGroundMDesert4AY", imageMDesert
			, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		BGDat4->SetScale(Vector2(4.5f, 4.5f));
		BGDat4->PlayAnimation(L"Mission1BackGroundMDesert4AY", true);

	
		

		Texture* imageDesert = Resources::Load<Texture>(L"Mission1BackGroundDesert"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1-backdesert.bmp");
		BGDesert* M1BackGroundDesert = object::Instantiate<BGDesert>(enums::eLayerType::Backgroud);
		SpriteRenderer* BGDsr = M1BackGroundDesert->AddComponent<SpriteRenderer>();
		Transform* BGDtr = M1BackGroundDesert->GetComponent<Transform>();
		BGDtr->SetPosition(Vector2(2240.0f, 400.0f));
		BGDsr->SetImage(imageDesert);
		BGDsr->SetScale(Vector2(4.5f, 4.5f));
	
	
		Texture* imageBG = Resources::Load<Texture>(L"Mission1BackGround"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1d.bmp");
		BackGround* M1BackGround = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		SpriteRenderer* BGsr = M1BackGround->AddComponent<SpriteRenderer>();
		Transform* BGtr = M1BackGround->GetComponent<Transform>();
		BGtr->SetPosition(Vector2(8550.0f, 250.0f));
		BGsr->SetImage(imageBG);
		BGsr->SetScale(Vector2(4.5f, 4.5f));
	
		Texture* imageBGboss = Resources::Load<Texture>(L"Mission1bossbackground"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1 bossground.bmp");
		BackGround* M1BackGroundboss = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		Transform* BGBtr = M1BackGroundboss->GetComponent<Transform>();
		BGBtr->SetPosition(Vector2(16460.0f, 190.0f));
		Animator* BGBat = M1BackGroundboss->AddComponent<Animator>();
		BGBat->CreateAnimation(L"mission1bossbackgroundAX", imageBGboss
			, Vector2(0.0f, 0.0f), Vector2(307.0f, 208.0f), 4);
		BGBat->SetScale(Vector2(4.5f, 4.5f));
		BGBat->PlayAnimation(L"mission1bossbackgroundAX", true);

		Texture* imageBGbossCanopi = Resources::Load<Texture>(L"BossCanopi"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1canopy.bmp");
		BGbossCanopi* bgbosscanopi = object::Instantiate<BGbossCanopi>(enums::eLayerType::Backgroud);
		Transform* BGCtr = bgbosscanopi->GetComponent<Transform>();
		BGCtr->SetPosition(Vector2(15740.0f, 230.0f));
		Animator* BGCat = bgbosscanopi->AddComponent<Animator>();
		BGCat->CreateAnimation(L"bosscanopiAY", imageBGbossCanopi
			, Vector2(0.0f, 0.0f), Vector2(180.0f, 63.0f), 3);
		BGCat->SetScale(Vector2(4.5f, 4.5f));
		BGCat->PlayAnimation(L"bosscanopiAY", true);


		BGbossCanopi* bgbosscanopi2 = object::Instantiate<BGbossCanopi>(enums::eLayerType::Backgroud);
		Transform* BGCtr2 = bgbosscanopi2->GetComponent<Transform>();
		BGCtr2->SetPosition(Vector2(16960.0f, 250.0f));
		Animator* BGCat2 = bgbosscanopi2->AddComponent<Animator>();
		BGCat2->CreateAnimation(L"bosscanopi2AY", imageBGbossCanopi
			, Vector2(825.0f, 0.0f), Vector2(89.0f, 63.0f), 3);
		BGCat2->SetScale(Vector2(4.5f, 4.5f));
		BGCat2->PlayAnimation(L"bosscanopi2AY", true);
		
		Texture* imagefruit = Resources::Load<Texture>(L"fruit"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Missionfruit 1.bmp");
		BackGround* fruit = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		SpriteRenderer* frsr = fruit->AddComponent<SpriteRenderer>();
		Transform* frtr = fruit->GetComponent<Transform>();
		frtr->SetPosition(Vector2(2680.0f, 580.0f));
		frsr->SetImage(imagefruit);
		frsr->SetScale(Vector2(4.5f, 4.5f));

		Texture* imagefruitcolumn = Resources::Load<Texture>(L"fruitcolumn"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Missionfruitcoulmn 1.bmp");
		FrontBackGround* fruitcolumn = object::Instantiate<FrontBackGround>(enums::eLayerType::FrontBackGround);
		SpriteRenderer* fcsr = fruitcolumn->AddComponent<SpriteRenderer>();
		Transform* fctr = fruitcolumn->GetComponent<Transform>();
		fctr->SetPosition(Vector2(2850.0f, 580.0f));
		fcsr->SetImage(imagefruitcolumn);
		fcsr->SetScale(Vector2(4.5f, 4.5f));


		Texture* imagemiddleboss = Resources::Load<Texture>(L"middleboss"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1middleboss.bmp");
		MiddleBoss* middlboss = object::Instantiate<MiddleBoss>(enums::eLayerType::Monster);
		SpriteRenderer* MBsr = middlboss->AddComponent<SpriteRenderer>();
		Transform* MBtr = middlboss->GetComponent<Transform>();
		MBtr->SetPosition(Vector2(9050.0f, 310.0f));
		MBsr->SetImage(imagemiddleboss);
		MBsr->SetScale(Vector2(4.5f, 4.5f));


		Texture* imageNpcOldMan = Resources::Load<Texture>(L"NpcOldMan"
			, L"..\\Resource\\Npc\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - POWs Helpful NPCs.bmp");
		OldMan* NpcOldMan1 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		Transform* OMtr1 = NpcOldMan1->GetComponent<Transform>();
		OMtr1->SetPosition(Vector2(2850.0f, 300.0f));
		Animator* OMat1 = NpcOldMan1->AddComponent<Animator>();
		OMat1->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		OMat1->SetScale(Vector2(4.5f, 4.5f));
		OMat1->PlayAnimation(L"NpcOldManIdleAX",true);



		OldMan* NpcOldMan2 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		Transform* OMtr2 = NpcOldMan2->GetComponent<Transform>();
		OMtr2->SetPosition(Vector2(6200.0f, 210.0f));
		Animator* OMat2 = NpcOldMan2->AddComponent<Animator>();
		OMat2->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2 );
		OMat2->SetScale(Vector2(4.5f, 4.5f));
		OMat2->PlayAnimation(L"NpcOldManIdleAX", true);
		


		
		OldMan* NpcOldMan3 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		Transform* OMtr3 = NpcOldMan3->GetComponent<Transform>();
		OMtr3->SetPosition(Vector2(9000.0f, 600.0f));
		Animator* OMat3 = NpcOldMan3->AddComponent<Animator>();
		OMat3->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		OMat3->SetScale(Vector2(4.5f, 4.5f));
		OMat3->PlayAnimation(L"NpcOldManIdleAX", true);
	

		
		OldMan* NpcOldMan4 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		Transform* OMtr4 = NpcOldMan4->GetComponent<Transform>();
		OMtr4->SetPosition(Vector2(13500.0f, 600.0f));
		Animator* OMat4 = NpcOldMan4->AddComponent<Animator>();
		OMat4->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		OMat4->SetScale(Vector2(4.5f, 4.5f));
		OMat4->PlayAnimation(L"NpcOldManIdleAX", true);
	
		
		Texture* imagePlayer = Resources::Load<Texture>(L"Player"
			, L"..\\Resource\\Character\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Marco Rossi.bmp");
	
		PlayerBottom* playerbottom = object::Instantiate<PlayerBottom>(enums::eLayerType::Player);
		Transform* ptr2 = playerbottom->GetComponent<Transform>();
		ptr2->SetPosition(Vector2(600.0f, 500.0f));
		Animator* pb = playerbottom->AddComponent<Animator>();
		pb->CreateAnimation(L"PlayerIdlerightBAX", imagePlayer, Vector2(176.0f, 258.0f), Vector2(44.0f, 36.0f), 1);
		pb->CreateAnimation(L"PlayerIdleleftBAX", imagePlayer, Vector2(0.0f, 299.0f), Vector2(44.0f, 36.0f), 1,Vector2(-35.0f, 0.0f));
		pb->CreateAnimation(L"PlayerrightBAX", imagePlayer, Vector2(0.0f, 506.0f), Vector2(44.0f, 25.0f), 12,Vector2(-5.0f,25.0f));
		pb->CreateAnimation(L"PlayerleftBAX", imagePlayer, Vector2(0.0f, 425.0f), Vector2(44.0f, 25.0f), 12, Vector2(-5.0f, 25.0f));
		pb->CreateAnimation(L"PlayerdeadBAX", imagePlayer, Vector2(906.0f, 53.0f), Vector2(44.0f, 44.0f), 19, Vector2(5.0f, -4.0f));
		pb->SetScale(Vector2(4.5f, 4.5f));
		pb->PlayAnimation(L"PlayerIdlerightBAX", true);

		PlayerTop* playerTop = object::Instantiate<PlayerTop>(enums::eLayerType::Player);
		Transform* ptr = playerTop->GetComponent<Transform>();
		ptr->SetPosition(Vector2(600.0f, 470.0f));
		Animator* pt = playerTop->AddComponent<Animator>();
		pt->CreateAnimation(L"PlayerIdlerightTAX", imagePlayer, Vector2(0.0f, 258.0f), Vector2(44.0f, 34.0f), 4);
		pt->CreateAnimation(L"PlayerIdleleftTAX", imagePlayer, Vector2(44.0f, 299.0f), Vector2(44.0f, 34.0f), 4, Vector2(-35.0f, 0.0f));
		pt->CreateAnimation(L"PlayerrightTAX", imagePlayer, Vector2(0.0f, 472.0f), Vector2(44.0f, 34.0f), 12,Vector2(-5.0f, -7.0f));
		pt->CreateAnimation(L"PlayerleftTAX", imagePlayer, Vector2(0.0f, 391.0f), Vector2(44.0f, 34.0f), 12, Vector2(-5.0f, -7.0f));
		pt->CreateAnimation(L"PlayerdeadTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(-20.0f, -2.0f));
		pt->SetScale(Vector2(4.5f, 4.5f));
		pt->PlayAnimation(L"PlayerIdlerightTAX", true);


		Texture* imageCameraPlayer = Resources::Load<Texture>(L"CameraPlayer"
			, L"..\\Resource\\Character\\Dev.bmp");
		CameraPlayer* cameraplayer = object::Instantiate<CameraPlayer>(enums::eLayerType::Player);
		SpriteRenderer* cpsr = cameraplayer->AddComponent<SpriteRenderer>();
		Transform* cptr = cameraplayer->GetComponent<Transform>();
		cptr->SetPosition(Vector2(600.0f, 400.0f));
		cpsr->SetImage(imageCameraPlayer);
		cpsr->SetAlpha(0.0f);

		Collider* col = playerbottom->AddComponent<Collider>();
		col->SetSize(Vector2(100.0f, 160.0f));
		col->SetOffset(Vector2(0.0f, 0.0f));
	
		
		Camera::SetTarget(cameraplayer);

	}
	void Mission1::Update()
	{
		Scene::Update();
		Camera::Update();
	}


	void Mission1::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}
}