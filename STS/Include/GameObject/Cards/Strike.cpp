#include "Strike.h"
#include "../../Widget/Text.h"
#include "../../Widget/ImageWidget2.h"
CStrike::CStrike()
{
}

CStrike::~CStrike()
{
}

bool CStrike::Init()
{
	CCard::Init();
	SetCardName("Å¸°Ý");
	SetCardCost(1);
	SetCardType(Card_Type::Attack);
	SetCardValue(Card_Value::Common);
	
	//m_cardPanel = CreateWidget<CImageWidget2>("dd");
	
	//SetSize(295.f, 415.f);
	//SetPivot(0.5f, 0.5f);

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

}
