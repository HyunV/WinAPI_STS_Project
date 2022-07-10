#include "GiveAttribute.h"
#include "../Character.h"
#include "../../Scene/Scene.h"
#include <sstream>
#include "../CardManager.h"

CGiveAttribute::CGiveAttribute()
{
	m_Type = Card_Attribute::None;
}

//어빌리티 활성화 구간
void CGiveAttribute::ActivateAbility(CGameObject* owner, CGameObject* target)
{
	//카드, 타겟
	switch (m_Type)
	{
	case Card_Attribute::Damage:	
		target->InflictDamage((float)m_Power);
		m_Scene->GetPlayer()->SetEnableAttack(true);
		break;
	case Card_Attribute::Shield:
		m_Scene->GetPlayer()->AddShield(m_Power);
		//플레이어 -> addShield(m_Power);
		break;
	case Card_Attribute::DrawCard:
		CCardManager::GetInst()->DrawCard(m_Power);
		m_Scene->GetSceneResource()->SoundPlay("SelectHandSound");
		break;
	case Card_Attribute::Exhaust:
		break;
	case Card_Attribute::Vulnerable:
		target->GetBuffArr()[(int)Buff::Vulnerable] += m_Power;
		m_Scene->GetSceneResource()->SoundPlay("32_DeBuff");
		break;
	case Card_Attribute::Weak:
		target->GetBuffArr()[(int)Buff::Weak] += m_Power;
		m_Scene->GetSceneResource()->SoundPlay("32_DeBuff");
		break;
	case Card_Attribute::Inflame:
		m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Atk] += m_Power;
		m_Scene->GetSceneResource()->SoundPlay("34_UsePower");
		break;
	case Card_Attribute::FootWork:
		m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Dex] += m_Power;
		m_Scene->GetPlayer()->ShieldSound();
		break;
	case Card_Attribute::Barricade:
		m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Barrigate] += 1;
		m_Scene->GetPlayer()->ShieldSound();
		break;
	case Card_Attribute::LimitBreak:
		m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::Atk] *= 2;
		m_Scene->GetSceneResource()->SoundPlay("34_UsePower");
		break;
	case Card_Attribute::DemonForm:
		m_Scene->GetPlayer()->GetBuffArr()[(int)Buff::DemonForm] += m_Power;
		m_Scene->GetSceneResource()->SoundPlay("34_UsePower");
		break;
	case Card_Attribute::BodySlam:
		target->InflictDamage((float)m_Scene->GetPlayer()->GetShield());
		break;
	case Card_Attribute::Entrench:		
		m_Scene->GetPlayer()->SetShield(m_Scene->GetPlayer()->GetShield() * 2);
		m_Scene->GetPlayer()->ShieldSound();
		break;
	case Card_Attribute::PlusHP:
		m_Scene->GetPlayer()->SetHP(m_Scene->GetPlayer()->GetHP() + m_Power);
		m_Scene->GetSceneResource()->SoundPlay("37_PlusHP");
		if (m_Scene->GetPlayer()->GetHP() > 80) {
			m_Scene->GetPlayer()->SetHP(80);
		}
		break;
	case Card_Attribute::LoseHP:
		//m_Scene->GetPlayer()->SetHP(m_Scene->GetPlayer()->GetHP() - m_Power);
		m_Scene->GetPlayer()->InflictDamage((float)m_Power);
		m_Scene->GetSceneResource()->SoundPlay("12_EnemyAttack");
		break;
	case Card_Attribute::GetEnergy:
		m_Scene->GetPlayer()->SetEnergy(m_Scene->GetPlayer()->GetEnergy() + m_Power);
		break;
	case Card_Attribute::Text1:
		break;
	}
}

void CGiveAttribute::SetType(Card_Attribute Type, float Power)
{
	m_Type = Type;
	m_Power = (int)Power;
	char	Text[256] = {};

	switch (m_Type)
	{
		
	case Card_Attribute::Damage:
		sprintf_s(Text, "피해를 %d 줍니다.", (int)Power);
		break;
	case Card_Attribute::Shield:
		sprintf_s(Text, "방어도를 %d 얻습니다.", (int)Power);
		break;
	case Card_Attribute::DrawCard:
		sprintf_s(Text, "카드를 %d 장 뽑습니다.", (int)Power);
		break;
	case Card_Attribute::Exhaust:
		sprintf_s(Text, "소멸");
		break;
	case Card_Attribute::Vulnerable:
		sprintf_s(Text, "취약을 %d 줍니다.", (int)Power);
		break;
	case Card_Attribute::Weak:
		sprintf_s(Text, "약화를 %d 줍니다.", (int)Power);
		break;
	case Card_Attribute::Inflame:
		sprintf_s(Text, "힘을 %d 얻습니다.", (int)Power);
		break;
	case Card_Attribute::FootWork:
		sprintf_s(Text, "민첩함을 %d 얻습니다.", (int)Power);
		break;
	case Card_Attribute::Barricade:
		sprintf_s(Text, "방어도가 사라지지 않습니다.");
		break;
	case Card_Attribute::LimitBreak:
		sprintf_s(Text, "힘이 2배 증가합니다.");
		break;
	case Card_Attribute::DemonForm:
		sprintf_s(Text, "힘을 %d 얻습니다.",(int)Power);
		break;
	case Card_Attribute::BodySlam:
		sprintf_s(Text, "내 방어도만큼 피해를 줍니다.");
		break;
	case Card_Attribute::Entrench:
		sprintf_s(Text, "방어도를 2배로 얻습니다.");
		break;
	case Card_Attribute::Text1:
		sprintf_s(Text, "내 턴 시작 시");
		break;
	case Card_Attribute::PlusHP:
		sprintf_s(Text, "체력을 %d 회복합니다.", (int)Power);
		break;
	case Card_Attribute::LoseHP:
		sprintf_s(Text, "체력을 %d 잃습니다.", (int)Power);
		break;
	case Card_Attribute::GetEnergy:
		sprintf_s(Text, "에너지를 %d 얻습니다.", (int)Power);
		break;
	}

	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	lstrcpy(m_Explain, Unicode);
}
