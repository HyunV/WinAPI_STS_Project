#include "CPlayerHitEffect.h"

CPlayerHitEffect::CPlayerHitEffect()
{
	m_RenderLayer = ERender_Layer::Effect;
	m_Time = 0.f;
}

CPlayerHitEffect::~CPlayerHitEffect()
{
}

bool CPlayerHitEffect::Init()
{
	//ÇÇ°Ý
	SetPos(240, 470);
	SetPivot(0.5f, 0.5f);
	SetSize(96.f, 96.f);
	SetTexture("HitEffect", TEXT("Effects/Hit.bmp"));
	SetColorKey(255, 0, 255);
	return true;
}

void CPlayerHitEffect::Update(float DeltaTime)
{
	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 0.5f)
		{
			SetActive(false);
		}
	}
}
