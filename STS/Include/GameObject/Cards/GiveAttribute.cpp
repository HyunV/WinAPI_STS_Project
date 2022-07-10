#include "GiveAttribute.h"
#include "../Character.h"
#include "../../Scene/Scene.h"
#include <sstream>
#include "../CardManager.h"

CGiveAttribute::CGiveAttribute()
{
	m_Type = Card_Attribute::None;
}

//�����Ƽ Ȱ��ȭ ����
void CGiveAttribute::ActivateAbility(CGameObject* owner, CGameObject* target)
{
	//ī��, Ÿ��
	switch (m_Type)
	{
	case Card_Attribute::Damage:	
		target->InflictDamage((float)m_Power);
		m_Scene->GetPlayer()->SetEnableAttack(true);
		break;
	case Card_Attribute::Shield:
		m_Scene->GetPlayer()->AddShield(m_Power);
		//�÷��̾� -> addShield(m_Power);
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
		sprintf_s(Text, "���ظ� %d �ݴϴ�.", (int)Power);
		break;
	case Card_Attribute::Shield:
		sprintf_s(Text, "���� %d ����ϴ�.", (int)Power);
		break;
	case Card_Attribute::DrawCard:
		sprintf_s(Text, "ī�带 %d �� �̽��ϴ�.", (int)Power);
		break;
	case Card_Attribute::Exhaust:
		sprintf_s(Text, "�Ҹ�");
		break;
	case Card_Attribute::Vulnerable:
		sprintf_s(Text, "����� %d �ݴϴ�.", (int)Power);
		break;
	case Card_Attribute::Weak:
		sprintf_s(Text, "��ȭ�� %d �ݴϴ�.", (int)Power);
		break;
	case Card_Attribute::Inflame:
		sprintf_s(Text, "���� %d ����ϴ�.", (int)Power);
		break;
	case Card_Attribute::FootWork:
		sprintf_s(Text, "��ø���� %d ����ϴ�.", (int)Power);
		break;
	case Card_Attribute::Barricade:
		sprintf_s(Text, "���� ������� �ʽ��ϴ�.");
		break;
	case Card_Attribute::LimitBreak:
		sprintf_s(Text, "���� 2�� �����մϴ�.");
		break;
	case Card_Attribute::DemonForm:
		sprintf_s(Text, "���� %d ����ϴ�.",(int)Power);
		break;
	case Card_Attribute::BodySlam:
		sprintf_s(Text, "�� ����ŭ ���ظ� �ݴϴ�.");
		break;
	case Card_Attribute::Entrench:
		sprintf_s(Text, "���� 2��� ����ϴ�.");
		break;
	case Card_Attribute::Text1:
		sprintf_s(Text, "�� �� ���� ��");
		break;
	case Card_Attribute::PlusHP:
		sprintf_s(Text, "ü���� %d ȸ���մϴ�.", (int)Power);
		break;
	case Card_Attribute::LoseHP:
		sprintf_s(Text, "ü���� %d �ҽ��ϴ�.", (int)Power);
		break;
	case Card_Attribute::GetEnergy:
		sprintf_s(Text, "�������� %d ����ϴ�.", (int)Power);
		break;
	}

	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	lstrcpy(m_Explain, Unicode);
}
