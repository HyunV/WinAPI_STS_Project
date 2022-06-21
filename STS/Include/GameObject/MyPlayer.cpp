#include "MyPlayer.h"
//idle �ִϸ��̼�
//���ݾִϸ��̼�: ��¦ ������ ���ٰ� �ڷ� ���� ����
//���� �ִϸ��̼�: ��Ʈ�ڽ� ���̾ �߰� ��� �ǵ� �ִϸ��̼� �ǵ� HUI �ִϸ��̼�

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
