#include "BattleStartImage.h"
#include "../CardManager.h"
#include "../../Widget/WidgetComponent.h"
#include "../../Widget/Text.h"

CBattleStartImage::CBattleStartImage()
{
	m_RenderLayer = ERender_Layer::Hand;
	m_Time = 0.f;
}

CBattleStartImage::~CBattleStartImage()
{
}

bool CBattleStartImage::Init()
{
	SetPos(640.f, 300.f);
	SetPivot(0.5f, 0.5f);
	SetSize(230.f,200.f);
	SetTexture("BattleStartLogo", TEXT("Effects/test.bmp"));
	SetColorKey(255, 0, 255);
	CCardManager::GetInst()->SetPlayerTurn(true);
	
	CWidgetComponent* Wiz = CreateWidgetComponent<CText>("BattleStartText");
	Wiz->GetWidget<CText>()->SetText(TEXT("전투 시작"));
	Wiz->GetWidget<CText>()->SetFont("TurnMessageFont");
	Wiz->GetWidget<CText>()->EnableShadow(true);
	Wiz->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	Wiz->GetWidget<CText>()->SetTextColor(227, 190, 77);
	Wiz->SetPos(0, -50);


	
	return true;
}

void CBattleStartImage::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 1.f) {
			m_Pos.x += -1500.f * DeltaTime;
		}
		if (m_Time >= 1.5f) {
			SetActive(false);
			CCardManager::GetInst()->SetBringDeck();
			CCardManager::GetInst()->DrawCard(5);
			CCardManager::GetInst()->HandSort();
			m_Scene->GetPlayer()->SetEnergy(m_Scene->GetPlayer()->GetMaxEnergy());
			vector<CCard*> temp = CCardManager::GetInst()->GetHand();
		}
	}

}
