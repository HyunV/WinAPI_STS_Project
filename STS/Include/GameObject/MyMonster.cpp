#include "MyMonster.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/ImageWidget2.h"
#include "../GameObject/CardManager.h"
#include "../GameObject/FloatingDamage.h"


CMyMonster::CMyMonster()
{
	SetTypeID<CMyMonster>();
}

CMyMonster::CMyMonster(const CMyMonster& Obj)
{
}

CMyMonster::~CMyMonster()
{
}

bool CMyMonster::Init()
{
	CGameObject::Init();
	CCharacter::Init();

	m_MoveSpeed = 20;
	m_AttackSpeed = 200;
	SetMoveObject(true);
	SetPos(1000.f, 450.f);
	SetSize(180.f, 180.f);
	SetPivot(0.5f, 0.5f);

	m_OriginPos = GetPos();

	SetTexture("MyMonster", TEXT("Monster/enemy1.bmp"));
	SetColorKey(255, 0, 255);


	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(180.f, 180.f);
	Box->SetCollisionProfile("Monster");

	Box->SetMouseCollisionBeginFunction<CMyMonster>(this, &CMyMonster::CollisionMouseBegin);
	Box->SetMouseCollisionEndFunction<CMyMonster>(this, &CMyMonster::CollisionMouseEnd);
	Box->SetCollisionBeginFunction(this, &CMyMonster::CollisionBegin);
	Box->SetCollisionEndFunction(this, &CMyMonster::CollisionEnd);
	
	m_HP = 100;
	m_MaxHP = 100;
	m_Shield = 10;


	m_NameBar = CreateWidgetComponent<CText>("MonsterNameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("광신자"));
	m_NameBar->GetWidget<CText>()->SetEnable(false);
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetFont("NameFont");
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(0.f, 110.f);

	
	//Vector2 v = GetPos();
	
	Vector2 v = GetPos();
	//Damage->SetPos(v.x, v.y-50.f);
	


	return true;
}

void CMyMonster::Update(float DeltaTime)
{

	CGameObject::Update(DeltaTime);
	CCharacter::Update(DeltaTime);
	if (CCardManager::GetInst()->GetMonstersTurn())
	{
		AttackMotion(m_AttackDir, m_AttackSpeed);
		m_Cnt++;
		if (m_Cnt == 30) {
			m_AttackDir = 10;
		}
		if (m_Cnt > 30 && m_OriginPos.x < m_Pos.x)
		{
			//데미지
			m_Scene->GetPlayer()->InflictDamage(12);


			SetPos(m_OriginPos);
			m_Cnt = 0;
			m_AttackDir = -10;
			CCardManager::GetInst()->SetMonstersTurn(false);
		}
	}
}

void CMyMonster::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CMyMonster::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CMyMonster::InflictDamage(float Damage)
{
	Damage = CCharacter::InflictDamage(Damage);
	//int FinalDamege = (int)Damage - m_Shield;
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

	//데미지 출력
	CFloatingDamage* Damages = m_Scene->CreateObject<CFloatingDamage>("Damages");
	Damages->SetPos(GetPos().x, GetPos().y-100.f);
	char ch[256] = {};
	sprintf_s(ch, "%d", (int)Damage);
	TCHAR t[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, ch, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ch, -1, t, Length);
	Damages->GetText()->GetWidget<CText>()->SetText(t);
	
	//사망
	if (m_HP <= 0)
	{
		SetActive(false);
	}
	return Damage;
}

void CMyMonster::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
	m_NameBar->GetWidget<CText>()->SetEnable(true);
}

void CMyMonster::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	m_NameBar->GetWidget<CText>()->SetEnable(false);
}

void CMyMonster::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//MessageBox(nullptr, TEXT("확인."), TEXT("^모^"), MB_OK);
	
	
}

void CMyMonster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
}
