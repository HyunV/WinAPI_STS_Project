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

CBattleScene::CBattleScene()
{
	CreateAnimationSequence();
}

CBattleScene::~CBattleScene()
{

}

bool CBattleScene::Init()
{
	CCardManager::GetInst()->Init();
	//CreateWidgetWindow<CStartWindow>("StartWindow");
	
	CCameraObject* Camera = CreateObject<CCameraObject>("Camera");
	
	GetCamera()->SetResolution(1280.f, 800.f);
	GetCamera()->SetWorldResolution(1280.f, 2880.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	//GetCamera()->SetTarget(CInput::GetInst()->GetMouseObj());
	GetCamera()->SetTarget(Camera);
	SetCameraObj(Camera);

	CreateObject<CBackObj>("BackObj");
	
	m_BlackLayer = CreateObject<CFrontObj>("FrontObj");
	m_BlackLayer->SetEnable(m_BlackLayerSwitch);

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

	CCardManager::GetInst()->InitMyDeck();
	
	CCardManager::GetInst()->SetBringDeck();
	CCardManager::GetInst()->DrawCard(1);

	CMyPlayer* Player = CreateObject<CMyPlayer>("Player");

	CMyMonster* Monster = CreateObject<CMyMonster>("Monster");
	//CMyMonster* Monster2 = CreateObject<CMyMonster>("Monster2");
	//Monster2->SetPos(1050, 250);
	CTurnEffect* test = CreateObject<CTurnEffect>("Testtt");
	CBattleStartImage* image = CreateObject<CBattleStartImage>("Testtttttt");



	GetSceneResource()->LoadTexture("strike", TEXT("Cards/CardImage/strike.bmp"));
	GetSceneResource()->LoadTexture("shield", TEXT("Cards/CardImage/defend.bmp"));
	//카드 키워드 생성 //////////////////////////

	///////////////////카드 생성//////////////////////////

	SetPlayer(Player);

	CreateWidgetWindow<CTopPanel>("TopPanel");
	//
	return true;
}

void CBattleScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
	//사용한 카드 재정렬
	m_BlackLayer->SetEnable(m_BlackLayerSwitch);
	if (!m_BlackLayerSwitch)
	{
		m_MyHand = CCardManager::GetInst()->GetHand();
	}
	if (m_SceneUsedCard) 
	{
		m_MyHand = CCardManager::GetInst()->GetHand();
		for (int i = 0; i < m_MyHand.size(); i++) 
		{
			if (m_MyHand[i] != nullptr && m_MyHand[i]->GetUsedCard()) { //카드가 사용되면
	
				m_MyHand[i]->SetEnable(false);
				m_MyHand[i]->SetPos(0, 0);
				m_MyHand[i]->SetUsedCard(false);
				//m_MyHand[i]->SetCardControl(false);
				CCardManager::GetInst()->AddDiscard(m_MyHand[i]);
				m_MyHand[i] = nullptr;
				CCardManager::GetInst()->SetHand(m_MyHand);
				CCardManager::GetInst()->HandSort();
				m_MyHand = CCardManager::GetInst()->GetHand();	
				SetUseCard(false);
			}
		}		
	}	
}

void CBattleScene::CreateAnimationSequence()
{
}
