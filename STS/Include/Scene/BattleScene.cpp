#include "BattleScene.h"
#include "../GameObject/MyPlayer.h"
#include "../GameObject/MyMonster.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/FrontObj.h"
#include "../GameObject/Deco.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"

#include "../GameObject/BubbleMessage.h"

#include "../Widget/WidgetComponent.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/TopPanel.h"
#include "../Widget/ImageWidget2.h"

#include "../Collision/ColliderBox.h"

#include "../GameObject/Cards/GiveAttribute.h"

#include "../GameObject/Card.h"
#include "../GameObject/CardManager.h"

#include "../GameObject/CameraObject.h"

#include "../GameObject/TurnEffect.h"
#include "../GameObject/Effects/BattleStartImage.h"
#include "../GameObject/Map.h"
#include "../GameObject/MapIconObject.h"
#include "../Widget/Reward.h"

#include "SceneResource.h"

CBattleScene::CBattleScene()
{
	CreateAnimationSequence();
}

CBattleScene::~CBattleScene()
{
	CCardManager::DestroyInst();
}

bool CBattleScene::Init()
{
	CCardManager::GetInst()->Init();
	GetSceneResource()->CreateAnimationSequence("circle", "circle", TEXT("Map/circle.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 5; i++)
	{
		GetSceneResource()->AddAnimationFrame("circle", 96.f * i, 0.f, 96.f, 96.f);
	}

	GetSceneResource()->SetColorKey("circle", 255, 0, 255);
	//CreateWidgetWindow<CStartWindow>("StartWindow");
	
	CCameraObject* Camera = CreateObject<CCameraObject>("Camera");
	
	GetCamera()->SetResolution(1280.f, 800.f);
	GetCamera()->SetWorldResolution(1280.f, 2880.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	//GetCamera()->SetTarget(CInput::GetInst()->GetMouseObj());
	
	GetCamera()->SetTarget(Camera);
	SetCameraObj(Camera);

	CreateObject<CBackObj>("BackObj");

	//뒷배경 맵 생성
	m_BlackLayer = CreateObject<CFrontObj>("FrontObj");
	m_BlackLayer->SetEnable(m_BlackLayerSwitch);

	CMapIconObject* Stage1 = CreateObject<CMapIconObject>("Stage1");
	Stage1->SetTexture("monster", TEXT("Map/monster.bmp"));

	CMapIconObject* Stage2 = CreateObject<CMapIconObject>("Stage2");
	Stage2->SetTexture("monster", TEXT("Map/monster.bmp"));

	CMapIconObject* Stage3 = CreateObject<CMapIconObject>("Stage3");
	Stage3->SetTexture("rest", TEXT("Map/rest.bmp"));

	CMapIconObject* Stage4 = CreateObject<CMapIconObject>("Stage4");
	Stage4->SetTexture("elite", TEXT("Map/elite.bmp"));

	CMapIconObject* Stage5 = CreateObject<CMapIconObject>("Stage5");
	//Stage5->SetTexture("chest", TEXT("Map/chest.bmp"));
	Stage5->SetTexture("rest", TEXT("Map/rest.bmp"));

	CMapIconObject* Stage6 = CreateObject<CMapIconObject>("Stage6");
	Stage6->SetTexture("monster", TEXT("Map/monster.bmp"));

	CMapIconObject* Stage7 = CreateObject<CMapIconObject>("Stage7");
	//Stage7->SetTexture("shop", TEXT("Map/shop.bmp"));
	Stage7->SetTexture("monster", TEXT("Map/monster.bmp"));

	CMapIconObject* Stage8 = CreateObject<CMapIconObject>("Stage8");
	Stage8->SetTexture("monster", TEXT("Map/monster.bmp"));

	CMapIconObject* Stage9 = CreateObject<CMapIconObject>("Stage9");
	Stage9->SetTexture("rest", TEXT("Map/rest.bmp"));

	CMapIconObject* Stage10 = CreateObject<CMapIconObject>("Stage10");
	Stage10->SetTexture("boss", TEXT("Map/slime.bmp"));
	Stage10->SetSize(256.f, 256.f);


	Stage1->SetType(EMapIcon_Type::monster);
	Stage2->SetType(EMapIcon_Type::monster);
	Stage3->SetType(EMapIcon_Type::rest);
	Stage4->SetType(EMapIcon_Type::elite);
	//Stage5->SetType(EMapIcon_Type::chest);
	Stage5->SetType(EMapIcon_Type::rest);
	Stage6->SetType(EMapIcon_Type::monster);
	//Stage7->SetType(EMapIcon_Type::shop);
	Stage7->SetType(EMapIcon_Type::monster);
	Stage8->SetType(EMapIcon_Type::monster);
	Stage9->SetType(EMapIcon_Type::rest);
	Stage10->SetType(EMapIcon_Type::boss);
	
	AddStage(Stage1); AddStage(Stage2); AddStage(Stage3); AddStage(Stage4); 
	AddStage(Stage5); AddStage(Stage6); AddStage(Stage7); AddStage(Stage8);
	AddStage(Stage9); AddStage(Stage10);

	StageSort();

	CDeco* BackImageA = CreateObject<CDeco>("BackImageA");
	BackImageA->SetPos(0, 0);
	BackImageA->SetTexture("BackImageA", TEXT("Scene/B.bmp"));
	BackImageA->SetSize(1280, 512);
	BackImageA->SetColorKey(255, 0, 255);

	CDeco* BackImageB = CreateObject<CDeco>("BackImageB");
	BackImageB->SetPos(0, 550);
	BackImageB->SetTexture("BackImageB", TEXT("Scene/C.bmp"));
	BackImageB->SetSize(1280, 185);
	BackImageB->SetColorKey(255, 0, 255);

	CDeco* BackImageD = CreateObject<CDeco>("BackImageD");
	BackImageD->SetPos(590, 130);
	BackImageD->SetTexture("BackImageD", TEXT("Scene/F.bmp"));
	BackImageD->SetSize(466, 348);
	BackImageD->SetColorKey(255, 0, 255);

	CDeco* BackImageC = CreateObject<CDeco>("BackImageC");
	BackImageC->SetPos(590, 130);
	BackImageC->SetTexture("BackImageC", TEXT("Scene/G.bmp"));
	BackImageC->SetSize(254, 280);
	BackImageC->SetColorKey(255, 0, 255);

	//몬스터 패턴
	GetSceneResource()->LoadTexture("attackInt", TEXT("Intent/attack.bmp"));
	GetSceneResource()->LoadTexture("attackBuffInt", TEXT("Intent/attackBuff.bmp"));
	GetSceneResource()->LoadTexture("attackDebuffInt", TEXT("Intent/attackDebuff.bmp"));
	GetSceneResource()->LoadTexture("attackDefendInt", TEXT("Intent/attackDefend.bmp"));
	GetSceneResource()->LoadTexture("buffInt", TEXT("Intent/buff1.bmp"));
	GetSceneResource()->LoadTexture("debuffInt", TEXT("Intent/debuff1.bmp"));
	GetSceneResource()->LoadTexture("defendInt", TEXT("Intent/defend.bmp"));
	GetSceneResource()->LoadTexture("defendBuffInt", TEXT("Intent/defendBuff.bmp"));



	CCardManager::GetInst()->InitMyDeck();
	CCardManager::GetInst()->SetRandomDeck(1);

	//CCardManager::GetInst()->SetBringDeck(); 배틀스타트 이미지에 있음
	//CCardManager::GetInst()->DrawCard(5);

	CMyPlayer* Player = CreateObject<CMyPlayer>("Player");

	SetPlayer(Player);
	SetGameStart(true);

	//#$#$#%%#$^$$$$$$$$$$$$$$$$$$$$$$$$$$$$카드일러#%@$^%$^#%#%#$%#$%#$%#$%#$%#$%


	GetSceneResource()->LoadTexture("strike", TEXT("Cards/CardImage/strike.bmp"));
	GetSceneResource()->LoadTexture("shield", TEXT("Cards/CardImage/defend.bmp"));
	GetSceneResource()->LoadTexture("Bash", TEXT("Cards/CardImage/bash.bmp"));

	GetSceneResource()->LoadTexture("Barricades", TEXT("Cards/CardImage/barricade.bmp"));
	GetSceneResource()->LoadTexture("BodySlam", TEXT("Cards/CardImage/body_slam.bmp"));
	GetSceneResource()->LoadTexture("DemonForms", TEXT("Cards/CardImage/demon_form.bmp"));
	GetSceneResource()->LoadTexture("Entrench", TEXT("Cards/CardImage/entrench.bmp"));
	GetSceneResource()->LoadTexture("Inflame", TEXT("Cards/CardImage/inflame.bmp"));
	GetSceneResource()->LoadTexture("LimitBreak", TEXT("Cards/CardImage/limit_Break.bmp"));

	GetSceneResource()->LoadTexture("FootWorks", TEXT("Cards/CardImage/footwork.bmp"));
	GetSceneResource()->LoadTexture("bandageup", TEXT("Cards/CardImage/bandage_up.bmp"));
	GetSceneResource()->LoadTexture("bite", TEXT("Cards/CardImage/bite.bmp"));
	GetSceneResource()->LoadTexture("bloodletting", TEXT("Cards/CardImage/bloodletting.bmp"));
	GetSceneResource()->LoadTexture("bludgeon", TEXT("Cards/CardImage/bludgeon.bmp"));
	GetSceneResource()->LoadTexture("clothesline", TEXT("Cards/CardImage/clothesline.bmp"));
	GetSceneResource()->LoadTexture("finesse", TEXT("Cards/CardImage/finesse.bmp"));
	GetSceneResource()->LoadTexture("flashOfSteel", TEXT("Cards/CardImage/flash_of_steel.bmp"));
	GetSceneResource()->LoadTexture("good_instincts", TEXT("Cards/CardImage/good_instincts.bmp"));
	GetSceneResource()->LoadTexture("hemokinesis", TEXT("Cards/CardImage/hemokinesis.bmp"));
	GetSceneResource()->LoadTexture("impervious", TEXT("Cards/CardImage/impervious.bmp"));

	//카드 키워드 생성 //////////////////////////

	///////////////////카드 생성//////////////////////////
	CreateWidgetWindow<CTopPanel>("TopPanel");

	m_MapLayer = CreateObject<CMap>("MapObj");
	SetMap(m_MapLayer);
	SetMapSwitch(true);
	
	m_MapLayer->SetEnable(true);

	return true;
}

void CBattleScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
	//사용한 카드 재정렬
	m_BlackLayer->SetEnable(m_BlackLayerSwitch);
	m_Map->SetEnable(m_MapLayerSwitch);

	if (!m_IsBattle) 
	{
		
		//for (int i = 0; i < m_MyHand.size(); i++)
		//{
		//	m_MyHand[i]->SetEnable(false);
		//	m_MyHand[i]->SetPos(0, 0);
		//	m_MyHand[i]->SetUsedCard(false);
		//	m_MyHand[i] = nullptr;
		//	CCardManager::GetInst()->SetHand(m_MyHand);
		//	CCardManager::GetInst()->HandSort();
		//	m_MyHand = CCardManager::GetInst()->GetHand();
		//	SetUseCard(false);
		//}
	}
	//
	if (!m_BlackLayerSwitch || !m_MapLayerSwitch)
	{
		m_MyHand = CCardManager::GetInst()->GetHand();
	}
	//if (m_SceneUsedCard) 
	//{
	//	m_MyHand = CCardManager::GetInst()->GetHand();
	//	for (int i = 0; i < m_MyHand.size(); i++) 
	//	{
	//		if (m_MyHand[i] != nullptr && m_MyHand[i]->GetUsedCard()) { //카드가 사용되면
	//
	//			m_MyHand[i]->SetEnable(false);
	//			m_MyHand[i]->SetPos(0, 0);
	//			m_MyHand[i]->SetUsedCard(false);
	//			CCardManager::GetInst()->AddDiscard(m_MyHand[i]);
	//			m_MyHand[i] = nullptr;
	//			CCardManager::GetInst()->SetHand(m_MyHand);
	//			CCardManager::GetInst()->HandSort();
	//			m_MyHand = CCardManager::GetInst()->GetHand();	
	//			SetUseCard(false);
	//		}
	//	}		
	//}



}

void CBattleScene::CreateAnimationSequence()
{
}
