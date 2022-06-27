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

	m_HPBarFrame = CreateWidgetComponent<CProgressBar>("HPBarFrame");
	m_HPBarFrame->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Back,
		"HPFrame", TEXT("HPBar/BarPanel.bmp"));

	m_HPBarFrame->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Default, Vector2(0, 0), Vector2(130, 12));
	m_HPBarFrame->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Shield, Vector2(130, 0), Vector2(260, 12));
	m_HPBarFrame->GetWidget<CProgressBar>()->SetColorKey(EProgressBar_Texture_Type::Back, 255, 0, 255);
	m_HPBarFrame->GetWidget<CProgressBar>()->SetSize(130.f, 12.f);
	m_HPBarFrame->SetPos(0.f, 100.f);


	m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");
	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar, 
		"HPBar", TEXT("HPBar/BarHP.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Default, Vector2(0, 0), Vector2(126, 12));
	m_HPBar->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Shield, Vector2(126, 0), Vector2(252, 12));

	m_HPBar->GetWidget<CProgressBar>()->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);
	m_HPBar->GetWidget<CProgressBar>()->SetSize(126.f, 12.f);
	m_HPBar->SetPos(0.f, 100.f);


	m_HPText = CreateWidgetComponent<CText>("HPText");
	m_HPText->GetWidget<CText>()->SetText(TEXT("Á×À½"));
	m_HPText->GetWidget<CText>()->EnableShadow(true);
	m_HPText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_HPText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_HPText->GetWidget<CText>()->SetFont("UI");
	m_HPText->SetPos(50.f, 137.f);
	m_HPText->GetWidget<CText>()->SetSize(100, 100);

	m_NameBar = CreateWidgetComponent<CText>("MonsterNameBar");

	m_NameBar->GetWidget<CText>()->SetText(TEXT("±¤½ÅÀÚ"));
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetFont("NameFont");
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(0.f, 110.f);


	return true;
}

void CMyMonster::Update(float DeltaTime)
{
 
	if (m_Shield) {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
	}
	else {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
	}
	CGameObject::Update(DeltaTime);



	char Text[256] = {};
	sprintf_s(Text, "%d/%d", m_HP, m_MaxHP);

	TCHAR Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);
	m_HPText->GetWidget<CText>()->SetText(Unicode);
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
	m_Shield++;
}

void CMyMonster::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	m_Shield--;
}

void CMyMonster::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//MessageBox(nullptr, TEXT("È®ÀÎ."), TEXT("^¸ð^"), MB_OK);
	
	
}

void CMyMonster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
}
