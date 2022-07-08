#include "ShieldEffect.h"

CShieldEffect::CShieldEffect()
{
	m_RenderLayer = ERender_Layer::Effect;
	m_Time = 0.f;
}

CShieldEffect::~CShieldEffect()
{
}

bool CShieldEffect::Init()
{
	SetPos(240, 270); //¿øº» Æ÷½º¿¡¼­ 200 »©ÁÜ
	SetPivot(0.f, 0.f);
	SetSize(72.f, 72.f);
	SetTexture("ShieldEffect", TEXT("Effects/Shield.bmp"));
	SetColorKey(255, 0, 255);
	return true;
}

void CShieldEffect::Update(float DeltaTime)
{
	//
	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 0.1f) {
			if (m_OriginPos.y+150.f > m_Pos.y)
			{				
				m_Pos.y += 800.f * DeltaTime;
			}						
		}
		if (m_Time >= 0.5f)
		{
			SetActive(false);
		}
	}
}
