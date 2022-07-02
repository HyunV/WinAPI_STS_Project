#include "MyMonster.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"


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
	SetMoveObject(true);
	SetPos(1000.f, 450.f);
	SetSize(180.f, 180.f);
	SetPivot(0.5f, 0.5f);

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
	m_Shield = 0;

	m_HPBarFrame->SetPos(0.f, 100.f);
	m_HPBar->SetPos(0.f, 100.f);
	m_HPText->SetPos(50.f, 137.f);

	m_NameBar = CreateWidgetComponent<CText>("MonsterNameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("광신자"));
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetFont("NameFont");
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(0.f, 110.f);

	return true;
}

void CMyMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	CCharacter::Update(DeltaTime);
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
	
	m_HP -= (int)Damage;

	if (m_HP <= 0)
	{
		SetActive(false);
	}
	return Damage;
}

void CMyMonster::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
	
}

void CMyMonster::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	
}

void CMyMonster::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//MessageBox(nullptr, TEXT("확인."), TEXT("^모^"), MB_OK);
	
	
}

void CMyMonster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
}
