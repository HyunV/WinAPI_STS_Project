#include "MyPlayer.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/Text.h"
#include "../GameObject/FloatingDamage.h"
#include "../GameObject/Effect.h"
#include "../GameObject/Effects/GameOver.h"
//idle �ִϸ��̼�
//���ݾִϸ��̼�: ��¦ ������ ���ٰ� �ڷ� ���� ����
//���� �ִϸ��̼�: ��Ʈ�ڽ� ���̾ �߰� ��� �ǵ� �ִϸ��̼� �ǵ� HUI �ִϸ��̼�

CMyPlayer::CMyPlayer()
{
	SetTypeID<CMyPlayer>();
	m_AttackCard = 0;
	m_AttackDir = 0;
	m_AttackSpeed = 0;

	//m_BuffFirstPos = (-60.f, 120.f); //�÷��̾� ������
	//m_TextOffSet = (15.f, 13.f);
}

CMyPlayer::~CMyPlayer()
{
}

bool CMyPlayer::Init()
{
	m_BuffArr[0] = 999; //���ݷ�
	//m_BuffArr[1] = 0; //��ø��
	//m_BuffArr[2] = 0; //�Ǹ������� //�Ͻ��� �� ���ݷ� +n
	//m_BuffArr[3] = 0; //�ٸ����̵� //���Ȼ����
	//m_BuffArr[4] = 0; //�ݳ�
	//m_BuffArr[5] = 0; //�ǽ� �� ���۽� ���ݷ� + n
	//m_BuffArr[6] = 0; //��� 50%�߰� ���� *1.5 //�� ���� �� 
	//m_BuffArr[7] = 0; //��ȭ 25% ���� ������ *0.75

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

	m_HP = 999;

	m_Shield = 0;

	SetPos(240.f, 470.f);
	m_OriginPos = GetPos();
	SetSize(270.f, 191.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Player", TEXT("Player/PlayerH.bmp"));
	SetColorKey(255, 0, 255);

		// �浹ü �߰�
	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(1000, 230.f); //ũ�� ����
	Box->SetOffset(380.f, -100.f); //��ġ����
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
	m_BuffFirstPos = (0.f, -20.f);
	m_TextOffSet = (0.f, 13.f);
	CCharacter::Update(DeltaTime);
	//���ݸ��
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
	//������ ���
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
	
	//## �ڵ� ����####################################################################
	//int AtkBonus = m_Scene->GetMonster()->GetBuffArr()[(int)Buff::Atk];
	int AtkBonus = 0;
	//###############################################################################

	float VulDebuff = 1.f;
	float WeakDebuff = 1.f;

	//�÷��̾ �����¶�� ���ϴ� ���� ����
	if (m_BuffArr[(int)Buff::Vulnerable])
	{
		VulDebuff = 1.5f;
	}
	//���Ͱ� ��ȭ���¶�� �޴� ���� ����
	//if (m_Scene->GetMonster()->GetBuffArr()[(int)Buff::Weak]) 
	//{
	//	WeakDebuff = 0.75;
	//}

	//���� ������
	int FinalDamage = (int)((Damage + AtkBonus) * WeakDebuff * VulDebuff);

	if (m_Shield > 0) {
		m_Shield -= FinalDamage;
		if (m_Shield < 0) {
			m_HP += (m_Shield);
			m_Shield = 0;
		}
	}
	else
	{
		m_HP -= FinalDamage;
	}
	
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
	
	//������ ���
	CFloatingDamage* Damages = m_Scene->CreateObject<CFloatingDamage>("Damages");
	Damages->SetPos(GetPos().x,GetPos().y-100.f);
	char ch[256] = {};
	sprintf_s(ch, "%d", FinalDamage);
	TCHAR t[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, ch, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ch, -1, t, Length);
	Damages->GetText()->GetWidget<CText>()->SetText(t);

	SetEnableDamaged(true);

	if (m_HP <= 0)
	{
		//���
		m_HP = 0;
		
		CGameOver* Gameover = m_Scene->CreateObject<CGameOver>("DefeatBack");
		Gameover->SetTexture("DefeatBack", TEXT("Scene/Defeat.bmp"));
		Gameover->SetColorKey(255, 0, 255);
		Gameover->SetSize(1280.f, 720.f);
		
		CGameOver* PlayerDefeat = m_Scene->CreateObject<CGameOver>("PlayerDefeat");
		PlayerDefeat->SetTexture("PlayerDefeat", TEXT("Player/corpse.bmp"));
		PlayerDefeat->SetPos(150, 300);
		PlayerDefeat->SetSize(256.f, 256.f);
		PlayerDefeat->SetColorKey(255, 0, 255);
		m_Scene->SetDefeatSwitch(true);
		
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
