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
	
}

CCardManager::~CCardManager()
{
	
}
void CCardManager::UseCard()
{
	//���ͷ����� ������ ����ī�� Ȯ��
	//�� ī�带 �ڵ忡�� �����ϰ� ���� ī��� �̵��Ѵ�.
	
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
	CGiveAttribute* DefaultDamage = m_Scene->CreateCard<CGiveAttribute>("DefaultDamage");
	DefaultDamage->SetType(Card_Attribute::Damage, 6);
	CGiveAttribute* DefaultShield = m_Scene->CreateCard<CGiveAttribute>("DefaultShield");
	DefaultShield->SetType(Card_Attribute::Shield, 5);

	CCard* Strike1 = m_Scene->CreateCard<CCard>("Strike1");
	Strike1->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike1->SetCardAttribute(TEXT("Ÿ��"), Card_Type::Attack, 1);
	Strike1->AddAbility(DefaultDamage);

	CCard* Strike2 = m_Scene->CreateCard<CCard>("Strike2");
	Strike2->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike2->SetCardAttribute(TEXT("Ÿ��"), Card_Type::Attack, 1);
	Strike2->AddAbility(DefaultDamage);

	CCard* Strike3 = m_Scene->CreateCard<CCard>("Strike3");
	Strike3->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike3->SetCardAttribute(TEXT("Ÿ��"), Card_Type::Attack, 1);
	Strike3->AddAbility(DefaultDamage);

	CCard* Strike4 = m_Scene->CreateCard<CCard>("Strike4");
	Strike4->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike4->SetCardAttribute(TEXT("Ÿ��"), Card_Type::Attack, 1);
	Strike4->AddAbility(DefaultDamage);

	CCard* Strike5 = m_Scene->CreateCard<CCard>("Strike5");
	Strike5->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike5->SetCardAttribute(TEXT("Ÿ��"), Card_Type::Attack, 1);
	Strike5->AddAbility(DefaultDamage);

	//����
	CCard* Defend1 = m_Scene->CreateCard<CCard>("Defend1");
	Defend1->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend1->SetCardAttribute(TEXT("����"), Card_Type::Skill, 1);
	Defend1->AddAbility(DefaultShield);

	CCard* Defend2 = m_Scene->CreateCard<CCard>("Defend2");
	Defend2->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend2->SetCardAttribute(TEXT("����"), Card_Type::Skill, 1);
	Defend2->AddAbility(DefaultShield);

	CCard* Defend3 = m_Scene->CreateCard<CCard>("Defend3");
	Defend3->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend3->SetCardAttribute(TEXT("����"), Card_Type::Skill, 1);
	Defend3->AddAbility(DefaultShield);

	CCard* Defend4 = m_Scene->CreateCard<CCard>("Defend4");
	Defend4->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend4->SetCardAttribute(TEXT("����"), Card_Type::Skill, 1);
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
		//���� ī�� 
		if (m_Hand.size() > 10)
			break;

		if (m_bringCardDummy.size() == 0) {
			//
			m_bringCardDummy = m_mainDeck;
		}
			//�����ִ� �ڵ�

		m_Hand.push_back(m_bringCardDummy.back());
		
		m_bringCardDummy.pop_back();
	}
}

void CCardManager::AddDiscard(CGameObject* Discard)
{
	m_disCardDummy.push_back((CCard*)Discard);
}

void CCardManager::BattleStart()
{
	m_bringCardDummy = m_mainDeck; //���� �� ������ ī��� �����´�
	//������ �� �� ���´�.
	//ī�带 n�� �̴´�
	//�ڵ忡 n���� �����´�.
}


