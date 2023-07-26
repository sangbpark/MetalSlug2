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
#include "sbRigidbody.h"
#include "sbFloor.h"

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
		SpriteRenderer* sr = M1BackGroundSky->AddComponent<SpriteRenderer>();
		Transform* tr = M1BackGroundSky->GetComponent<Transform>();
		tr->SetPosition(Vector2(4000.0f, 100.0f));
		sr->SetImage(imagesky);
		sr->SetScale(Vector2(4.5f, 4.5f));
	

		Texture* imagebosssky = Resources::Load<Texture>(L"Mission1BackGroundbossSky"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1bosssky.bmp");
		BackGround* M1BackGroundBossSky = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		sr = M1BackGroundBossSky->AddComponent<SpriteRenderer>();
		tr = M1BackGroundBossSky->GetComponent<Transform>();
		tr->SetPosition(Vector2(16000.0f, 70.0f));
		sr->SetImage(imagebosssky);
		sr->SetScale(Vector2(7.0f, 9.0f));

		Texture* imageMDesert = Resources::Load<Texture>(L"Mission1BackGroundMDesert"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1-mbackdesert.bmp");
		BGMDesert* M1BackGroundMDesert1 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		tr = M1BackGroundMDesert1->GetComponent<Transform>();
		tr->SetPosition(Vector2(500.0f, 325.0f));
		Animator* at = M1BackGroundMDesert1->AddComponent<Animator>();
		at->CreateAnimation(L"Mission1BackGroundMDesertAY", imageMDesert
			, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"Mission1BackGroundMDesertAY",true);
		BGMDesert* M1BackGroundMDesert2 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		tr = M1BackGroundMDesert2->GetComponent<Transform>();
		tr->SetPosition(Vector2(1580.0f, 325.0f));
		at = M1BackGroundMDesert2->AddComponent<Animator>();
		at->CreateAnimation(L"Mission1BackGroundMDesertAY", imageMDesert
			, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"Mission1BackGroundMDesertAY", true);
		BGMDesert* M1BackGroundMDesert3 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		tr = M1BackGroundMDesert3->GetComponent<Transform>();
		tr->SetPosition(Vector2(2670.0f, 325.0f));
		at = M1BackGroundMDesert3->AddComponent<Animator>();
		at->CreateAnimation(L"Mission1BackGroundMDesertAY", imageMDesert
			, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"Mission1BackGroundMDesertAY", true);
		BGMDesert* M1BackGroundMDesert4 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		tr = M1BackGroundMDesert4->GetComponent<Transform>();
		tr->SetPosition(Vector2(3750.0f, 325.0f));
		at = M1BackGroundMDesert4->AddComponent<Animator>();
		at->CreateAnimation(L"Mission1BackGroundMDesertAY", imageMDesert
			, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"Mission1BackGroundMDesertAY", true);

	
		

		Texture* imageDesert = Resources::Load<Texture>(L"Mission1BackGroundDesert"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1-backdesert.bmp");
		BGDesert* M1BackGroundDesert = object::Instantiate<BGDesert>(enums::eLayerType::Backgroud);
		sr = M1BackGroundDesert->AddComponent<SpriteRenderer>();
		tr = M1BackGroundDesert->GetComponent<Transform>();
		tr->SetPosition(Vector2(2240.0f, 400.0f));
		sr->SetImage(imageDesert);
		sr->SetScale(Vector2(4.5f, 4.5f));
	
	
		Texture* imageBG = Resources::Load<Texture>(L"Mission1BackGround"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1d.bmp");
		BackGround* M1BackGround = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		sr = M1BackGround->AddComponent<SpriteRenderer>();
		tr = M1BackGround->GetComponent<Transform>();
		tr->SetPosition(Vector2(8550.0f, 250.0f));
		sr->SetImage(imageBG);
		sr->SetScale(Vector2(4.5f, 4.5f));
	
		Texture* imageBGboss = Resources::Load<Texture>(L"Mission1bossbackground"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1 bossground.bmp");
		BackGround* M1BackGroundboss = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		tr = M1BackGroundboss->GetComponent<Transform>();
		tr->SetPosition(Vector2(16460.0f, 190.0f));
		at = M1BackGroundboss->AddComponent<Animator>();
		at->CreateAnimation(L"mission1bossbackgroundAX", imageBGboss
			, Vector2(0.0f, 0.0f), Vector2(307.0f, 208.0f), 4);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"mission1bossbackgroundAX", true);

		Texture* imageBGbossCanopi = Resources::Load<Texture>(L"BossCanopi"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1canopy.bmp");
		BGbossCanopi* bgbosscanopi = object::Instantiate<BGbossCanopi>(enums::eLayerType::Backgroud);
		tr = bgbosscanopi->GetComponent<Transform>();
		tr->SetPosition(Vector2(15740.0f, 230.0f));
		at = bgbosscanopi->AddComponent<Animator>();
		at->CreateAnimation(L"bosscanopiAY", imageBGbossCanopi
			, Vector2(0.0f, 0.0f), Vector2(180.0f, 63.0f), 3);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"bosscanopiAY", true);


		BGbossCanopi* bgbosscanopi2 = object::Instantiate<BGbossCanopi>(enums::eLayerType::Backgroud);
		tr = bgbosscanopi2->GetComponent<Transform>();
		tr->SetPosition(Vector2(16960.0f, 250.0f));
		at = bgbosscanopi2->AddComponent<Animator>();
		at->CreateAnimation(L"bosscanopi2AY", imageBGbossCanopi
			, Vector2(825.0f, 0.0f), Vector2(89.0f, 63.0f), 3);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"bosscanopi2AY", true);
		
		Texture* imagefruit = Resources::Load<Texture>(L"fruit"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Missionfruit 1.bmp");
		BackGround* fruit = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		sr = fruit->AddComponent<SpriteRenderer>();
		tr = fruit->GetComponent<Transform>();
		tr->SetPosition(Vector2(2680.0f, 580.0f));
		sr->SetImage(imagefruit);
		sr->SetScale(Vector2(4.5f, 4.5f));

		Texture* imagefruitcolumn = Resources::Load<Texture>(L"fruitcolumn"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Missionfruitcoulmn 1.bmp");
		FrontBackGround* fruitcolumn = object::Instantiate<FrontBackGround>(enums::eLayerType::FrontBackGround);
		sr = fruitcolumn->AddComponent<SpriteRenderer>();
		tr = fruitcolumn->GetComponent<Transform>();
		tr->SetPosition(Vector2(2850.0f, 580.0f));
		sr->SetImage(imagefruitcolumn);
		sr->SetScale(Vector2(4.5f, 4.5f));


		Texture* imagemiddleboss = Resources::Load<Texture>(L"middleboss"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1middleboss.bmp");
		MiddleBoss* middlboss = object::Instantiate<MiddleBoss>(enums::eLayerType::Monster);
		sr = middlboss->AddComponent<SpriteRenderer>();
		tr = middlboss->GetComponent<Transform>();
		tr->SetPosition(Vector2(9050.0f, 310.0f));
		sr->SetImage(imagemiddleboss);
		sr->SetScale(Vector2(4.5f, 4.5f));


		Texture* imageNpcOldMan = Resources::Load<Texture>(L"NpcOldMan"
			, L"..\\Resource\\Npc\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - POWs Helpful NPCs.bmp");
		OldMan* NpcOldMan1 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		tr = NpcOldMan1->GetComponent<Transform>();
		tr->SetPosition(Vector2(2850.0f, 300.0f));
		at = NpcOldMan1->AddComponent<Animator>();
		at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"NpcOldManIdleAX",true);



		OldMan* NpcOldMan2 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		tr = NpcOldMan2->GetComponent<Transform>();
		tr->SetPosition(Vector2(6200.0f, 210.0f));
		at = NpcOldMan2->AddComponent<Animator>();
		at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2 );
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"NpcOldManIdleAX", true);
		


		
		OldMan* NpcOldMan3 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		tr = NpcOldMan3->GetComponent<Transform>();
		tr->SetPosition(Vector2(9000.0f, 600.0f));
		at = NpcOldMan3->AddComponent<Animator>();
		at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"NpcOldManIdleAX", true);
	

		
		OldMan* NpcOldMan4 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		tr = NpcOldMan4->GetComponent<Transform>();
		tr->SetPosition(Vector2(13500.0f, 600.0f));
		at = NpcOldMan4->AddComponent<Animator>();
		at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"NpcOldManIdleAX", true);
	
		
		Texture* imagePlayer = Resources::Load<Texture>(L"Player"
			, L"..\\Resource\\Character\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Marco Rossi.bmp");
	
		PlayerBottom* playerbottom = object::Instantiate<PlayerBottom>(enums::eLayerType::Player);
		tr = playerbottom->GetComponent<Transform>();
<<<<<<< HEAD
		tr->SetPosition(Vector2(600.0f, 200.0f));
=======
		tr->SetPosition(Vector2(600.0f, 500.0f));
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		at = playerbottom->AddComponent<Animator>();
		at->CreateAnimation(L"PlayerIdlerightBAX", imagePlayer, Vector2(176.0f, 258.0f), Vector2(44.0f, 36.0f), 1);
		at->CreateAnimation(L"PlayerIdleleftBAX", imagePlayer, Vector2(0.0f, 299.0f), Vector2(44.0f, 36.0f), 1,Vector2(-35.0f, 0.0f));
		at->CreateAnimation(L"PlayerrightBAX", imagePlayer, Vector2(0.0f, 506.0f), Vector2(44.0f, 25.0f), 12,Vector2(-5.0f,25.0f));
		at->CreateAnimation(L"PlayerleftBAX", imagePlayer, Vector2(0.0f, 425.0f), Vector2(44.0f, 25.0f), 12, Vector2(-5.0f, 25.0f));
		at->CreateAnimation(L"PlayerdeadBAX", imagePlayer, Vector2(906.0f, 53.0f), Vector2(44.0f, 44.0f), 19, Vector2(5.0f, -4.0f));
<<<<<<< HEAD
		at->CreateAnimation(L"PlayerrightjumpBAX", imagePlayer, Vector2(0.0f, 616.0f), Vector2(44.0f, 44.0f), 12, Vector2(-5.0f, 40.0f),0.05f);
		at->CreateAnimation(L"PlayerleftjumpBAX", imagePlayer, Vector2(0.0f, 704.0f), Vector2(44.0f, 44.0f), 12, Vector2(5.0f, 40.0f),0.05f);
		at->CreateAnimation(L"PlayerrightdownBAX", imagePlayer, Vector2(0.0f, 1144.0f), Vector2(44.0f, 44.0f), 7, Vector2(13.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdownBAX", imagePlayer, Vector2(0.0f, 1188.0f), Vector2(44.0f, 44.0f), 7, Vector2(-25.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightdownwalkBAX", imagePlayer, Vector2(0.0f, 1232.0f), Vector2(44.0f, 44.0f), 7, Vector2(13.0f, -18.0f));
		at->CreateAnimation(L"PlayerleftdownwalkBAX", imagePlayer, Vector2(0.0f, 1276.0f), Vector2(44.0f, 44.0f), 7, Vector2(-7.0f, -18.0f));
		at->CreateAnimation(L"PlayerrightdownidleBAX", imagePlayer, Vector2(132.0f, 1144.0f), Vector2(44.0f, 44.0f), 4, Vector2(13.0f, -18.0f));
		at->CreateAnimation(L"PlayerleftdownidleBAX", imagePlayer, Vector2(132.0f, 1188.0f), Vector2(44.0f, 44.0f), 4, Vector2(-7.0f, -18.0f));
		at->CreateAnimation(L"PlayerrightrunjumpBAX", imagePlayer, Vector2(308.0f, 836.0f), Vector2(44.0f, 44.0f), 6, Vector2(-5.0f, -5.0f));
		at->CreateAnimation(L"PlayerleftrunjumpBAX", imagePlayer, Vector2(308.0f, 924.0f), Vector2(44.0f, 44.0f), 6, Vector2(0.0f, -5.0f));
		at->CreateAnimation(L"PlayerrightdowngunBAX", imagePlayer, Vector2(0.0f, 1320.0f), Vector2(88.0f, 44.0f), 6, Vector2(0.0f, -18.0f),0.01f);
		at->CreateAnimation(L"PlayerleftdowngunBAX", imagePlayer, Vector2(0.0f, 1364.0f), Vector2(88.0f, 44.0f), 6, Vector2(0.0f, -18.0f),0.01f);
		at->CreateAnimation(L"PlayerrightdownbombBAX", imagePlayer, Vector2(0.0f, 1408.0f), Vector2(44.0f, 44.0f), 6, Vector2(0.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"PlayerleftdownbombBAX", imagePlayer, Vector2(264.0f, 1408.0f), Vector2(44.0f, 44.0f), 6, Vector2(0.0f, -18.0f), 0.001f);
=======
		at->CreateAnimation(L"PlayerrightjumatAX", imagePlayer, Vector2(0.0f, 616.0f), Vector2(44.0f, 44.0f), 12, Vector2(5.0f, 40.0f),0.1f);
		at->CreateAnimation(L"PlayerleftjumatAX", imagePlayer, Vector2(0.0f, 704.0f), Vector2(44.0f, 44.0f), 12, Vector2(5.0f, 40.0f),0.1f);
		at->CreateAnimation(L"PlayerrightdownBAX", imagePlayer, Vector2(0.0f, 1144.0f), Vector2(44.0f, 44.0f), 7, Vector2(13.0f, -18.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdownBAX", imagePlayer, Vector2(0.0f, 1188.0f), Vector2(44.0f, 44.0f), 7, Vector2(-25.0f, -18.0f), 0.000001f);
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"PlayerIdlerightBAX", true);


		playerbottom->AddComponent<Rigidbody>();

		PlayerTop* playerTop = object::Instantiate<PlayerTop>(enums::eLayerType::Player);
		tr = playerTop->GetComponent<Transform>();
<<<<<<< HEAD
		tr->SetPosition(Vector2(600.0f, 170.0f));
=======
		tr->SetPosition(Vector2(600.0f, 470.0f));
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		at = playerTop->AddComponent<Animator>();
		at->CreateAnimation(L"PlayerIdlerightTAX", imagePlayer, Vector2(0.0f, 264.0f), Vector2(44.0f, 34.0f), 4 , Vector2(0.0f, 17.0f));
		at->CreateAnimation(L"PlayerIdleleftTAX", imagePlayer, Vector2(44.0f, 304.0f), Vector2(44.0f, 34.0f), 4, Vector2(-35.0f, 13.0f));
		at->CreateAnimation(L"PlayerrightTAX", imagePlayer, Vector2(0.0f, 472.0f), Vector2(44.0f, 34.0f), 12,Vector2(-5.0f, -7.0f));
		at->CreateAnimation(L"PlayerleftTAX", imagePlayer, Vector2(0.0f, 391.0f), Vector2(44.0f, 34.0f), 12, Vector2(-5.0f, -7.0f));
		at->CreateAnimation(L"PlayerdeadTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(-20.0f, -2.0f));
<<<<<<< HEAD
		at->CreateAnimation(L"PlayerrightjumpTAX", imagePlayer, Vector2(0.0f, 572.0f), Vector2(44.0f, 44.0f), 6, Vector2(-5.0f, -29.0f),0.2f);
		at->CreateAnimation(L"PlayerleftjumpTAX", imagePlayer, Vector2(0.0f, 660.0f), Vector2(44.0f, 44.0f), 6, Vector2(5.0f, -29.0f),0.2f);
=======
		at->CreateAnimation(L"PlayerrightjumatAX", imagePlayer, Vector2(0.0f, 572.0f), Vector2(44.0f, 44.0f), 6, Vector2(5.0f, -29.0f),0.2f);
		at->CreateAnimation(L"PlayerleftjumatAX", imagePlayer, Vector2(0.0f, 660.0f), Vector2(44.0f, 44.0f), 6, Vector2(5.0f, -29.0f),0.2f);
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		at->CreateAnimation(L"PlayerrightbombTAX", imagePlayer, Vector2(0.0f, 792.0f), Vector2(44.0f, 44.0f), 6, Vector2(-3.0f, -8.0f), 0.001f);
		at->CreateAnimation(L"PlayerleftbombTAX", imagePlayer, Vector2(0.0f, 924.0f), Vector2(44.0f, 44.0f), 6, Vector2(-6.0f, -8.0f), 0.001f);
		at->CreateAnimation(L"PlayerrightknifeTAX", imagePlayer, Vector2(0.0f, 836.0f), Vector2(44.0f, 88.0f), 6, Vector2(-8.0f, -3.0f),0.001f);
		at->CreateAnimation(L"PlayerleftknifeTAX", imagePlayer, Vector2(0.0f, 968.0f), Vector2(44.0f, 88.0f), 6, Vector2(-10.0f, -3.0f), 0.001f);
<<<<<<< HEAD
		at->CreateAnimation(L"PlayerrightgunTAX", imagePlayer, Vector2(0.0f, 1056.0f), Vector2(88.0f, 44.0f), 6, Vector2(5.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftgunTAX", imagePlayer, Vector2(0.0f, 1100.0f), Vector2(88.0f, 44.0f), 6, Vector2(-15.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);		
		at->CreateAnimation(L"PlayerrightdownwalkTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f) );
		at->CreateAnimation(L"PlayerleftdownwalkTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f));
		at->CreateAnimation(L"PlayerrightdownidleTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f));
		at->CreateAnimation(L"PlayerleftdownidleTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f));
		at->CreateAnimation(L"PlayerrightrunjumpTAX", imagePlayer, Vector2(308.0f, 792.0f), Vector2(44.0f, 44.0f), 6, Vector2(-15.0f, 0.0f));
		at->CreateAnimation(L"PlayerleftrunjumpTAX", imagePlayer, Vector2(308.0f, 880.0f), Vector2(44.0f, 44.0f), 6, Vector2(5.0f, 0.0f));
		at->CreateAnimation(L"PlayerleftdownbombTAX", imagePlayer, Vector2(264.0f, 1408.0f), Vector2(0.0f, 0.0f), 6, Vector2(0.0f, -18.0f), 0.001f);
		at->CreateAnimation(L"PlayerrightdowngunTAX", imagePlayer, Vector2(0.0f, 1320.0f), Vector2(0.0f, 0.0f), 6, Vector2(0.0f, -18.0f), 0.01f);
		at->CreateAnimation(L"PlayerrightkniferunTAX", imagePlayer, Vector2(0.0f, 836.0f), Vector2(44.0f, 88.0f), 6, Vector2(-8.0f, -13.0f), 0.001f);
		at->CreateAnimation(L"PlayerleftkniferunTAX", imagePlayer, Vector2(0.0f, 968.0f), Vector2(44.0f, 88.0f), 6, Vector2(-10.0f, -13.0f), 0.001f);
		at->CreateAnimation(L"PlayerrightgunrunTAX", imagePlayer, Vector2(0.0f, 1056.0f), Vector2(88.0f, 44.0f), 6, Vector2(5.0f, -10.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftgunrunTAX", imagePlayer, Vector2(0.0f, 1100.0f), Vector2(88.0f, 44.0f), 6, Vector2(-15.0f, -10.0f), 0.000001f);
=======
		at->CreateAnimation(L"PlayerrightgunTAX", imagePlayer, Vector2(0.0f, 1056.0f), Vector2(88.0f, 44.0f), 10, Vector2(5.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftgunTAX", imagePlayer, Vector2(0.0f, 1100.0f), Vector2(88.0f, 44.0f), 10, Vector2(-15.0f, 0.0f), 0.000001f);
		at->CreateAnimation(L"PlayerrightdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);
		at->CreateAnimation(L"PlayerleftdownTAX", imagePlayer, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 12, Vector2(5.0f, 72.0f), 0.000001f);		
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		at->SetScale(Vector2(4.5f, 4.5f));
		at->PlayAnimation(L"PlayerIdlerightTAX", true);

		


		Texture* imageCameraPlayer = Resources::Load<Texture>(L"CameraPlayer"
			, L"..\\Resource\\Character\\Dev.bmp");
		CameraPlayer* cameraplayer = object::Instantiate<CameraPlayer>(enums::eLayerType::Player);
		sr = cameraplayer->AddComponent<SpriteRenderer>();
		tr = cameraplayer->GetComponent<Transform>();
		tr->SetPosition(Vector2(600.0f, 400.0f));
		sr->SetImage(imageCameraPlayer);
		sr->SetAlpha(0.0f);

		Collider* col = playerbottom->AddComponent<Collider>();
		col->SetSize(Vector2(100.0f, 160.0f));
	
	
		
		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		tr = floor->AddComponent<Transform>();
		col->SetSize(Vector2(1500.0f, 100.0f));
		tr = floor->GetComponent<Transform>();
<<<<<<< HEAD
		tr->SetPosition(Vector2(600.0f, 600.0f));
=======
		tr->SetPosition(Vector2(600.0f, 800.0f));
		
>>>>>>> cdee4dc92013b8598fc7d8f8add74dd9f523ec77
		Camera::SetTarget(cameraplayer);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Npc, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);

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