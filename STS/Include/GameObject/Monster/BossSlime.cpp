#include "BossSlime.h"

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
#include "../../GameObject/Effects/DelayScene.h"

CBossSlime::CBossSlime()
{
	m_AttackDir = 0;
	m_UseTurn = 0;
	m_NextStatus = EMonsterStatus::debuff;
	m_MonAttackDamage = 29;
	m_IntantIcon = 0;
	m_IntantDamage = 0;
	m_Count = 0;
	m_AttackSpeed = 0;
	m_AttackDir = 0;
}


CBossSlime::~CBossSlime()
{
}

bool CBossSlime::Init()
{
	CCharacter::Init();
	int turn = CCardManager::GetInst()->GetTurnCount();

	m_MaxHP = 140;
	m_HP = m_MaxHP;

	m_MonAttackDamage = 29; //기본공격력

	//이속
	m_AttackDir = -1.f;
	m_AttackSpeed = 600.f;

	//움직임 여부
	SetMoveObject(true);
	m_MoveSpeed = 35.f;

	//크기, 위치, 이미지
	SetPos(950.f, 400.f);
	m_OriginPos = GetPos();
	SetSize(308.f, 308.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("BossSlime", TEXT("Monster/boss.bmp"));

	//충돌
	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(308.f, 308.f);
	Box->SetCollisionProfile("Monster");
	SetColorKey(255, 0, 255);

	Box->SetMouseCollisionBeginFunction<CBossSlime>(this, &CBossSlime::CollisionMouseBegin);
	Box->SetMouseCollisionEndFunction<CBossSlime>(this, &CBossSlime::CollisionMouseEnd);
	Box->SetCollisionBeginFunction(this, &CBossSlime::CollisionBegin);
	Box->SetCollisionEndFunction(this, &CBossSlime::CollisionEnd);

	//UI
	m_NameBar = CreateWidgetComponent<CText>("MonsterNameBar");
	m_NameBar->GetWidget<CText>()->SetText(TEXT("거대 슬라임"));
	m_NameBar->GetWidget<CText>()->SetEnable(false);
	m_NameBar->GetWidget<CText>()->EnableShadow(true);
	m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_NameBar->GetWidget<CText>()->SetFont("NameFont");
	m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_NameBar->SetPos(0.f, 185.f);

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

	m_HPBarFrame->SetPos(0.f, 170.f);
	m_HPBar->SetPos(0.f, 170.f);
	m_HPText->SetPos(49.f, 207.f);


	return true;
}

void CBossSlime::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (!m_isDeath) {
		m_Scene->GetSceneResource()->SoundPause("StageBGM");
	}

	if (m_Shield > 0) {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
		m_ShieldImage->GetWidget<CImageWidget2>()->SetEnable(true);
		m_ShieldText->GetWidget<CImageWidget2>()->SetEnable(true);

		ConvertText(m_Shield, m_ShieldText);

	}
	else {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
		m_ShieldImage->GetWidget<CImageWidget2>()->SetEnable(false);
		m_ShieldText->GetWidget<CImageWidget2>()->SetEnable(false);
	}

	char Text[256] = {};
	sprintf_s(Text, "%d/%d", m_HP, m_MaxHP);

	TCHAR Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);
	m_HPText->GetWidget<CText>()->SetText(Unicode);

	UpdateStatus();

	int count = 0;

	auto iter = m_StatusList.begin();
	auto end = m_StatusList.end();


	for (; iter != end;)
	{
		if (!(*iter)->GetWidget()->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->SetPos(m_BuffFirstPos.x-60 + (count * 20), 190.f);
		iter++;
		count++;
	}

	count = 0;

	auto iter2 = m_ValueList.begin();
	auto end2 = m_ValueList.end();

	for (; iter2 != end2;)
	{
		if (!(*iter2)->GetWidget()->GetEnable())
		{
			++iter2;
			continue;
		}
		(*iter2)->SetPos(m_BuffFirstPos.x-45 + m_TextOffSet.x + (count * 20), 200.f);
		iter2++;
		count++;
	}
	count = 0;

	for (int i = 0; i < m_ValueList.size(); i++)
	{
		ConvertText(ArrTemp[i], m_ValueList[i]);
	}

	

	MonstersAI();
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
	int Length2 = MultiByteToWideChar(CP_ACP, 0, ch, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, ch, -1, t, Length2);
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
					m_Scene->GetSceneResource()->SoundPlay("26_BossSlimeAttack");
					Hit->SetTexture("SlimeAttack", TEXT("SlimeAttack.bmp"));
					Hit->SetSize(120, 100);
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

void CBossSlime::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossSlime::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CBossSlime::InflictDamage(float Damage)
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
		if (m_Scene->CheckMonsters())
		{
			//MessageBox(nullptr, TEXT("게임 끝"), TEXT("a"), MB_OK);
			m_Scene->SetIsBattle(false);

			//씬에다 호출하자..
			//보상탭, 버프제거, 덱 복구
			//CDelayObject* Delay = m_Scene->CreateObject<CDelayObject>("Delay");
			
			CDelayScene* Scene = m_Scene->CreateObject<CDelayScene>("Scene");//엔딩으로 넘어감
			m_Scene->GetSceneResource()->SoundStop("38_BossBGM");
			m_Scene->GetSceneResource()->SoundPlay("29_BossSlimeDead");
			m_Scene->GetSceneResource()->SoundPlay("30_BossSlimeDead2");
			m_Scene->GetSceneResource()->SoundPlay("31_VictoryBoss");
		};
	}
	return Damage;
}

void CBossSlime::MonstersAI()
{
	//턴마다 행동 패턴을 불러온다.
	int Turn = CCardManager::GetInst()->GetTurnCount();
	switch ((Turn-1)%3)
	{
	case 0:
		//점액뿌리기(약화로 대체)
		m_NextStatus = EMonsterStatus::debuff;
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("debuffInt", TEXT("Intent/debuff1.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(false);
		break;
	case 1: //
		m_NextStatus = EMonsterStatus::buff;
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("buffInt", TEXT("Intent/buff1.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(false);
		break;
	case 2:
		m_NextStatus = EMonsterStatus::attack;
		m_IntantIcon->GetWidget<CImageWidget2>()->SetTexture("attackInt", TEXT("Intent/attack.bmp"));
		m_IntantIcon->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
		m_IntantDamage->GetWidget<CText>()->SetEnable(true);
		break;
	}
}

bool CBossSlime::ActivateMonster(EMonsterStatus m_NextStatus)
{
	switch (m_NextStatus)
	{
	case EMonsterStatus::attack:
		m_MonAttackDamage = 29;
		m_Scene->GetPlayer()->InflictDamage((float)m_MonAttackDamage + m_BuffArr[0]);
		break;
	case EMonsterStatus::attackBuff:
		break;
	case EMonsterStatus::attackDebuff:
		break;
	case EMonsterStatus::attackDefend:
		m_MonAttackDamage = 4;
		m_Scene->GetPlayer()->InflictDamage((float)m_MonAttackDamage + m_BuffArr[0]);
		AddShield(6);
		break;
	case EMonsterStatus::buff:
		UseBuff();
		break;
	case EMonsterStatus::debuff:
		m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Weak] += 3;
		m_Scene->GetSceneResource()->SoundPlay("27_Slime_Debuff");
		break;
	case EMonsterStatus::defend:
		break;
	case EMonsterStatus::defendBuff:
		break;
	default:
		break;
	}
	return true;
}

void CBossSlime::CheckNextMonster()
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

void CBossSlime::EndCallbackMonster()
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

void CBossSlime::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
	m_NameBar->GetWidget<CText>()->SetEnable(true);
}

void CBossSlime::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	m_NameBar->GetWidget<CText>()->SetEnable(false);
}

void CBossSlime::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CBossSlime::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_MaxHP);
}

void CBossSlime::AddShield(int Shield)
{
	m_Shield = m_Shield + Shield + m_BuffArr[(int)Buff::Dex];
	ShieldSound();
}

void CBossSlime::randomattack()
{
}

void CBossSlime::UseBuff()
{
	CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("MonsterBuffed");
	Message->SetMessageType(EMessageBox_Type::Monster);
	Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("슬라임.. 으깬다!!"));
	Message->SetPos(GetPos().x - 180, GetPos().y - 70);
	m_Scene->GetSceneResource()->SoundPlay("28_BossSlime_P2");
	m_BuffArr[(int)Buff::Dex] += 1;
	m_BuffArr[(int)Buff::Atk] += 1;
	m_BuffArr[(int)Buff::Rage] += 1;
	m_BuffArr[(int)Buff::Ritual] += 1;
	m_Scene->GetSceneResource()->SoundPlay("33_Buff");
}

//점액덩어리 구현?
//분열 구현?