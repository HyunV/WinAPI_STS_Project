#include "Slime.h"

#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
#include "../../Collision/ColliderBox.h"
#include "../../Widget/WidgetComponent.h"
#include "../../Widget/Text.h"
#include "../../Widget/ProgressBar.h"
#include "../../Widget/ImageWidget2.h"
#include "../../GameObject/CardManager.h"
#include "../../GameObject/FloatingDamage.h"
#include "../../GameObject/TurnEffect.h"
#include "../../GameObject/BubbleMessage.h"
#include "../../GameObject/Effects/ShieldEffect.h"
#include "../../GameObject/Effects/CPlayerHitEffect.h"
#include "../../GameObject/Effects/DelayObject.h"

CSlime::CSlime()
{
	SetTypeID<CSlime>();
	m_UseTurn = false;
	m_NextStatus = EMonsterStatus::attack;
	m_MonAttackDamage = 7;
	m_IntantIcon = 0;
	m_IntantDamage = 0;
	m_Count = 0;
	m_AttackSpeed = 0;
	m_AttackDir = 0;
	m_UseTurn = 0;


}
CSlime::~CSlime()
{
}
bool CSlime::Init()
{
	CCharacter::Init();
	int turn = CCardManager::GetInst()->GetTurnCount();

	m_MaxHP = CCardManager::GetInst()->RangeRand(28, 32);
	m_HP = m_MaxHP;
	
	m_MonAttackDamage = 7; //�⺻���ݷ�

	//�̼�
	m_AttackDir = -1.f;
	m_AttackSpeed = 900.f;

	//������ ����
	SetMoveObject(true);
	m_MoveSpeed = 40.f;

	//ũ��, ��ġ, �̹���
	SetPos(1000.f, 450.f);
	m_OriginPos = GetPos();
	SetSize(180.f, 180.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("Slime", TEXT("Monster/Slime.bmp"));

	//�浹
	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(180.f, 180.f);
	Box->SetCollisionProfile("Monster");
	SetColorKey(255, 0, 255);

	Box->SetMouseCollisionBeginFunction<CSlime>(this, &CSlime::CollisionMouseBegin);
	Box->SetMouseCollisionEndFunction<CSlime>(this, &CSlime::CollisionMouseEnd);
	Box->SetCollisionBeginFunction(this, &CSlime::CollisionBegin);
	Box->SetCollisionEndFunction(this, &CSlime::CollisionEnd);


	//UI
	m_NameBar = CreateWidgetComponent<CText>("MonsterNameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("������"));
	m_NameBar->GetWidget<CText>()->SetEnable(false);
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetFont("NameFont");
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(0.f, 135.f);

	m_IntantIcon = CreateWidgetComponent<CImageWidget2>("IntantStatus");
	m_IntantIcon->GetWidget<CImageWidget2>()->SetSize(32, 32);
	m_IntantIcon->SetPos(0, -70);

	m_IntantDamage = CreateWidgetComponent<CText>("IntantDamageText");
	m_IntantDamage->GetWidget<CText>()->SetText(TEXT("0"));
	m_IntantDamage->GetWidget<CText>()->EnableShadow(true);
	m_IntantDamage->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_IntantDamage->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_IntantDamage->GetWidget<CText>()->SetFont("UI");
	m_IntantDamage->GetWidget<CText>()->SetSize(32, 32);
	m_IntantDamage->SetPos(0, -50);
	m_IntantDamage->GetWidget<CText>()->SetEnable(false);

	randomattack();

	return true;
}

void CSlime::Update(float DeltaTime)
{
	//�ϴ� ����â ��ġ����(����)
	m_BuffFirstPos = (0.f, -60.f);
	m_TextOffSet = (0.f, 13.f); 

	CCharacter::Update(DeltaTime);

	MonstersAI();

	//�ΰ����� ���� ###################################################
	 
	//���������� ����
	int FinalDamage = m_MonAttackDamage + m_BuffArr[0];
	float vul = 1.f;
	float weak = 1.f;

	if (m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Vulnerable] > 0) { //�÷��̾� ����
		vul = 1.5f;
	}
	if (m_BuffArr[(int)Buff::Weak] > 0) //�ش� ��ü ��ȭ�� ��
	{
		weak = 0.75f;
	}

	FinalDamage = (int)(FinalDamage * vul * weak); //������ ���

	char ch[256] = {};
	sprintf_s(ch, "%d", FinalDamage);
	TCHAR t[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, ch, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ch, -1, t, Length);
	m_IntantDamage->GetWidget<CText>()->SetText(t);

	//##########################################################################

	if (CCardManager::GetInst()->GetMonstersTurn()) //���� ���϶�
	{
		if (m_NextStatus == EMonsterStatus::buff || m_NextStatus == EMonsterStatus::debuff ||
			m_NextStatus == EMonsterStatus::defend || m_NextStatus == EMonsterStatus::defendBuff)
		{
			if (m_EnableAttack)
			{
				if (m_NextStatus == EMonsterStatus::debuff)
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

						m_EnableAttack = false;
						ActivateMonster(m_NextStatus);
						SetEnableAttack(false);
						CheckNextMonster();

						randomattack();
					}
				}
				else if (m_NextStatus == EMonsterStatus::buff)
				{
					ActivateMonster(m_NextStatus);
					SetEnableAttack(false);
					CheckNextMonster();
				}
				else if (m_NextStatus == EMonsterStatus::defend ||
					m_NextStatus == EMonsterStatus::defendBuff)
				{
					// ���� ����Ʈ		
					ActivateMonster(m_NextStatus);
					SetEnableAttack(false);
					CheckNextMonster();		
				}
			}
		}

		//����
		if (m_NextStatus == EMonsterStatus::attack || m_NextStatus == EMonsterStatus::attackBuff ||
			m_NextStatus == EMonsterStatus::attackDebuff || m_NextStatus == EMonsterStatus::attackDefend)
		{
			if (m_EnableAttack) {
				m_Pos.x += m_AttackDir * m_AttackSpeed * DeltaTime;
				if (m_OriginPos.x - GetPos().x >= 150.f)
				{
					m_AttackDir = 1.f;
					m_AttackSpeed = 300.f;
				}
				if (m_Pos.x >= m_OriginPos.x) {
					CPlayerHitEffect* Hit = m_Scene->CreateObject<CPlayerHitEffect>("Hit");
					m_Scene->GetSceneResource()->SoundPlay("25_SlimeAttack");
					Hit->SetTexture("SlimeAttack", TEXT("SlimeAttack.bmp"));
					Hit->SetSize(120, 100);
					SetPos(m_OriginPos);
					m_AttackDir = -1.f;
					m_AttackSpeed = 900.f;

					m_EnableAttack = false;
					ActivateMonster(m_NextStatus);
					SetEnableAttack(false);
					CheckNextMonster();
					randomattack();
				}

			}
		}

	}

	//�ǰ� ���
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

void CSlime::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CSlime::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CSlime::InflictDamage(float Damage)
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
	int FinalDamage = (int)((Damage + AtkBonus) * WeakDebuff * VulDebuff);

	//�ǵ� ���� ��
	if (m_Shield > 0) {
		m_Shield -= FinalDamage;
		if (m_Shield < 0) {
			m_Scene->GetSceneResource()->SoundPlay("24_BrokenShield");
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
	Damages->SetPos(GetPos().x, GetPos().y - 100.f);
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
		SetIsDeath(true);
		if (m_Scene->CheckMonsters())
		{
			//MessageBox(nullptr, TEXT("���� ��"), TEXT("a"), MB_OK);
			m_Scene->SetIsBattle(false);

			//������ ȣ������..
			//������, ��������, �� ����
			CDelayObject* Delay = m_Scene->CreateObject<CDelayObject>("Delay");
		};
	}
	return Damage;
}

void CSlime::MonstersAI()
{
	//�ϸ��� �ൿ ������ �ҷ��´�.
	//int Turn = CCardManager::GetInst()->GetTurnCount();
	//
	//switch (Turn)
	//{
	//case 1:
	//	m_NextStatus = EMonsterStatus::debuff;
	//	m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("debuffInt", TEXT("Intent/debuff1.bmp"));
	//	m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	//	break;
	////case 2:
	////	m_NextStatus = EMonsterStatus::attack;
	////	m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("attackInt", TEXT("Intent/attack.bmp"));
	////	m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	////	m_IntantDamage->GetWidget<CText>()->SetEnable(true);
	////	break;
	////case 3:
	////	break;
	////default:
	////	m_NextStatus = EMonsterStatus::attack;
	////	m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("attackInt", TEXT("Intent/attack.bmp"));
	////	m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	////	m_IntantDamage->GetWidget<CText>()->SetEnable(true);
	////	break;
	//}
}

bool CSlime::ActivateMonster(EMonsterStatus m_NextStatus)
{
	//���Ͱ� ������ ��� �ൿ�Ѵ�.
	switch (m_NextStatus)
	{
	case EMonsterStatus::attack:
		m_Scene->GetPlayer()->InflictDamage((float)10 + m_BuffArr[0]);
		break;

	case EMonsterStatus::attackDebuff:
		//
		m_Scene->GetPlayer()->InflictDamage((float)7 + m_BuffArr[0]);
		m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Weak] += 2;
		break;
	case EMonsterStatus::debuff:
		m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Weak] += 2;
		m_Scene->GetSceneResource()->SoundPlay("27_Slime_Debuff");
		break;
	}
	return true;
}

void CSlime::CheckNextMonster()
{

	CCardManager::GetInst()->AddMonstersAttackCount();
	int n = CCardManager::GetInst()->GetMonsterAttackCount();
	int size = (int)m_Scene->GetMonsters().size();

	if (size - n > 0) //�迭 ������ - ī��Ʈ 0���� ũ��(���Ͱ� ����������)
	{
		m_Scene->GetMonsters()[n]->SetEnableAttack(true);
	}
	else
	{
		CCardManager::GetInst()->SetMonsterAttackCount(0);
		if (CCardManager::GetInst()->GetTurnEffect() == nullptr)
		{
			EndCallbackMonster();
		}
	}
}

void CSlime::EndCallbackMonster()
{
	//������ Ȯ��	
	if (m_Scene->GetPlayer()->GetEnable())
	{
		CTurnEffect* TurnMessage = m_Scene->CreateObject<CTurnEffect>("TurnMessage");
		TurnMessage->SetTurnMessage(EWhos_Turn::Player);
		CCardManager::GetInst()->SetTurnCount(CCardManager::GetInst()->GetTurnCount() + 1);
		//�� ���� �� ����� ����, �ǽ� ���� �� ���ݷ� ����
		m_Scene->MonstersBuffControl();
	}
}

void CSlime::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
	m_NameBar->GetWidget<CText>()->SetEnable(true);
}

void CSlime::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	m_NameBar->GetWidget<CText>()->SetEnable(false);
}

void CSlime::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CSlime::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
}

void CSlime::AddShield(int Shield)
{
	m_Shield = m_Shield + Shield + m_BuffArr[(int)Buff::Dex];
	CShieldEffect* ShieldEf2 = m_Scene->CreateObject<CShieldEffect>("ShieldEf2");
	ShieldEf2->SetPos(950.f, 250.f);
	ShieldSound();
}

void CSlime::randomattack()
{
	//srand((unsigned int)time(0));
	int n = rand() % 3;
	if (n == 0) //�Ϲݰ���
	{
		m_NextStatus = EMonsterStatus::attack;
		m_MonAttackDamage = 10;
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("attackInt", TEXT("Intent/attack.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(true);
	}
	if (n == 1) //�����
	{
		m_NextStatus = EMonsterStatus::debuff;
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("debuffInt", TEXT("Intent/debuff1.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(false);
	}
	if (n == 2) //����� ����
	{
		m_NextStatus = EMonsterStatus::attackDebuff;
		m_MonAttackDamage = 7;
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("attackDebuffInt", TEXT("Intent/attackDebuff.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(true);
	}
}
