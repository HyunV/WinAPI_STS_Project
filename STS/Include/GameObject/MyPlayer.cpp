#include "MyPlayer.h"
#include "../Collision/ColliderBox.h"
//idle �ִϸ��̼�
//���ݾִϸ��̼�: ��¦ ������ ���ٰ� �ڷ� ���� ����
//���� �ִϸ��̼�: ��Ʈ�ڽ� ���̾ �߰� ��� �ǵ� �ִϸ��̼� �ǵ� HUI �ִϸ��̼�

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
	
	
	SetMoveObject(true);
	m_MoveSpeed = 12;

	m_AttackDir = 10;
	m_AttackSpeed = 200;

	m_MaxHP = 80;
	m_HP = m_MaxHP;
	m_Shield = 0;
	m_Atk = 3;
	cnt = 0;

	SetPos(140.f, 370.f);
	OriginPos = GetPos();
	SetSize(270.f, 191.f);
	SetPivot(0.f, 0.f);

	SetTexture("Player", TEXT("Player/PlayerH.bmp"));
	SetColorKey(255, 0, 255);

		// �浹ü �߰�
	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(1000, 300.f); //ũ�� ����
	Box->SetOffset(480.f, 1.f); //��ġ����
	Box->SetCollisionProfile("MyPlayer");

	Box->SetCollisionBeginFunction<CMyPlayer>(this, &CMyPlayer::CollisionBegin);
	Box->SetCollisionEndFunction<CMyPlayer>(this, &CMyPlayer::CollisionEnd);
	m_Shield = 0;

	m_HPBarFrame->SetPos(170.f, 180.f);
	m_HPBar->SetPos(170.f, 180.f);
	m_HPText->SetPos(220.f, 215.f);
	
	
	return true;
}

void CMyPlayer::Update(float DeltaTime)
{

	CGameObject::Update(DeltaTime);
	CCharacter::Update(DeltaTime);
	if (m_EnableAttack) {	
		AttackMotion(m_AttackDir, m_AttackSpeed);
		cnt++;
		if (cnt == 30) {
			m_AttackDir = -10;
		}
		if (cnt>30 && OriginPos.x > m_Pos.x)
		{
			SetPos(OriginPos);
			m_EnableAttack = false;
			cnt = 0;
			m_AttackDir = 10;
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
	return 0.0f;
}

float CMyPlayer::AddShield(float shield)
{
	//�÷��̾��� ���� �ø���.
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
	//AttackMotion(m_AttackDir, m_AttackSpeed);
	

}

void CMyPlayer::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
