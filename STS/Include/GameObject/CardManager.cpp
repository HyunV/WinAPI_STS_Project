#include "CardManager.h"
#include "Card.h"
#include "Cards/CardAbility.h"
#include "Cards/GiveAttribute.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneResource.h"
#include "GameObject.h"
#include "BubbleMessage.h"
#include <time.h>

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
	srand((unsigned int)time(0));
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
		deck[i]->SetPos(-1000.f, 0.f);
		//deck[i]->SetEnable(false);
	}
	HandSort();
}
void CCardManager::HandToDiscard()
{
	if (!m_Hand.size() == 0) {
		EnableHand(false);
	}
	//역순으로 버리게 
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
int CCardManager::Rand(int n)
{
	return rand()%n;
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
	//카드 능력치 세팅

	//공격 
	CGiveAttribute* StrikeDamage = m_Scene->CreateObject<CGiveAttribute>("StrikeDamage");
	StrikeDamage->SetType(Card_Attribute::Damage, 6);

	//강타딜
	CGiveAttribute* BashDamage = m_Scene->CreateObject<CGiveAttribute>("BashDamage");
	BashDamage->SetType(Card_Attribute::Damage, 8);
	
	CGiveAttribute* HyperDamage = m_Scene->CreateObject<CGiveAttribute>("HyperDamage");
	HyperDamage->SetType(Card_Attribute::Damage, 99999);

	//수비
	CGiveAttribute* Shield5 = m_Scene->CreateObject<CGiveAttribute>("Shield");
	Shield5->SetType(Card_Attribute::Shield, 5);
	
	//드로우카드
	CGiveAttribute* DrawCard1 = m_Scene->CreateObject<CGiveAttribute>("DrawCard1");
	DrawCard1->SetType(Card_Attribute::DrawCard, 1);

	//소멸
	CGiveAttribute* Exhaust = m_Scene->CreateObject<CGiveAttribute>("Exhaust");
	Exhaust->SetType(Card_Attribute::Exhaust, 0);

	//취약
	CGiveAttribute* Vulnerable2 = m_Scene->CreateObject<CGiveAttribute>("Vulnerable");
	Vulnerable2->SetType(Card_Attribute::Vulnerable, 2);

	//약화
	CGiveAttribute* Weak2 = m_Scene->CreateObject<CGiveAttribute>("Vulnerable");
	Weak2->SetType(Card_Attribute::Weak, 2);

	//공격력
	CGiveAttribute* Inflame2 = m_Scene->CreateObject<CGiveAttribute>("Inflame2");
	Inflame2->SetType(Card_Attribute::Inflame, 2);

	CGiveAttribute* Inflame3 = m_Scene->CreateObject<CGiveAttribute>("Inflame3");
	Inflame3->SetType(Card_Attribute::Inflame, 3);

	//민첩함
	CGiveAttribute* FootWork2 = m_Scene->CreateObject<CGiveAttribute>("FootWork2");
	FootWork2->SetType(Card_Attribute::FootWork, 2);

	//바리케이드
	CGiveAttribute* BarricadeAtt = m_Scene->CreateObject<CGiveAttribute>("BarricadeAtt");
	BarricadeAtt->SetType(Card_Attribute::Barricade, 1);

	//한계돌파
	CGiveAttribute* LimitBreakAtt = m_Scene->CreateObject<CGiveAttribute>("LimitBreakAtt");
	LimitBreakAtt->SetType(Card_Attribute::LimitBreak, 0);
	
	//악마의형상
	CGiveAttribute* DemonAtt = m_Scene->CreateObject<CGiveAttribute>("DemonAtt");
	DemonAtt->SetType(Card_Attribute::DemonForm, 3);

	//몸통박치기
	CGiveAttribute* BodySlamAtt = m_Scene->CreateObject<CGiveAttribute>("BodySlamAtt");
	BodySlamAtt->SetType(Card_Attribute::BodySlam, 0);

	//참호
	CGiveAttribute* EntrenchAtt = m_Scene->CreateObject<CGiveAttribute>("EntrenchAtt");
	EntrenchAtt->SetType(Card_Attribute::Entrench, 0);

	//내 턴 시작 시
	CGiveAttribute* Text1 = m_Scene->CreateObject<CGiveAttribute>("Text1");
	Text1->SetType(Card_Attribute::Text1, 0);


	//##############################################메인덱 카드 세팅###################################################################################
	CCard* Strike1 = m_Scene->CreateObject<CCard>("Strike1");
	Strike1->SetCardInfo("strike", Card_Type::Attack, Card_Value::Special, false, false);
	Strike1->SetCardAttribute(TEXT("테스트타격"), Card_Type::Attack, 1);
	Strike1->AddAbility(StrikeDamage);

	CCard* Strike2 = m_Scene->CreateObject<CCard>("Strike2");
	Strike2->SetCardInfo("strike", Card_Type::Attack, Card_Value::Rare, false, false);
	Strike2->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike2->AddAbility(StrikeDamage);

	CCard* Strike3 = m_Scene->CreateObject<CCard>("Strike3");
	Strike3->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike3->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike3->AddAbility(StrikeDamage);

	CCard* Strike4 = m_Scene->CreateObject<CCard>("Strike4");
	Strike4->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike4->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike4->AddAbility(StrikeDamage);

	CCard* Strike5 = m_Scene->CreateObject<CCard>("Strike5");
	Strike5->SetCardInfo("strike", Card_Type::Attack, Card_Value::Rare, true, true);
	Strike5->SetCardAttribute(TEXT("전설의 타격"), Card_Type::Attack, 0);
	Strike5->AddAbility(HyperDamage);


	//수비
	CCard* Defend1 = m_Scene->CreateObject<CCard>("Defend1");
	Defend1->SetCardInfo("shield", Card_Type::Power, Card_Value::Common, false, false);
	Defend1->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend1->AddAbility(Shield5);

	CCard* Defend2 = m_Scene->CreateObject<CCard>("Defend2");
	Defend2->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend2->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend2->AddAbility(Shield5);

	CCard* Defend3 = m_Scene->CreateObject<CCard>("Defend3");
	Defend3->SetCardInfo("shield", Card_Type::Skill, Card_Value::Rare, false, false);
	Defend3->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend3->AddAbility(Shield5);

	CCard* Defend4 = m_Scene->CreateObject<CCard>("Defend4");
	Defend4->SetCardInfo("shield", Card_Type::Skill, Card_Value::Special, true, false);
	Defend4->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend4->AddAbility(Shield5);

	//강타
	CCard* Bash = m_Scene->CreateObject<CCard>("Bash");
	Bash->SetCardInfo("Bash", Card_Type::Attack, Card_Value::Common, false, false);
	Bash->SetCardAttribute(TEXT("강타"), Card_Type::Attack, 2);
	Bash->AddAbility(BashDamage);
	Bash->AddAbility(Vulnerable2);

	//발화
	CCard* Inflame = m_Scene->CreateObject<CCard>("Inflame");
	Inflame->SetCardInfo("Inflame", Card_Type::Power, Card_Value::Special, false, false);
	Inflame->SetCardAttribute(TEXT("발화"), Card_Type::Power, 2);
	Inflame->AddAbility(Inflame2);
	
	//바리케이드
	CCard* Barricade = m_Scene->CreateObject<CCard>("Barricade");
	Barricade->SetCardInfo("Barricade", Card_Type::Power, Card_Value::Rare, false, false);
	Barricade->SetCardAttribute(TEXT("바리케이드"), Card_Type::Power, 3);
	Barricade->AddAbility(Text1);
	Barricade->AddAbility(BarricadeAtt);

	//한계돌파
	CCard* LimitBreak = m_Scene->CreateObject<CCard>("LimitBreak");
	LimitBreak->SetCardInfo("LimitBreak", Card_Type::Skill, Card_Value::Rare, false, false);
	LimitBreak->SetCardAttribute(TEXT("한계돌파"), Card_Type::Skill, 1);	
	LimitBreak->AddAbility(LimitBreakAtt);
	LimitBreak->AddAbility(Exhaust);

	//악마의형상
	CCard* DemonForm = m_Scene->CreateObject<CCard>("DemonForm");
	DemonForm->SetCardInfo("DemonForm", Card_Type::Power, Card_Value::Rare, false, false);
	DemonForm->SetCardAttribute(TEXT("악마의 형상"), Card_Type::Power, 3);
	DemonForm->AddAbility(DemonAtt);

	//몸통박치기
	CCard* BodySlam = m_Scene->CreateObject<CCard>("BodySlam");
	BodySlam->SetCardInfo("BodySlam", Card_Type::Attack, Card_Value::Common, false, false);
	BodySlam->SetCardAttribute(TEXT("몸통박치기"), Card_Type::Attack, 0);
	BodySlam->AddAbility(BodySlamAtt);
	
	//참호
	CCard* Entrench = m_Scene->CreateObject<CCard>("Entrench");
	Entrench->SetCardInfo("Entrench", Card_Type::Skill, Card_Value::Special, false, false);
	Entrench->SetCardAttribute(TEXT("참호"), Card_Type::Skill, 1);
	Entrench->AddAbility(EntrenchAtt);
	//발놀림
	CCard* FootWork = m_Scene->CreateObject<CCard>("FootWork");
	FootWork->SetCardInfo("FootWork", Card_Type::Power, Card_Value::Special, false, false);
	FootWork->SetCardAttribute(TEXT("발놀림"), Card_Type::Power, 1);
	FootWork->AddAbility(FootWork2);


	//만든 카드 삽입
	//m_mainDeck.push_back(Strike1);
	//m_mainDeck.push_back(Strike2);
	//m_mainDeck.push_back(Strike3);
	//m_mainDeck.push_back(Strike4);
	//m_mainDeck.push_back(Strike5);

	//m_mainDeck.push_back(Defend1);
	//m_mainDeck.push_back(Defend2);
	//m_mainDeck.push_back(Defend3);
	m_mainDeck.push_back(Defend4);
	m_mainDeck.push_back(Bash);
	//테스트 추가
	
	m_mainDeck.push_back(Barricade);
	m_mainDeck.push_back(LimitBreak);
	m_mainDeck.push_back(DemonForm);
	m_mainDeck.push_back(BodySlam);
	m_mainDeck.push_back(Entrench);
	m_mainDeck.push_back(FootWork);
}

void CCardManager::SetBringDeck()
{
	m_bringCardDummy = GetMainDeck();
}

void CCardManager::DrawCard(int value)
{
	HandSort();
	for (int i = 0; i < value; i++) {
		
		//핸드가 10장 이상일 때
		if (m_Hand.size() >= 10) {
			CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("Messages");
			Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("손이 가득 찼다."));
			return;
		}
	
		//뽑을카드가 없을 때
		if (m_bringCardDummy.size() == 0) { 
			if (m_disCardDummy.size() == 0) {
				CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("Messages");
				Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("가져올 카드가 없다."));
				HandSort();
				return;
			}
			m_bringCardDummy = m_disCardDummy;
			m_disCardDummy.clear();
		}
		
		//섞어주는 코드(수정)
		vector<CCard*> Temp = m_bringCardDummy;
		std::random_shuffle(Temp.begin(), Temp.end());

		if (!m_Hand.size() == 0) {
			Vector2(m_Hand.back()->GetPos());
		}
		m_Hand.push_back(Temp.back());
		for (int i = 0; i < m_bringCardDummy.size(); i++)
		{
			if (m_bringCardDummy[i] == Temp.back())
			{
				m_bringCardDummy.erase(m_bringCardDummy.begin()+i);
			}
		}
		//m_Hand.back()->SetIsAnimated(true);
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


