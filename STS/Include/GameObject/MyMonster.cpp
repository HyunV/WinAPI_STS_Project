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
#include "../GameObject/TurnEffect.h"

CMyMonster::CMyMonster()
{
	SetTypeID<CMyMonster>();
}

CMyMonster::CMyMonster(const CMyMonster& Obj) :
	CCharacter(Obj)
{
}

CMyMonster::~CMyMonster()
{
}

bool CMyMonster::Init()
{
	CCharacter::Init();

	m_BuffArr[0] = 0; //���ݷ�
	m_BuffArr[1] = 0; //��ø��
	m_BuffArr[2] = 0; //�Ǹ������� //�Ͻ��� �� ���ݷ� +n
	m_BuffArr[3] = 0; //�ٸ����̵� //���Ȼ����
	m_BuffArr[4] = 0; //�ݳ�
	m_BuffArr[5] = 0; //�ǽ� �� ���۽� ���ݷ� + n
	m_BuffArr[6] = 0; //��� 50%�߰� ���� *1.5 //�� ���� �� 
	m_BuffArr[7] = 0; //��ȭ 25% ���� ������ *0.75

	m_AttackDir = -1.f;
	m_AttackSpeed = 1500.f;
	SetMoveObject(true);

	m_MoveSpeed = 30.f;

	SetPos(1000.f, 450.f);
	m_OriginPos = GetPos();
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
	//m_Shield = 10;

	m_NameBar = CreateWidgetComponent<CText>("MonsterNameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("������"));
	m_NameBar->GetWidget<CText>()->SetEnable(false);
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetFont("NameFont");
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(0.f, 135.f);	

	return true;
}

void CMyMonster::Update(float DeltaTime)
{
	m_BuffFirstPos = (0.f, -60.f);
	m_TextOffSet = (0.f, 13.f);
	CCharacter::Update(DeltaTime);

	//�ӽ��ڵ�
	if (CCardManager::GetInst()->GetMonstersTurn())
	{
		//
		if (m_EnableAttack)
		{
			m_Pos.x += m_AttackDir * m_AttackSpeed * DeltaTime;
			if (m_OriginPos.x - GetPos().x >= 150.f)
			{
				m_AttackDir = 1.f;
				m_AttackSpeed = 800.f;
			}
			if (m_Pos.x >= m_OriginPos.x) {
				SetPos(m_OriginPos);
				m_AttackDir = -1.f;
				m_AttackSpeed = 1500.f;
				//m_EnableAttack = false;
				///////////////////////////////�ӽ� �ڵ�

				m_Scene->GetPlayer()->InflictDamage(12);
				SetEnableAttack(false);

				if (CCardManager::GetInst()->GetTurnEffect() == nullptr)
				{
					CTurnEffect* TurnMessage = m_Scene->CreateObject<CTurnEffect>("TurnMessage");
					TurnMessage->SetTurnMessage(EWhos_Turn::Player);
					CCardManager::GetInst()->SetTurnCount(CCardManager::GetInst()->GetTurnCount() + 1);
				}
				
			}
		}
		//
	}

	//������ ���
	if (m_EnableDamaged)
	{
		m_Pos.x += m_AttackDir * (-1.f) * m_AttackSpeed * DeltaTime;
		if (GetPos().x - m_OriginPos.x >= 50.f)
		{
			m_AttackDir = 1.f;
			m_AttackSpeed = 800.f;
		}
		if (m_Pos.x <= m_OriginPos.x) {
			SetPos(m_OriginPos);
			m_AttackDir = -1.f;
			m_AttackSpeed = 1500.f;
			m_EnableDamaged = false;
		}
	}
}

void CMyMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMyMonster::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CMyMonster::InflictDamage(float Damage)
{
	Damage = CCharacter::InflictDamage(Damage);

	int AtkBonus = m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Atk];
	float VulDebuff = 1.f;
	float WeakDebuff = 1.f;

	//�ڽ��� �����¶�� �޴� ���� ����
	if (m_BuffArr[(int)Buff::Vulnerable])
	{
		VulDebuff = 1.5f;
	}
	//�÷��̾ ��ȭ ���¶�� �޴� ���� ����
	if (m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Weak])
	{
		WeakDebuff = 0.75f;
	}

	//����������
	int FinalDamage = (Damage + AtkBonus) * WeakDebuff * VulDebuff;

	//�ǵ� ���� ��
	if (m_Shield > 0) {
		m_Shield -= FinalDamage;
		if (m_Shield < 0) {
			m_HP += (m_Shield);
			m_Shield = 0;
		}
	}
	else //�ǵ� �̺�����
	{
		m_HP -= FinalDamage;
	}

	//���� ������ ���
	CFloatingDamage* Damages = m_Scene->CreateObject<CFloatingDamage>("Damages");
	Damages->SetPos(GetPos().x, GetPos().y-100.f);
	char ch[256] = {};
	sprintf_s(ch, "%d", FinalDamage);
	TCHAR t[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, ch, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ch, -1, t, Length);
	Damages->GetText()->GetWidget<CText>()->SetText(t);
	//
	SetEnableDamaged(true);

	//���
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
	//MessageBox(nullptr, TEXT("Ȯ��."), TEXT("^��^"), MB_OK);
	
	
}

void CMyMonster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
}
