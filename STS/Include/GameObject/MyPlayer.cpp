#include "MyPlayer.h"
#include "../Collision/ColliderBox.h"
//idle 애니메이션
//공격애니메이션: 살짝 앞으로 갔다가 뒤로 슬슬 빠짐
//수비 애니메이션: 히트박스 레이어가 뜨고 가운데 실드 애니메이션 실드 HUI 애니메이션

CMyPlayer::CMyPlayer()
{
	SetTypeID<CMyPlayer>();
}

CMyPlayer::CMyPlayer(const CMyPlayer& Obj)	:
	CCharacter(Obj)
{
}

CMyPlayer::~CMyPlayer()
{
}

bool CMyPlayer::Init()
{
	CGameObject::Init();
	m_HPMax = 80;
	m_HP = m_HPMax;
	
	m_Atk = 3;

	SetPos(100.f, 400.f);
	SetSize(270.f, 161.f);
	//SetSize(148.f, 208.f);
	SetPivot(0.f, 0.f);

	SetTexture("Player", TEXT("Player/PlayerH.bmp"));
	SetColorKey(255, 0, 255);
	//SetTexture("Player", TEXT("card.bmp"));

		// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(270, 191.f); //크기 세팅
	//Box->SetOffset(1.f, 1.f); //위치세팅
	Box->SetCollisionProfile("MyPlayer");

	Box->SetCollisionBeginFunction<CMyPlayer>(this, &CMyPlayer::CollisionBegin);
	Box->SetCollisionEndFunction<CMyPlayer>(this, &CMyPlayer::CollisionEnd);



	return true;
}

void CMyPlayer::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
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
	return 0.0f;
}

float CMyPlayer::AddShield(float shield)
{
	//플레이어의 방어도를 올린다.
	return 0.0f;
}

void CMyPlayer::Buff()
{
	//
}

void CMyPlayer::Debuff()
{
}

void CMyPlayer::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CMyPlayer::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
