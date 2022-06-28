#include "Character.h"

#include "../GameManager.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"

CCharacter::CCharacter()
{
	SetTypeID<CCharacter>();
}

CCharacter::CCharacter(const CCharacter& Obj) :
	CGameObject(Obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	m_Shield = 0;
	float m_AttackDir = 50;
	float m_AttackSpeed = 1000;

	m_HPBarFrame = CreateWidgetComponent<CProgressBar>("HPBarFrame");
	m_HPBarFrame->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Back,
		"HPFrame", TEXT("HPBar/BarPanel.bmp"));
	m_HPBarFrame->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Default, Vector2(0, 0), Vector2(130, 12));
	m_HPBarFrame->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Shield, Vector2(130, 0), Vector2(260, 12));
	m_HPBarFrame->GetWidget<CProgressBar>()->SetColorKey(EProgressBar_Texture_Type::Back, 255, 0, 255);
	m_HPBarFrame->GetWidget<CProgressBar>()->SetSize(130.f, 12.f);

	m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");
	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar,
		"HPBar", TEXT("HPBar/BarHP.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Default, Vector2(0, 0), Vector2(126, 12));
	m_HPBar->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Shield, Vector2(126, 0), Vector2(252, 12));
	m_HPBar->GetWidget<CProgressBar>()->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);
	m_HPBar->GetWidget<CProgressBar>()->SetSize(126.f, 12.f);


	m_HPText = CreateWidgetComponent<CText>("HPText");
	m_HPText->GetWidget<CText>()->SetText(TEXT("Á×À½"));
	m_HPText->GetWidget<CText>()->EnableShadow(true);
	m_HPText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_HPText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_HPText->GetWidget<CText>()->SetFont("UI");
	m_HPText->GetWidget<CText>()->SetSize(100, 100);

	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	//if (m_AttackOn) {
	//	AttackMotion(m_AttackDir, m_AttackSpeed);
	//	m_AttackOn = false;
	//}
		if (m_Shield) {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
	}
	else {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
	}

	char Text[256] = {};
	sprintf_s(Text, "%d/%d", m_HP, m_MaxHP);

	TCHAR Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);
	m_HPText->GetWidget<CText>()->SetText(Unicode);
}

void CCharacter::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CCharacter::AttackMotion(float Dir, float Speed)
{	
	m_Pos.x += Dir * Speed * DELTA_TIME * m_TimeScale;
}
