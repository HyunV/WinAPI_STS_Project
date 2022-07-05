#include "TurnEffect.h"
#include "../Widget/Text.h"
#include "../Widget/WidgetComponent.h"
#include "CardManager.h"

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
	
	m_WhosTurnText->GetWidget<CText>()->SetTextColor(227, 189, 77);
	m_WhosTurnText->SetPos(0, -50);

	m_TurnCountText = CreateWidgetComponent<CText>("TurnCountText");
	m_TurnCountText->GetWidget<CText>()->SetFont("CostFont");
	
	m_TurnCountText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_TurnCountText->SetPos(0, 20);

	return true;
}

void CTurnEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	int Turn = CCardManager::GetInst()->GetTurnCount();
	char Text[256] = {};
	sprintf_s(Text, "%d턴", Turn);
	TCHAR Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);

	switch (m_Turn)
	{
	case EWhos_Turn::None:
		break;
	case EWhos_Turn::Player:
		m_WhosTurnText->GetWidget<CText>()->SetText(TEXT("내 턴"));
		MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);
		m_TurnCountText->GetWidget<CText>()->SetText(Unicode);		
		
		m_Scene->GetPlayer()->SetEnergy(m_Scene->GetPlayer()->GetMaxEnergy());
		break;

	case EWhos_Turn::Monster:
		m_WhosTurnText->GetWidget<CText>()->SetText(TEXT("적 턴"));
		m_TurnCountText->GetWidget<CText>()->SetText(TEXT(""));
		//몬스터 클리어 쉴드
		break;

	}

	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 1.5f) {
			if (m_Turn == EWhos_Turn::Player) {
				CCardManager::GetInst()->SetPlayerTurn(true);
				CCardManager::GetInst()->DrawCard(CCardManager::GetInst()->GetDrawCard());
				CCardManager::GetInst()->SetMonstersTurn(false);

				//버프 정보 받아옴
				int *BuffArrTemp = m_Scene->GetPlayer()->GetBuffArr();

				if (!(BuffArrTemp[(int)Buff::Barrigate] > 0)) { //바리케이드 버프
					m_Scene->GetPlayer()->ClearShield();
				}
				if (BuffArrTemp[(int)Buff::DemonForm]) { //악마의 형상 버프
					BuffArrTemp[(int)Buff::Atk] += BuffArrTemp[(int)Buff::DemonForm];
				}
				
				//디버프 감소
				if (BuffArrTemp[(int)Buff::Vulnerable])
				{
					BuffArrTemp[(int)Buff::Vulnerable] -= 1;
				}
				if (BuffArrTemp[(int)Buff::Weak])
				{
					BuffArrTemp[(int)Buff::Weak] -= 1;
				}
			}
			if (m_Turn == EWhos_Turn::Monster) {
				CCardManager::GetInst()->SetMonstersTurn(true);
				CCardManager::GetInst()->SetPlayerTurn(false);
			}
			SetActive(false);
		}
	}
}

void CTurnEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CTurnEffect::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
