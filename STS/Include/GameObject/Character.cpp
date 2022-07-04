#include "Character.h"

#include "../GameManager.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/ImageWidget2.h"

CCharacter::CCharacter() :
	m_AttackDir(0),
	m_AttackSpeed(0),
	m_Cnt(0)

{
	SetTypeID<CCharacter>();
	
}

CCharacter::CCharacter(const CCharacter& Obj) :
	CGameObject(Obj),
	m_AttackDir(0),
	m_AttackSpeed(0),
	m_Cnt(0)

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

	m_HPBarFrame->SetPos(0.f, 100.f);
	m_HPBar->SetPos(0.f, 100.f);
	m_HPText->SetPos(50.f, 137.f);

	m_ShieldImage = CreateWidgetComponent<CImageWidget2>("ShieldImage");
	m_ShieldImage->GetWidget<CImageWidget2>()->SetTexture("AddShield", TEXT("Effects/block.bmp"));
	m_ShieldImage->GetWidget<CImageWidget2>()->SetSize(32, 32);
	m_ShieldImage->SetPos(-60, 98);
	m_ShieldImage->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_ShieldImage->GetWidget<CImageWidget2>()->SetEnable(false);

	m_ShieldText = CreateWidgetComponent<CText>("ShieldText");
	m_ShieldText->GetWidget<CText>()->SetText(TEXT("5"));
	m_ShieldText->GetWidget<CText>()->EnableShadow(true);
	m_ShieldText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_ShieldText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_ShieldText->GetWidget<CText>()->SetFont("Shield");
	m_ShieldText->GetWidget<CText>()->SetSize(32, 32);
	m_ShieldText->SetPos(-46, 100);
	m_ShieldText->GetWidget<CImageWidget2>()->SetEnable(false);


	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	//if (m_AttackOn) {
	//	AttackMotion(m_AttackDir, m_AttackSpeed);
	//	m_AttackOn = false;
	//}
		if (m_Shield > 0) {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
		m_ShieldImage->GetWidget<CImageWidget2>()->SetEnable(true);
		m_ShieldText->GetWidget<CImageWidget2>()->SetEnable(true);
		char Text2[256] = {};
		sprintf_s(Text2, "%d", m_Shield);

		TCHAR Unicode2[256] = {};
		int Length2 = MultiByteToWideChar(CP_ACP, 0, Text2, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Text2, -1, Unicode2, Length2);
		m_ShieldText->GetWidget<CText>()->SetText(Unicode2);
	}
	else {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
		m_ShieldImage->GetWidget<CImageWidget2>()->SetEnable(false);
		m_ShieldText->GetWidget<CImageWidget2>()->SetEnable(false);
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
