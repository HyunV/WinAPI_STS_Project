#include "Jaw.h"

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


//턱벌레
CJaw::CJaw()
{
	m_UseTurn = false;
	m_NextStatus = EMonsterStatus::attack;
	m_MonAttackDamage = 11;
	m_IntantIcon = 0;
	m_IntantDamage = 0;
	m_Count = 0;
	m_AttackSpeed = 0;
	m_AttackDir = 0;
}


CJaw::~CJaw()
{
}

bool CJaw::Init()
{
    CCharacter::Init();
    int turn = CCardManager::GetInst()->GetTurnCount();

    m_MaxHP = CCardManager::GetInst()->RangeRand(40, 44);
    m_HP = m_MaxHP;

	m_MonAttackDamage = 11; //기본공격력

	//이속
	m_AttackDir = -1.f;
	m_AttackSpeed = 1500.f;

	//움직임 여부
	SetMoveObject(true);
	m_MoveSpeed = 35.f;

	//크기, 위치, 이미지
	SetPos(1000.f, 450.f);
	m_OriginPos = GetPos();
	SetSize(180.f, 180.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("Jaw", TEXT("Monster/enemy2.bmp"));

	//충돌
	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(180.f, 180.f);
	Box->SetCollisionProfile("Monster");
	SetColorKey(255, 0, 255);

	Box->SetMouseCollisionBeginFunction<CJaw>(this, &CJaw::CollisionMouseBegin);
	Box->SetMouseCollisionEndFunction<CJaw>(this, &CJaw::CollisionMouseEnd);
	Box->SetCollisionBeginFunction(this, &CJaw::CollisionBegin);
	Box->SetCollisionEndFunction(this, &CJaw::CollisionEnd);

	//UI
	m_NameBar = CreateWidgetComponent<CText>("MonsterNameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("턱벌레"));
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

void CJaw::Update(float DeltaTime)
{
	m_BuffFirstPos = (0.f, -60.f);
	m_TextOffSet = (0.f, 13.f);

	CCharacter::Update(DeltaTime);

	int FinalDamage = m_MonAttackDamage + m_BuffArr[0];
	float vul = 1.f;
	float weak = 1.f;

	if (m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Vulnerable] > 0) { //플레이어 취약시
		vul = 1.5f;
	}
	if (m_BuffArr[(int)Buff::Weak] > 0) //해당 객체 약화일 시
	{
		weak = 0.75f;
	}

	FinalDamage = (int)(FinalDamage * vul * weak); //최종뎀 계산

	char ch[256] = {};
	sprintf_s(ch, "%d", FinalDamage);
	TCHAR t[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, ch, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ch, -1, t, Length);
	m_IntantDamage->GetWidget<CText>()->SetText(t);

	//##########################################################################

	if (CCardManager::GetInst()->GetMonstersTurn()) //몬스터 턴일때
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
						m_Scene->GetSceneResource()->SoundPlay("33_Buff");

						randomattack();
					}
				}
				else if (m_NextStatus == EMonsterStatus::buff)
				{
					ActivateMonster(m_NextStatus);
					SetEnableAttack(false);
					CheckNextMonster();
					randomattack();
				}
				else if (m_NextStatus == EMonsterStatus::defend ||
					m_NextStatus == EMonsterStatus::defendBuff)
				{
					// 쉴드 이펙트		
					ActivateMonster(m_NextStatus);
					SetEnableAttack(false);
					CheckNextMonster();
					randomattack();
				}
			}
		}

		//공격
		if (m_NextStatus == EMonsterStatus::attack || m_NextStatus == EMonsterStatus::attackBuff ||
			m_NextStatus == EMonsterStatus::attackDebuff || m_NextStatus == EMonsterStatus::attackDefend)
		{
			if (m_EnableAttack) {
				m_Pos.x += m_AttackDir * m_AttackSpeed * DeltaTime;
				if (m_OriginPos.x - GetPos().x >= 150.f)
				{
					m_AttackDir = 1.f;
					m_AttackSpeed = 800.f;
				}
				if (m_Pos.x >= m_OriginPos.x) {
					CPlayerHitEffect* Hit = m_Scene->CreateObject<CPlayerHitEffect>("Hit");
					SetPos(m_OriginPos);
					m_AttackDir = -1.f;
					m_AttackSpeed = 1500.f;

					m_EnableAttack = false;
					ActivateMonster(m_NextStatus);
					SetEnableAttack(false);
					CheckNextMonster();
					randomattack();
					m_Scene->GetSceneResource()->SoundPlay("12_EnemyAttack");
				}

			}
		}

	}

	//피격 모션
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

void CJaw::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CJaw::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CJaw::InflictDamage(float Damage)
{
	Damage = CCharacter::InflictDamage(Damage);

	int AtkBonus = m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Atk];
	float VulDebuff = 1.f;
	float WeakDebuff = 1.f;

	//자신이 취약상태라면 받는 피해 증가
	if (m_BuffArr[(int)Buff::Vulnerable])
	{
		VulDebuff = 1.5f;
	}
	//플레이어가 약화 상태라면 받는 피해 감소
	if (m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Weak])
	{
		WeakDebuff = 0.75f;
	}

	//최종데미지
	int FinalDamage = (int)((Damage + AtkBonus) * WeakDebuff * VulDebuff);

	//실드 보유 시
	if (m_Shield > 0) {
		m_Shield -= FinalDamage;
		if (m_Shield < 0) {
			m_Scene->GetSceneResource()->SoundPlay("24_BrokenShield");
			m_HP += (m_Shield);
			m_Shield = 0;
		}
	}
	else //실드 미보유시
	{
		m_HP -= FinalDamage;
	}

	//최종 데미지 출력
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

	//사망
	if (m_HP <= 0)
	{
		SetActive(false);
		SetIsDeath(true);
		m_Scene->GetSceneResource()->SoundPlay("jawDeath");
		if (m_Scene->CheckMonsters())
		{
			//MessageBox(nullptr, TEXT("게임 끝"), TEXT("a"), MB_OK);
			m_Scene->SetIsBattle(false);

			//씬에다 호출하자..
			//보상탭, 버프제거, 덱 복구
			//CCardManager::GetInst()->BattleReset();
			//m_Scene->CreateWidgetWindow<CReward>("Reward");
			CDelayObject* Delay = m_Scene->CreateObject<CDelayObject>("Delay");
			
		};
	}
	return Damage;
}

void CJaw::MonstersAI()
{

}

bool CJaw::ActivateMonster(EMonsterStatus m_NextStatus)
{
	switch (m_NextStatus)
	{
	case EMonsterStatus::attack:
		m_Scene->GetPlayer()->InflictDamage((float)12 + m_BuffArr[0]);
		break;

	case EMonsterStatus::attackDefend:
		m_Scene->GetPlayer()->InflictDamage((float)7 + m_BuffArr[0]);
		AddShield(5);
		break;

	case EMonsterStatus::defendBuff:
		m_BuffArr[0] += 3;
		AddShield(6);
		m_Scene->GetSceneResource()->LoadSound("Effect", "33_Buff", false, "33_Buff.ogg");
		break;
	}
    return true;
}

void CJaw::CheckNextMonster()
{
	CCardManager::GetInst()->AddMonstersAttackCount();
	int n = CCardManager::GetInst()->GetMonsterAttackCount();
	int size = (int)m_Scene->GetMonsters().size();

	if (size - n > 0) //배열 사이즈 - 카운트 0보다 크면(몬스터가 남아있으면)
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

void CJaw::EndCallbackMonster()
{
	//턴종료 확정	
	if (m_Scene->GetPlayer()->GetEnable())
	{
		CTurnEffect* TurnMessage = m_Scene->CreateObject<CTurnEffect>("TurnMessage");
		TurnMessage->SetTurnMessage(EWhos_Turn::Player);
		CCardManager::GetInst()->SetTurnCount(CCardManager::GetInst()->GetTurnCount() + 1);
		//턴 시작 시 디버프 감소, 의식 존재 시 공격력 증가
		m_Scene->MonstersBuffControl();
	}
}

void CJaw::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
	m_NameBar->GetWidget<CText>()->SetEnable(true);
}

void CJaw::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	m_NameBar->GetWidget<CText>()->SetEnable(false);
}

void CJaw::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	
}

void CJaw::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
}

void CJaw::AddShield(int Shield)
{
	m_Shield = m_Shield + Shield + m_BuffArr[(int)Buff::Dex];
	//CShieldEffect* ShieldEf2 = m_Scene->CreateObject<CShieldEffect>("ShieldEf2");
	//ShieldEf2->SetPos(950.f, 250.f);
	ShieldSound();
}

void CJaw::randomattack()
{
	//srand((unsigned int)time(0));
	int n = rand() % 3;
	if (n == 0) //일반공격
	{
		m_NextStatus = EMonsterStatus::attack;
		m_MonAttackDamage = 11;
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("attackInt", TEXT("Intent/attack.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(true);
	}
	if (n == 1) //공격 방어
	{
		m_NextStatus = EMonsterStatus::attackDefend;
		m_MonAttackDamage = 7;
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("attackDefendInt", TEXT("Intent/attackDefend.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(true);
	}
	if (n == 2) //방어 및 버프
	{
		m_NextStatus = EMonsterStatus::defendBuff;
		
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("defendBuffInt", TEXT("Intent/defendBuff.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(false);
	}
}

void CJaw::UseBuff()
{
}
