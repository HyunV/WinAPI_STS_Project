#include "Defend.h"

CDefend::CDefend()
{
	m_EnableCollider = true;
}

CDefend::~CDefend()
{
}

bool CDefend::Init()
{
	CCard::Init();
	SetCardName("Defend");
	SetCardCost(1);
	SetCardType(Card_Type::Skill);
	SetCardValue(Card_Value::Rare);
	

	m_Scene->GetSceneResource()->LoadTexture("CardImage", TEXT("Cards/CardImage/defend.bmp"));

	SetCardInfo(m_cardType, m_cardValue, m_colorless, m_curse);
	SetCardAttribute(TEXT("수비"), m_cardType, m_cost); //이름, 카드 타입, 

	return true;
}

void CDefend::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);
}

void CDefend::Render(HDC hDC, float DeltaTime)
{
	CCard::Render(hDC, DeltaTime);
}

void CDefend::useCard()
{

}

void CDefend::SetAbility()
{
	int Shield = 5;
	sprintf_s(m_CardExplain, "방어도를 %d 얻습니다.", Shield);
	CCard::SetAbility();
}
