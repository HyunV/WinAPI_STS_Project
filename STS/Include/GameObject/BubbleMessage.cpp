#include "BubbleMessage.h"
#include "../Widget/Text.h"
#include "../Widget/WidgetComponent.h"

CBubbleMessage::CBubbleMessage()
{
	m_Time = 0.f;
	m_Type = EMessageBox_Type::Default;
	m_Message = nullptr;
}

CBubbleMessage::~CBubbleMessage()
{
}

bool CBubbleMessage::Init()
{
	SetPos(400, 330);
	SetSize(256, 256);
	SetPivot(0.5f, 0.5f);
	SetColorKey(255, 0, 255);

	m_Message = CreateWidgetComponent<CText>("Messagess");
	m_Message->GetWidget<CText>()->SetFont("NameFont");
	m_Message->GetWidget<CText>()->SetText(TEXT(""));
	m_Message->GetWidget<CText>()->SetTextColor(64, 64, 64);
	m_Message->SetPos(0, -10);
	//m_Message->GetWidget<CText>()->SetSize(10, 100);
	
	return true;
}

void CBubbleMessage::Update(float DeltaTime)
{
	switch (m_Type)
	{
	case EMessageBox_Type::Default:
		SetTexture("Text2", TEXT("speechBubble2.bmp"));
		SetColorKey(255, 0, 255);
		break;
	case EMessageBox_Type::Shop:
		SetTexture("Text3", TEXT("speechBubble3.bmp"));
		SetColorKey(255, 0, 255);
		//SetPos(0, 0);
		break;
	case EMessageBox_Type::Monster:
		SetTexture("Text3", TEXT("speechBubble1.bmp"));
		SetColorKey(255, 0, 255);
		break;
	}

	CGameObject::Update(DeltaTime);

	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 2.5f) {
			m_Time = 0.f;
			SetActive(false);
		}
	}
}

void CBubbleMessage::PostUpdate(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBubbleMessage::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
