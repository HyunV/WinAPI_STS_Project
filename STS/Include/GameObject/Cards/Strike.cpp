#include "Strike.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"


CStrike::CStrike()
{
}

CStrike::~CStrike()
{
}

bool CStrike::Init()
{
	// 타격
	CCard::Init();
	SetCardName("Strike");
	SetCardCost(1);
	SetCardType(Card_Type::Attack);
	SetCardValue(Card_Value::Common);
	m_EnableCollider = true;
	
	//카드 이미지
	m_Scene->GetSceneResource()->LoadTexture("CardImage", TEXT("Cards/CardImage/Strike.bmp"));
	m_cardImageSize = Vector2(246, 185);
	m_cardImageOffset = Vector2(22, 44);

	//SetCardInfo(m_cardType, m_cardValue, m_colorless, m_curse);
	SetCardAttribute(TEXT("타격"), m_cardType, m_cost); //이름, 카드 타입, 

	return true;
}

void CStrike::Update(float DeltaTime)
{
	CCard::Update(DeltaTime);
}

void CStrike::Render(HDC hDC, float DeltaTime)
{
	CCard::Render(hDC, DeltaTime);
}

void CStrike::useCard()
{
	//strike ~~
	//카드 구현부
}

void CStrike::SetAbility()
{
	int Attack = 3;
	sprintf_s(m_CardExplain, "피해를 %d 줍니다.", Attack);
	CCard::SetAbility();
}

