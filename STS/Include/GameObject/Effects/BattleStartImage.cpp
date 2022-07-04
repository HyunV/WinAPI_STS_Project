#include "BattleStartImage.h"
#include "../CardManager.h"

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
		if (m_Time >= 2.f) {
			SetActive(false);
		}
	}

}
