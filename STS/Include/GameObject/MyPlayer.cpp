#include "MyPlayer.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/Text.h"
#include "../GameObject/FloatingDamage.h"
//idle 애니메이션
//공격애니메이션: 살짝 앞으로 갔다가 뒤로 슬슬 빠짐
//수비 애니메이션: 히트박스 레이어가 뜨고 가운데 실드 애니메이션 실드 HUI 애니메이션

CMyPlayer::CMyPlayer()
{
	SetTypeID<CMyPlayer>();
}

CMyPlayer::CMyPlayer(const CMyPlayer& Obj) :
	CCharacter(Obj)
{
}

CMyPlayer::~CMyPlayer()
{
}

bool CMyPlayer::Init()
{
	CGameObject::Init();
	CCharacter::Init();
	
	
	SetMaxEnergy(5);
	m_Energy = 999;
	
	m_AttackDir = 1.f;
	m_AttackSpeed = 1500.f;

	SetMoveObject(true);
	m_MoveSpeed = 35.f;

	m_MaxHP = 80;
	m_HP = m_MaxHP;
	m_Shield = 0;

	SetPos(240.f, 470.f);
	m_OriginPos = GetPos();
	SetSize(270.f, 191.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Player", TEXT("Player/PlayerH.bmp"));
	SetColorKey(255, 0, 255);

		// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(1000, 230.f); //크기 세팅
	Box->SetOffset(380.f, -100.f); //위치세팅
	Box->SetCollisionProfile("MyPlayer");

	Box->SetCollisionBeginFunction<CMyPlayer>(this, &CMyPlayer::CollisionBegin);
	Box->SetCollisionEndFunction<CMyPlayer>(this, &CMyPlayer::CollisionEnd);
	m_Shield = 0;

	//m_HPBarFrame->SetPos(170.f, 180.f);
	//m_HPBar->SetPos(170.f, 180.f);
	//m_HPText->SetPos(220.f, 215.f);

	m_HPBarFrame->SetPos(35.f, 100.f);
	m_HPBar->SetPos(35.f, 100.f);
	m_HPText->SetPos(85.f, 137.f);
	m_ShieldImage->SetPos(-25, 98);
	m_ShieldText->SetPos(-11, 100);
	
	return true;
}

void CMyPlayer::Update(float DeltaTime)
{	
	CCharacter::Update(DeltaTime);
	//공격모션
	if (m_EnableAttack) 
	{
		m_Pos.x += m_AttackDir * m_AttackSpeed * DeltaTime;
		if (GetPos().x - m_OriginPos.x >= 150.f)
		{
			m_AttackDir = -1.f;
			m_AttackSpeed = 800.f;
		}
		if (m_Pos.x <= m_OriginPos.x) {
			SetPos(m_OriginPos);
			m_AttackDir = 1.f;
			m_AttackSpeed = 1500.f;
			m_EnableAttack = false;
		}
	}
	//데미지 모션
	if (m_EnableDamaged)
	{		
		m_Pos.x += m_AttackDir * (-1.f) * m_AttackSpeed * DeltaTime;
		if (m_OriginPos.x - GetPos().x >= 50.f)
		{
			m_AttackDir = -1.f;
			m_AttackSpeed = 800.f;
		}
		if (m_Pos.x >= m_OriginPos.x) {
			SetPos(m_OriginPos);
			m_AttackDir = 1.f;
			m_AttackSpeed = 1500.f;
			m_EnableDamaged = false;
		}
	}
}

void CMyPlayer::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMyPlayer::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CMyPlayer::InflictDamage(float Damage)
{
	Damage = CCharacter::InflictDamage(Damage);
	
	if (m_Shield > 0) {
		m_Shield -= (int)Damage;
		if (m_Shield < 0) {
			m_HP += (m_Shield);
			m_Shield = 0;
		}
	}
	else
	{
		m_HP -= (int)Damage;
	}
	
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
	
	//데미지 출력
	CFloatingDamage* Damages = m_Scene->CreateObject<CFloatingDamage>("Damages");
	Damages->SetPos(GetPos().x,GetPos().y-100.f);
	char ch[256] = {};
	sprintf_s(ch, "%d", (int)Damage);
	TCHAR t[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, ch, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ch, -1, t, Length);
	Damages->GetText()->GetWidget<CText>()->SetText(t);

	SetEnableDamaged(true);

	if (m_HP <= 0)
	{
		//사망
		SetEnable(false);
	}
	return Damage;
}



void CMyPlayer::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//AttackMotion(m_AttackDir, m_AttackSpeed);
	

}

void CMyPlayer::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
