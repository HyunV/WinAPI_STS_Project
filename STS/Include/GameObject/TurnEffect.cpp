#include "TurnEffect.h"
#include "../Widget/Text.h"
#include "../Widget/WidgetComponent.h"

CTurnEffect::CTurnEffect()
{
	m_RenderLayer = ERender_Layer::Effect;
	m_WhosTurnText = nullptr;
	m_TurnCountText = nullptr;
	m_Turn = EWhos_Turn::None;
	m_Time = 0.f;
}

CTurnEffect::~CTurnEffect()
{
}

bool CTurnEffect::Init()
{
	CGameObject::Init();
	SetPos(640.f, 300.f);
	SetSize(1280.f, 100.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("TurnPanel", TEXT("BattlePanel.bmp"));

	m_WhosTurnText = CreateWidgetComponent<CText>("WhosTurnText");
	m_WhosTurnText->GetWidget<CText>()->SetFont("TurnMessageFont");
	m_WhosTurnText->GetWidget<CText>()->SetText(TEXT("Àû ÅÏ"));
	m_WhosTurnText->GetWidget<CText>()->SetTextColor(227, 189, 77);
	m_WhosTurnText->SetPos(0, -50);

	m_TurnCountText = CreateWidgetComponent<CText>("TurnCountText");
	m_TurnCountText->GetWidget<CText>()->SetFont("CostFont");
	m_TurnCountText->GetWidget<CText>()->SetText(TEXT("1ÅÏ"));
	m_TurnCountText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_TurnCountText->SetPos(0, 20);

	return true;
}

void CTurnEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTurnEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CTurnEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
