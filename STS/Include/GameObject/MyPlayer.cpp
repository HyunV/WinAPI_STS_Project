#include "MyPlayer.h"
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

	SetPos(100.f, 400.f);
	SetSize(270.f, 191.f);
	SetPivot(0.f, 0.f);

	//SetTexture("Player", TEXT("Player/Player.bmp"));

	return true;
}

void CMyPlayer::Update(float DeltaTime)
{
}

void CMyPlayer::PostUpdate(float DeltaTime)
{
}

void CMyPlayer::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CMyPlayer::InflictDamage(float Damage)
{
	return 0.0f;
}

void CMyPlayer::Buff()
{
}

void CMyPlayer::Debuff()
{
}
