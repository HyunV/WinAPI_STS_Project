#include "CardManager.h"
#include "Card.h"
#include "Cards/CardAbility.h"
#include "Cards/GiveAttribute.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneResource.h"
#include "GameObject.h"
#include "BubbleMessage.h"

DEFINITION_SINGLE(CCardManager);

CCardManager::CCardManager()
{
	m_CardCheck = nullptr;
	m_MouseClicked = false;
	m_MouseHovered = false;
	m_MonstersTurn = false;
	m_PlayerTurn = false;
	m_TurnCount = 1;
	m_UsedCard = false;
	m_Scene = nullptr;
	m_DrawCard = 5;
}

CCardManager::~CCardManager()
{
	
}
void CCardManager::EnableHand(bool Enable)
{
	for (int i = 0; i < m_Hand.size(); i++)
	{
		m_Hand[i]->SetEnable(Enable);
	}
}
void CCardManager::HandSort()
{
	vector<CCard*> SortHand;

	for (int i = 0; i < m_Hand.size(); i++) 
		//핸드창에 nullptr이 아닌애들만 임시 핸드에 담아준다.
	{
		if (m_Hand[i] != nullptr) {
			SortHand.push_back(m_Hand[i]);
		}
	}
	m_Hand = SortHand;

	//(처음위치 + (거리 * i), 600);
	for (int i = 0; i < m_Hand.size(); i++) //임시로 담은 애들을 재정렬한다.
	{
		m_Hand[i]->SetEnable(true);
		//m_Hand[i]->SetCardControl(true);
		m_Hand[i]->SetPos((float)(550-(40*(m_Hand.size()))) + (80* i), 600);
	}

	//케이스문으로 장수를 따져서 정렬하게 하자
}
void CCardManager::CardView(vector<CCard*> deck)
{
	if (!m_Hand.size() == 0) {
		EnableHand(false);
	}	
	int x = -1;
	int y = 0;
	for (int i = 0; i < deck.size(); i++)
	{
		if (i % 5 == 0) {
			x++;
			y = 0;
		}	
		deck[i]->SetEnable(true);
		deck[i]->SetPos((float)180+(y*200), (float)100+(300*x));
		y++;
	}	
}
void CCardManager::ClearCard(vector<CCard*> deck)
{
	
	for (int i = 0; i < deck.size(); i++)
	{		
		deck[i]->SetPos(0.f, 0.f);
		deck[i]->SetEnable(false);
	}

	HandSort();
}
void CCardManager::HandToDiscard()
{
	if (!m_Hand.size() == 0) {
		EnableHand(false);
	}
	for (int i = 0; i < m_Hand.size(); i++)
	{
		if (m_Hand[i] == nullptr) {
			continue;
		}
		m_Hand[i]->SetPos(0, 0);
		m_Hand[i]->SetUsedCard(false);
		m_Hand[i]->SetEnable(false);
		m_disCardDummy.push_back(m_Hand[i]);
		m_Hand[i] = nullptr;
	}
	m_Hand.clear();
	int a = (int)m_Hand.size();
}
bool CCardManager::Init()
{
	m_PlayerTurn = false;
	m_MonstersTurn = false;
	m_TurnCount = 1;
	return true;
}



void CCardManager::SetPlayerTurn(bool Enable)
{
		m_PlayerTurn = Enable;
}

void CCardManager::InitMyDeck()
{
	CGiveAttribute* DefaultDamage = m_Scene->CreateObject<CGiveAttribute>("DefaultDamage");
	DefaultDamage->SetType(Card_Attribute::Damage, 6);
	CGiveAttribute* DefaultShield = m_Scene->CreateObject<CGiveAttribute>("DefaultShield");
	DefaultShield->SetType(Card_Attribute::Shield, 5);
	CGiveAttribute* HyperDamage = m_Scene->CreateObject<CGiveAttribute>("HyperDamage");
	HyperDamage->SetType(Card_Attribute::Damage, 99999);

	CCard* Strike1 = m_Scene->CreateObject<CCard>("Strike1");
	Strike1->SetCardInfo("strike", Card_Type::Attack, Card_Value::Special, false, false);
	Strike1->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike1->AddAbility(DefaultDamage);
	Strike1->SetRenderLayer(ERender_Layer::Hand);

	CCard* Strike2 = m_Scene->CreateObject<CCard>("Strike2");
	Strike2->SetCardInfo("strike", Card_Type::Attack, Card_Value::Rare, false, false);
	Strike2->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike2->AddAbility(DefaultDamage);

	CCard* Strike3 = m_Scene->CreateObject<CCard>("Strike3");
	Strike3->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, true);
	Strike3->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike3->AddAbility(DefaultDamage);

	CCard* Strike4 = m_Scene->CreateObject<CCard>("Strike4");
	Strike4->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike4->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike4->AddAbility(DefaultDamage);

	CCard* Strike5 = m_Scene->CreateObject<CCard>("Strike5");
	Strike5->SetCardInfo("strike", Card_Type::Attack, Card_Value::Rare, true, false);
	Strike5->SetCardAttribute(TEXT("전설의 타격"), Card_Type::Attack, 0);
	Strike5->AddAbility(HyperDamage);


	//수비
	CCard* Defend1 = m_Scene->CreateObject<CCard>("Defend1");
	Defend1->SetCardInfo("shield", Card_Type::Power, Card_Value::Common, false, false);
	Defend1->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend1->AddAbility(DefaultShield);

	CCard* Defend2 = m_Scene->CreateObject<CCard>("Defend2");
	Defend2->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend2->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend2->AddAbility(DefaultShield);

	CCard* Defend3 = m_Scene->CreateObject<CCard>("Defend3");
	Defend3->SetCardInfo("shield", Card_Type::Skill, Card_Value::Rare, false, false);
	Defend3->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend3->AddAbility(DefaultShield);

	CCard* Defend4 = m_Scene->CreateObject<CCard>("Defend4");
	Defend4->SetCardInfo("shield", Card_Type::Skill, Card_Value::Special, true, false);
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
			return;
		
		//뽑을카드가 없을 때
		if (m_bringCardDummy.size() == 0) { 
			if (m_disCardDummy.size() == 0) {
				CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("Messages");
				Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("손이 가득 찼다."));
				HandSort();
				return;
			}
			m_bringCardDummy = m_disCardDummy;
			m_disCardDummy.clear();
		}
		//섞어주는 코드
		vector<CCard*> Temp = m_bringCardDummy;
		std::random_shuffle(Temp.begin(), Temp.end());

		m_Hand.push_back(Temp.back());
		for (int i = 0; i < m_bringCardDummy.size(); i++)
		{
			if (m_bringCardDummy[i] == Temp.back())
			{
				m_bringCardDummy.erase(m_bringCardDummy.begin()+i);
			}
		}		
		//m_bringCardDummy.pop_back();
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


