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
	SetCardName("Å¸°Ý");
	SetCardCost(1);
	SetCardType(Card_Type::Attack);
	SetCardValue(Card_Value::Common);
	
	//m_cardPanel = CreateWidget<CImageWidget2>("dd");
	
	SetPos(300.f, 800.f);
	SetSize(250.f, 318.f);
	SetPivot(0.5f, 0.5f);

	return true;
}

void CStrike::Update(float DeltaTime)
{

}

void CStrike::Render(HDC hDC, float DeltaTime)
{
	CCard::Render(hDC, DeltaTime);

}

void CStrike::useCard()
{
	//strike ~~

}
