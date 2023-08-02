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
#include "sbArabian.h"

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
	
		//Texture* imagesky = Resources::Load<Texture>(L"Mission1BackGroundSky"
		//	, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission sky.bmp");
		//BackGround* M1BackGroundSky = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		//SpriteRenderer* sr = M1BackGroundSky->AddComponent<SpriteRenderer>();
		//Transform* tr = M1BackGroundSky->GetComponent<Transform>();
		//tr->SetPosition(Vector2(4000.0f, 100.0f));
		//sr->SetImage(imagesky);
		//sr->SetScale(Vector2(4.5f, 4.5f));
	

		//Texture* imagebosssky = Resources::Load<Texture>(L"Mission1BackGroundbossSky"
		//	, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1bosssky.bmp");
		//BackGround* M1BackGroundBossSky = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		//sr = M1BackGroundBossSky->AddComponent<SpriteRenderer>();
		//tr = M1BackGroundBossSky->GetComponent<Transform>();
		//tr->SetPosition(Vector2(16000.0f, 70.0f));
		//sr->SetImage(imagebosssky);
		//sr->SetScale(Vector2(7.0f, 9.0f));

		//Texture* imageMDesert = Resources::Load<Texture>(L"Mission1BackGroundMDesert"
		//	, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1-mbackdesert.bmp");
		//BGMDesert* M1BackGroundMDesert1 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		//tr = M1BackGroundMDesert1->GetComponent<Transform>();
		//tr->SetPosition(Vector2(500.0f, 325.0f));
		//Animator* at = M1BackGroundMDesert1->AddComponent<Animator>();
		//at->CreateAnimation(L"Mission1BackGroundMDesertAY", imageMDesert
		//	, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		//at->SetScale(Vector2(4.5f, 4.5f));
		//at->PlayAnimation(L"Mission1BackGroundMDesertAY",true);
		//BGMDesert* M1BackGroundMDesert2 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		//tr = M1BackGroundMDesert2->GetComponent<Transform>();
		//tr->SetPosition(Vector2(1580.0f, 325.0f));
		//at = M1BackGroundMDesert2->AddComponent<Animator>();
		//at->CreateAnimation(L"Mission1BackGroundMDesertAY", imageMDesert
		//	, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		//at->SetScale(Vector2(4.5f, 4.5f));
		//at->PlayAnimation(L"Mission1BackGroundMDesertAY", true);
		//BGMDesert* M1BackGroundMDesert3 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		//tr = M1BackGroundMDesert3->GetComponent<Transform>();
		//tr->SetPosition(Vector2(2670.0f, 325.0f));
		//at = M1BackGroundMDesert3->AddComponent<Animator>();
		//at->CreateAnimation(L"Mission1BackGroundMDesertAY", imageMDesert
		//	, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		//at->SetScale(Vector2(4.5f, 4.5f));
		//at->PlayAnimation(L"Mission1BackGroundMDesertAY", true);
		//BGMDesert* M1BackGroundMDesert4 = object::Instantiate<BGMDesert>(enums::eLayerType::Backgroud);
		//tr = M1BackGroundMDesert4->GetComponent<Transform>();
		//tr->SetPosition(Vector2(3750.0f, 325.0f));
		//at = M1BackGroundMDesert4->AddComponent<Animator>();
		//at->CreateAnimation(L"Mission1BackGroundMDesertAY", imageMDesert
		//	, Vector2(0.0f, 0.0f), Vector2(249.0f, 35.0f), 4);
		//at->SetScale(Vector2(4.5f, 4.5f));
		//at->PlayAnimation(L"Mission1BackGroundMDesertAY", true);

	
		//

		//Texture* imageDesert = Resources::Load<Texture>(L"Mission1BackGroundDesert"
		//	, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1-backdesert.bmp");
		//BGDesert* M1BackGroundDesert = object::Instantiate<BGDesert>(enums::eLayerType::Backgroud);
		//sr = M1BackGroundDesert->AddComponent<SpriteRenderer>();
		//tr = M1BackGroundDesert->GetComponent<Transform>();
		//tr->SetPosition(Vector2(2240.0f, 400.0f));
		//sr->SetImage(imageDesert);
		//sr->SetScale(Vector2(4.5f, 4.5f));
	
	
		Texture* imageBG = Resources::Load<Texture>(L"Mission1BackGround"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1d.bmp");
		BackGround* M1BackGround = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		SpriteRenderer* sr = M1BackGround->AddComponent<SpriteRenderer>();
		Transform* tr = M1BackGround->GetComponent<Transform>();
		tr->SetPosition(Vector2(8550.0f, 250.0f));
		sr->SetImage(imageBG);
		sr->SetScale(Vector2(4.5f, 4.5f));
	
	/*	Texture* imageBGboss = Resources::Load<Texture>(L"Mission1bossbackground"
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
		at->PlayAnimation(L"bosscanopi2AY", true);*/
		
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


		//Texture* imagemiddleboss = Resources::Load<Texture>(L"middleboss"
		//	, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1middleboss.bmp");
		//MiddleBoss* middlboss = object::Instantiate<MiddleBoss>(enums::eLayerType::Monster);
		//sr = middlboss->AddComponent<SpriteRenderer>();
		//tr = middlboss->GetComponent<Transform>();
		//tr->SetPosition(Vector2(9050.0f, 310.0f));
		//sr->SetImage(imagemiddleboss);
		//sr->SetScale(Vector2(4.5f, 4.5f));


		//Texture* imageNpcOldMan = Resources::Load<Texture>(L"NpcOldMan"
		//	, L"..\\Resource\\Npc\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - POWs Helpful NPCs.bmp");
		//OldMan* NpcOldMan1 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		//tr = NpcOldMan1->GetComponent<Transform>();
		//tr->SetPosition(Vector2(2850.0f, 300.0f));
		//at = NpcOldMan1->AddComponent<Animator>();
		//at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		//at->SetScale(Vector2(4.5f, 4.5f));
		//at->PlayAnimation(L"NpcOldManIdleAX",true);



		//OldMan* NpcOldMan2 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		//tr = NpcOldMan2->GetComponent<Transform>();
		//tr->SetPosition(Vector2(6200.0f, 210.0f));
		//at = NpcOldMan2->AddComponent<Animator>();
		//at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2 );
		//at->SetScale(Vector2(4.5f, 4.5f));
		//at->PlayAnimation(L"NpcOldManIdleAX", true);
		//


		//
		//OldMan* NpcOldMan3 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		//tr = NpcOldMan3->GetComponent<Transform>();
		//tr->SetPosition(Vector2(9000.0f, 600.0f));
		//at = NpcOldMan3->AddComponent<Animator>();
		//at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		//at->SetScale(Vector2(4.5f, 4.5f));
		//at->PlayAnimation(L"NpcOldManIdleAX", true);
	

		//
		//OldMan* NpcOldMan4 = object::Instantiate<OldMan>(enums::eLayerType::Npc);
		//tr = NpcOldMan4->GetComponent<Transform>();
		//tr->SetPosition(Vector2(13500.0f, 600.0f));
		//at = NpcOldMan4->AddComponent<Animator>();
		//at->CreateAnimation(L"NpcOldManIdleAX", imageNpcOldMan, Vector2(0.0f, 11.0f), Vector2(44.0f, 42.0f), 2);
		//at->SetScale(Vector2(4.5f, 4.5f));
		//at->PlayAnimation(L"NpcOldManIdleAX", true);
		

		Arabian* arabian = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(2500.0f, 500.0f));

		PlayerBottom* playerbottom = object::Instantiate<PlayerBottom>(enums::eLayerType::Player, Vector2(600.0f, 200.0f));

		PlayerTop* playerTop = object::Instantiate<PlayerTop>(enums::eLayerType::Player);
		
		
			
		CameraPlayer* cameraplayer = object::Instantiate<CameraPlayer>(enums::eLayerType::Player , Vector2(600.0f, 400.0f));
	
		
		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor , Vector2(600.0f, 600.0f));
		Collider* col = floor->AddComponent<Collider>();
		col->SetSize(Vector2(1500.0f, 100.0f));
	

		Floor* floor2 = object::Instantiate<Floor>(eLayerType::Floor, Vector2(9200.0f, 720.0f));
		col = floor2->AddComponent<Collider>();
		col->SetSize(Vector2(16000.0f, 100.0f));

		
		Camera::SetTarget(cameraplayer);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Npc, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effects, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effects, eLayerType::Monster, true);
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