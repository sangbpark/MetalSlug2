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
#include "sbHOldMan.h"
#include "sbCameraPlayer.h"
#include "sbAnimator.h"
#include "sbBGbossCanopi.h"
#include "sbCollider.h"
#include "sbCollisionManager.h"
#include "sbRigidbody.h"
#include "sbFloor.h"
#include "sbArabian.h"
#include "sbBGBackGround.h"
#include "sbUi.h"
#include "sbBerserker.h"
#include "sbTruck.h"
#include "sbCamel.h"
#include "sbBoss.h"
#include "sbBGBackGround.h"
#include "sbInput.h"
#include "sbTime.h"
#include "sbLoadingScene.h"


namespace sb
{
	Mission1::Mission1()
		: mEndTime(0.0f)
	{
	}
	Mission1::~Mission1()
	{
	}
	void Mission1::Initialize()
	{

		Texture* imageBG1 = Resources::Load<Texture>(L"Mission1BackGround1"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1d1.bmp");
		Texture* imageBG2 = Resources::Load<Texture>(L"Mission1BackGround2"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1d2.bmp");
		Texture* imageBG3 = Resources::Load<Texture>(L"Mission1BackGround3"
			, L"..\\Resource\\Map\\Neo Geo NGCD - Metal Slug 2 Metal Slug X - Mission 1d3.bmp");
		BackGround* M1BackGround1 = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		M1BackGround1->SetStage(BackGround::eStage::First);
		SpriteRenderer* sr = M1BackGround1->AddComponent<SpriteRenderer>();
		Transform* tr = M1BackGround1->GetComponent<Transform>();
		tr->SetPosition(Vector2(3700.0f, 250.0f)); //8550
		sr->SetImage(imageBG1);
		sr->SetScale(Vector2(4.5f, 4.5f));

		BackGround* M1BackGround2 = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		M1BackGround2->SetStage(BackGround::eStage::Second);
		sr = M1BackGround2->AddComponent<SpriteRenderer>();
		tr = M1BackGround2->GetComponent<Transform>();
		tr->SetPosition(Vector2(11225.0f, 250.0f)); //8550
		sr->SetImage(imageBG2);
		sr->SetScale(Vector2(4.5f, 4.5f));

		BackGround* M1BackGround3 = object::Instantiate<BackGround>(enums::eLayerType::Backgroud);
		M1BackGround2->SetStage(BackGround::eStage::Last);
		sr = M1BackGround3->AddComponent<SpriteRenderer>();
		tr = M1BackGround3->GetComponent<Transform>();
		tr->SetPosition(Vector2(16060.0f, 250.0f)); //8550
		sr->SetImage(imageBG3);
		sr->SetScale(Vector2(4.5f, 4.5f));
	
		BGBackGround* bgbackground = object::Instantiate<BGBackGround>(enums::eLayerType::Backgroud, Vector2(16460.0f, 190.0f));

		BGbossCanopi* bgbosscanopi = object::Instantiate<BGbossCanopi>(enums::eLayerType::Backgroud, Vector2(15740.0f, 230.0f));
		bgbosscanopi->SetCanopiPosition(BGbossCanopi::ePosition::Left);

		BGbossCanopi* bgbosscanopi2 = object::Instantiate<BGbossCanopi>(enums::eLayerType::Backgroud, Vector2(16960.0f, 250.0f));
		bgbosscanopi2->SetCanopiPosition(BGbossCanopi::ePosition::Right);
		
		
		
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


		HOldMan* holdman1 = object::Instantiate<HOldMan>(eLayerType::Npc, Vector2(2850.0f, 300.0f));
		holdman1->SetItems(HOldMan::eItems::Heavy);
		HOldMan* holdman2 = object::Instantiate<HOldMan>(eLayerType::Npc, Vector2(3500.0f, 300.0f));
		holdman2->SetItems(HOldMan::eItems::Supply);
		HOldMan* holdman3 = object::Instantiate<HOldMan>(eLayerType::Npc, Vector2(5500.0f, 300.0f)); 
		holdman3->SetItems(HOldMan::eItems::Heavy);

	

		//Arabian* arabian1 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(1500.0f, 600.0f));
		//Arabian* arabian2 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(1700.0f, 600.0f));
		//Arabian* arabian3 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(1900.0f, 600.0f));
		//Arabian* arabian4 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(2200.0f, 600.0f));
		//Arabian* arabian5 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(2500.0f, 600.0f));
		//Arabian* arabian6 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(3000.0f, 600.0f));
		//Arabian* arabian7 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(3500.0f, 600.0f));
		//Arabian* arabian8 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(3600.0f, 600.0f));
		//Arabian* arabian9 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(5000.0f, 600.0f));
		//Arabian* arabian10 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(13000.0f, 500.0f));
		//Arabian* arabian11 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(13100.0f, 500.0f));
		//Arabian* arabian12 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(13200.0f, 500.0f));
		//Arabian* arabian13 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(13300.0f, 500.0f));
		//Arabian* arabian14 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(13500.0f, 500.0f));
		//Arabian* arabian15 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(13700.0f, 500.0f));
		//Arabian* arabian16 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(13900.0f, 500.0f));
		//Arabian* arabian17 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(14000.0f, 500.0f));
		//Arabian* arabian18 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(14200.0f, 500.0f));
		//Arabian* arabian19 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(14300.0f, 500.0f));
		//Arabian* arabian20 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(14500.0f, 500.0f));
		//Arabian* arabian21 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(4000.0f, 500.0f));
		//Arabian* arabian22 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(4300.0f, 500.0f));
		//Arabian* arabian23 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(4500.0f, 500.0f));
		//Arabian* arabian24 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(14800.0f, 500.0f));
		//Arabian* arabian25 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(15000.0f, 500.0f));
		//Arabian* arabian26 = object::Instantiate<Arabian>(enums::eLayerType::Monster, Vector2(14900.0f, 500.0f));

		Camel* camel = object::Instantiate<Camel>(enums::eLayerType::Vehicle, Vector2(750.0f, 200.0f));

		PlayerBottom* playerbottom = object::Instantiate<PlayerBottom>(enums::eLayerType::Player, Vector2(750.0f, 600.0f));

		PlayerTop* playerTop = object::Instantiate<PlayerTop>(enums::eLayerType::Player);
		playerTop->SetPlayerBottomOnwer(playerbottom);
		
		

	
			
		CameraPlayer* cameraplayer = object::Instantiate<CameraPlayer>(enums::eLayerType::Player , Vector2(600.0f, 400.0f));
		cameraplayer->SetOwner(playerbottom);		
		mCamera = cameraplayer;
	
		Floor* floor2 = object::Instantiate<Floor>(eLayerType::Floor, Vector2(9200.0f, 720.0f));
		Collider* col = floor2->AddComponent<Collider>();
		col->SetSize(Vector2(20000.0f, 100.0f));

		Sound* sound = Resources::Load<Sound>(L"bgsound"
			, L"..\\Resource\\sound\\Metal-Slug-2.wav");
		mSound = sound;
		cameraplayer->SetSound(mSound);
		
		
		Camera::SetTarget(cameraplayer);

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Npc, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::ControlTower, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Vehicle, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Vehicle, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Npc, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Npc, eLayerType::Effects, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effects, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effects, eLayerType::Effects, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effects, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Effects, eLayerType::BossMonster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Effects, true);
	}
	void Mission1::Update()
	{
		if(LoadingScene::GetSceneLoading())
		{
			mSound->Play(true);
			LoadingScene::SetSceneNext(false);
		}
		Scene::Update();
		Camera::SetTarget(mCamera);
		Camera::Update();
		if (Input::GetKeyDown(eKeyCode::V))
		{
			if (mColliderRender)
				mColliderRender = false;
			else
				mColliderRender = true;
		}
		Collider::SetColliderRender(mColliderRender);
		if (CameraPlayer::GetStageClear())
		{

			if (mEndTime == 0.0f)
			{
				Sound* sound = Resources::Load<Sound>(L"missionComplete"
					, L"..\\Resource\\sound\\metal-slug-mission-complete-_1_.wav");
				sound->Play(false);
				sound->SetVolume(150.0f);
			}
			mEndTime += Time::DeltaTime();
		
			if(mEndTime>= 10.0f)
			{
				mEndTime = 0.0f;
				Camera::Clear();
				SceneManager::LoadScene(L"EndScene");
				LoadingScene::SetSceneLoading(true);
				LoadingScene::SetSceneNext(true);
			}
			
		}
	}


	void Mission1::Render(HDC hdc)
	{
		Scene::Render(hdc);
		LoadingScene::Render(hdc);
		if (!LoadingScene::GetSceneNext())
			LoadingScene::SetSceneLoading(false);

	}

}