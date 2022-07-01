#include "CardManager.h"
#include "Card.h"
#include "Cards/CardAbility.h"
#include "Cards/GiveAttribute.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneResource.h"
#include "GameObject.h"

DEFINITION_SINGLE(CCardManager);

CCardManager::CCardManager()
{
	m_CardCheck = nullptr;
	m_MouseClicked = false;
}

CCardManager::~CCardManager()
{
	
}
void CCardManager::HandSort()
{
	int count = 0;
	vector<CCard*> SortHand;

	for (int i = 0; i < m_Hand.size(); i++) 
	{
		if (m_Hand[i] != nullptr) {
			SortHand.push_back(m_Hand[i]);
		}
	}
	m_Hand = SortHand;
	for (int i = 0; i < m_Hand.size(); i++) 
	{
		m_Hand[i]->SetEnable(true);
		m_Hand[i]->SetPos(200 + (100 * i), 600);
	}
}
void CCardManager::UseCard()
{
	//이터레이터 돌려서 사용된카드 확인
	//그 카드를 핸드에서 제거하고 버린 카드로 이동한다.
	
	//list<CCard*>::iterator iter = m_Hand.begin();
	//list<CCard*>::iterator End = m_Hand.end();

	//for (; iter != End; iter++)
	//{
	//	if ((*iter)->GetUsedCard()) {
	//		(*iter)->SetEnable(false);
	//		m_disCardDummy.push_back(*iter);

	//		iter = m_Hand.erase(iter);
	//		End = m_Hand.end();
	//		//continue;
	//	}

	//}

}
bool CCardManager::Init()
{
	return true;
}

void CCardManager::InitMyDeck()
{
	CGiveAttribute* DefaultDamage = m_Scene->CreateObject<CGiveAttribute>("DefaultDamage");
	DefaultDamage->SetType(Card_Attribute::Damage, 6);
	CGiveAttribute* DefaultShield = m_Scene->CreateObject<CGiveAttribute>("DefaultShield");
	DefaultShield->SetType(Card_Attribute::Shield, 5);

	CCard* Strike1 = m_Scene->CreateObject<CCard>("Strike1");
	Strike1->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike1->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike1->AddAbility(DefaultDamage);

	CCard* Strike2 = m_Scene->CreateObject<CCard>("Strike2");
	Strike2->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike2->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike2->AddAbility(DefaultDamage);

	CCard* Strike3 = m_Scene->CreateObject<CCard>("Strike3");
	Strike3->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike3->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike3->AddAbility(DefaultDamage);

	CCard* Strike4 = m_Scene->CreateObject<CCard>("Strike4");
	Strike4->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike4->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike4->AddAbility(DefaultDamage);

	CCard* Strike5 = m_Scene->CreateObject<CCard>("Strike5");
	Strike5->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike5->SetCardAttribute(TEXT("타겨격"), Card_Type::Attack, 1);
	Strike5->AddAbility(DefaultDamage);
	Strike5->SetRenderLayer(ERender_Layer::Hand);

	//수비
	CCard* Defend1 = m_Scene->CreateObject<CCard>("Defend1");
	Defend1->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend1->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend1->AddAbility(DefaultShield);

	CCard* Defend2 = m_Scene->CreateObject<CCard>("Defend2");
	Defend2->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend2->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend2->AddAbility(DefaultShield);

	CCard* Defend3 = m_Scene->CreateObject<CCard>("Defend3");
	Defend3->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend3->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend3->AddAbility(DefaultShield);

	CCard* Defend4 = m_Scene->CreateObject<CCard>("Defend4");
	Defend4->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend4->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend4->AddAbility(DefaultShield);


	m_mainDeck.push_back(Strike1);
	m_mainDeck.push_back(Strike2);
	m_mainDeck.push_back(Strike3);
	m_mainDeck.push_back(Strike4);
	m_mainDeck.push_back(Strike5);

	m_mainDeck.push_back(Defend1);
	m_mainDeck.push_back(Defend2);
	m_mainDeck.push_back(Defend3);
	m_mainDeck.push_back(Defend4);
	
}

void CCardManager::SetBringDeck()
{
	m_bringCardDummy = GetMainDeck();
}

void CCardManager::DrawCard(int value)
{
	for (int i = 0; i < value; i++) {
		//뽑을 카드 
		if (m_Hand.size() > 10)
			break;

		if (m_bringCardDummy.size() == 0) {
			if (m_disCardDummy.size() == 0) {
				MessageBox(nullptr, TEXT("뽑을 카드가 없다"), TEXT("^모^"), MB_OK);
				return;
			}
			m_bringCardDummy = m_disCardDummy;
			m_disCardDummy.clear();
		}
			//섞어주는 코드

		m_Hand.push_back(m_bringCardDummy.back());
		
		m_bringCardDummy.pop_back();
	}
	HandSort();
}

void CCardManager::AddDiscard(CGameObject* Discard)
{
	m_disCardDummy.push_back((CCard*)Discard);
}

void CCardManager::BattleStart()
{
	m_bringCardDummy = m_mainDeck; //메인 덱 가져올 카드로 가져온다
	//가져올 덱 을 섞는다.
	//카드를 n장 뽑는다
	//핸드에 n장을 가져온다.
}

CGameObject* CCardManager::CardCheck()
{
	return m_CardCheck;
}


