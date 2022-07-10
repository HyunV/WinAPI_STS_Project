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
	CCardManager::GetInst()->SetRandomDeck(17);

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
	GetSceneResource()->LoadTexture("iron_wave", TEXT("Cards/CardImage/iron_wave.bmp"));
	GetSceneResource()->LoadTexture("JAX", TEXT("Cards/CardImage/jax.bmp"));
	GetSceneResource()->LoadTexture("master_of_strategy", TEXT("Cards/CardImage/master_of_strategy.bmp"));
	GetSceneResource()->LoadTexture("offering", TEXT("Cards/CardImage/offering.bmp"));
	GetSceneResource()->LoadTexture("pommel_strike", TEXT("Cards/CardImage/pommel_strike.bmp"));
	GetSceneResource()->LoadTexture("seeing_red", TEXT("Cards/CardImage/seeing_red.bmp"));
	GetSceneResource()->LoadTexture("shrug_it_off", TEXT("Cards/CardImage/shrug_it_off.bmp"));
	GetSceneResource()->LoadTexture("swift_strike", TEXT("Cards/CardImage/swift_strike.bmp"));
	GetSceneResource()->LoadTexture("uppercut", TEXT("Cards/CardImage/uppercut.bmp"));

	//사운드%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GetSceneResource()->LoadSound("BGM", "StageBGM", true, "05_Stage1.ogg"); //
	GetSceneResource()->SoundPlay("StageBGM"); //

	GetSceneResource()->LoadSound("UI", "mouseHovered", false, "02.MouseHovered.wav");
	GetSceneResource()->LoadSound("UI", "UIClick", false, "03.Click.wav");
	GetSceneResource()->LoadSound("UI", "CircledSound", false, "06_MapCheck.ogg"); //
	GetSceneResource()->LoadSound("BGM", "EliteSound", true, "07_Elite.ogg");
	GetSceneResource()->LoadSound("UI", "TurnOffSound", false, "08_TurnOffButton.ogg"); 
	GetSceneResource()->LoadSound("Effect", "jawDeath", false, "jawDeath.ogg"); //
	GetSceneResource()->LoadSound("UI", "SelectHandSound", false, "09_SelectHand.ogg"); //
	GetSceneResource()->LoadSound("UI", "MapButtonSound", false, "10_MapButton.ogg"); //
	GetSceneResource()->LoadSound("UI", "DecksButtonSound", false, "11_DecksButton.ogg"); //

	GetSceneResource()->LoadSound("Effect", "12_EnemyAttack", false, "12_EnemyAttack.ogg"); //// ddddddd
	GetSceneResource()->LoadSound("Effect", "13_RitBuff", false, "13_RitBuff.ogg"); //ㅇ
	GetSceneResource()->LoadSound("Effect", "14_RitDead", false, "14_RitDead.ogg"); //ㅇ

	GetSceneResource()->LoadSound("Effect", "15_Attack1", false, "15_Attack1.ogg"); // d
	GetSceneResource()->LoadSound("Effect", "16_Attack2", false, "16_Attack2.ogg"); // d
	GetSceneResource()->LoadSound("Effect", "17_Attack3", false, "17_Attack3.ogg"); //d
	GetSceneResource()->LoadSound("Effect", "18_Attack4", false, "18_Attack4.ogg"); //d
	GetSceneResource()->LoadSound("Effect", "19_Attack5", false, "19_Attack5.ogg"); //d
	GetSceneResource()->LoadSound("Effect", "04_Attack1", false, "04_Attack1.ogg"); //d

	GetSceneResource()->LoadSound("Effect", "20_Shield1", false, "20_Shield1.ogg"); //d
	GetSceneResource()->LoadSound("Effect", "21_Shield2", false, "21_Shield2.ogg"); //d
	GetSceneResource()->LoadSound("Effect", "22_Shield3", false, "22_Shield3.ogg"); //d
	GetSceneResource()->LoadSound("Effect", "23_Shield4", false, "23_Shield4.ogg"); //d
	GetSceneResource()->LoadSound("Effect", "24_BrokenShield", false, "24_BrokenShield.ogg"); //d

	GetSceneResource()->LoadSound("Effect", "25_SlimeAttack", false, "25_SlimeAttack.ogg"); //
	GetSceneResource()->LoadSound("Effect", "26_BossSlimeAttack", false, "26_BossSlimeAttack.ogg"); //
	GetSceneResource()->LoadSound("Effect", "27_Slime_Debuff", false, "27_Slime_Debuff.ogg"); //
	GetSceneResource()->LoadSound("Effect", "28_BossSlime_P2", false, "28_BossSlime_P2.ogg"); //
	GetSceneResource()->LoadSound("Effect", "29_BossSlimeDead", false, "29_BossSlimeDead.ogg"); //
	GetSceneResource()->LoadSound("Effect", "30_BossSlimeDead2", false, "30_BossSlimeDead2.ogg"); //
	GetSceneResource()->LoadSound("Effect", "31_VictoryBoss", false, "31_VictoryBoss.ogg");

	//###################
	GetSceneResource()->LoadSound("Effect", "32_DeBuff", false, "32_DeBuff.ogg");
	GetSceneResource()->LoadSound("Effect", "33_Buff", false, "33_Buff.ogg");
	GetSceneResource()->LoadSound("Effect", "34_UsePower", false, "34_UsePower.ogg");

	GetSceneResource()->LoadSound("Effect", "35_BattleStart", false, "35_BattleStart.ogg");//
	GetSceneResource()->LoadSound("Effect", "36_EnemyTurn", false, "36_EnemyTurn.ogg");//

	GetSceneResource()->LoadSound("Effect", "37_PlusHP", false, "37_PlusHP.ogg");
	GetSceneResource()->LoadSound("BGM", "38_BossBGM", false, "38_BossBGM.ogg");

	GetSceneResource()->LoadSound("Effect", "39_EliteBigAttack", false, "39_EliteBigAttack.ogg");
	GetSceneResource()->LoadSound("Effect", "40_EliteDead", false, "40_EliteDead.ogg");
	GetSceneResource()->LoadSound("Effect", "41_EliteBuff", false, "41_EliteBuff.ogg");

	GetSceneResource()->LoadSound("UI", "42_UseCard", false, "42_UseCard.ogg");
	GetSceneResource()->LoadSound("Effect", "43_DefeatGame", false, "43_DefeatGame.ogg");
	GetSceneResource()->LoadSound("BGM", "44_RestTime", true, "44_RestTime.ogg");
	GetSceneResource()->LoadSound("Effect", "45_Resting", false, "45_Resting.ogg");



	//GetSceneResource()->LoadSound("Effect", "26_BossSlimeAttack", false, "26_BossSlimeAttack.ogg"); //


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
