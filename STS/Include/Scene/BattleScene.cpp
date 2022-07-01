#include "BattleScene.h"
#include "../GameObject/MyPlayer.h"
#include "../GameObject/MyMonster.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/Deco.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"


#include "../Widget/WidgetComponent.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/TopPanel.h"
#include "../Widget/ImageWidget2.h"
#include "../Widget/CharacterHUD.h"

#include "../Collision/ColliderBox.h"


#include "../GameObject/Cards/GiveAttribute.h"

#include "../Widget/StartWindow.h"

#include "../GameObject/Card.h"
#include "../GameObject/CardManager.h"


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

	GetCamera()->SetResolution(1280.f, 1200.f);
	GetCamera()->SetWorldResolution(1280.f, 1200.f);
	GetCamera()->SetTargetPivot(0.f, 0.f);

	CreateObject<CBackObj>("BackObj");

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

	CCardManager::GetInst()->InitMyDeck();
	CCardManager::GetInst()->SetBringDeck();
	CCardManager::GetInst()->DrawCard(5);

	m_MyHand = CCardManager::GetInst()->GetHand();
	//list<CCard*>::iterator iter = m_MyHand.begin();
	//list<CCard*>::iterator end = m_MyHand.end();

	vector<CCard*>::iterator iter = m_MyHand.begin();
	vector<CCard*>::iterator end = m_MyHand.end();
	for (int i = 0; iter != end; iter++)
	{
		(*iter)->SetEnable(true);
		(*iter)->SetPos(200 + (100 * i), 600);
		//(*iter)->SetCollisionEnable(true);
		i++;
	}

	CMyPlayer* Player = CreateObject<CMyPlayer>("Player");

	CMyMonster* Monster = CreateObject<CMyMonster>("Monster");
	CMyMonster* Monster2 = CreateObject<CMyMonster>("Monster2");
	Monster2->SetPos(1050, 450);

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
	if (m_SceneUsedCard) 
	{
		m_MyHand = CCardManager::GetInst()->GetHand();
		for (int i = 0; i < m_MyHand.size(); i++) 
		{
			if (m_MyHand[i] != nullptr && m_MyHand[i]->GetUsedCard()) {
				//MessageBox(nullptr, TEXT("카드사용."), TEXT("^모^"), MB_OK);
				//m_MyHand[i]->SetEnable(false);
				CCardManager::GetInst()->AddDiscard(m_MyHand[i]);
				m_MyHand[i]->SetEnable(false);
				m_MyHand[i]->SetPos(0, 0);
				m_MyHand[i] = nullptr;
				CCardManager::GetInst()->SetHand(m_MyHand);
				CCardManager::GetInst()->HandSort();
				m_MyHand = CCardManager::GetInst()->GetHand();	
			}
		}
		
		//list<CCard*>::iterator iter = m_MyHand.begin();
		//list<CCard*>::iterator end = m_MyHand.end();
		//for (; iter != end; iter++)
		//{
		//	if ((*iter)->GetUsedCard()){
		//			MessageBox(nullptr, TEXT("카드사용."), TEXT("^모^"), MB_OK);
		//			(*iter)->SetEnable(false);
		//			//iter = m_MyHand.erase(iter);
		//			//end =  m_MyHand.end();
		//			continue;
		//	}
		//	else {
		//		(*iter)->SetEnable(true);
		//		//(*iter)->SetPos(200 + (100 * i), 600);
		//		(*iter)->Update(DeltaTime);
		//		++iter;
		//		//(*iter)->SetCollisionEnable(true);
		//		//i++;
		//}
		//}
		
	}
	SetUseCard(false);
}

void CBattleScene::CreateAnimationSequence()
{
}
