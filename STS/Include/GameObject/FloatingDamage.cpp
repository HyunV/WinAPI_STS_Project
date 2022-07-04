#include "FloatingDamage.h"
#include "../Widget/Text.h"
#include "../Widget/WidgetComponent.h"

CFloatingDamage::CFloatingDamage()
{
	m_Damage = nullptr;
	m_Time = 0.f;
	m_Count = 0;
}

CFloatingDamage::~CFloatingDamage()
{
}

bool CFloatingDamage::Init()
{
	SetPivot(0.5f, 0.5f);
	SetSize(100.f, 100.f);
	m_MoveSpeed = 1500;
	m_MoveDamage = (-1.f, -1.f);
	m_Damage = CreateWidgetComponent<CText>("DamageText");
	m_Damage->GetWidget<CText>()->SetFont("DamageFont");
	//m_Damage->GetWidget<CText>()->SetText(TEXT(""));
	m_Damage->GetWidget<CText>()->SetTextColor(255, 255, 255);
	
	//m_Damage->SetPos(1000, 450);
	//m_Damage->GetWidget<CText>()->SetSize(10, 100);
	return true;
}

void CFloatingDamage::Update(float DeltaTime)
{	
	CGameObject::Update(DeltaTime);
	MoveDir(m_MoveDamage);
	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 0.1f) {			
			m_MoveDamage = (0.f, 0.f);
			MoveDir(m_MoveDamage);
			m_Pos.y += 900 * DeltaTime;
		}
		if (m_Time >= 1.f) {
			SetActive(false);
		}
	}
}

void CFloatingDamage::PostUpdate(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CFloatingDamage::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
