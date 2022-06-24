#include "GiveAttribute.h"
#include <sstream>

//�����Ƽ Ȱ��ȭ ����
void CGiveAttribute::ActivateAbility(CGameObject* target)
{
	switch (m_Type)
	{
	case Card_Attribute::Damage:
		target->InflictDamage(m_Power);
		break;
	case Card_Attribute::Shield:
		//�÷��̾� -> addShield(m_Power);
	{
		int a = 0;
	}		
		break;
	}
}

void CGiveAttribute::SetType(Card_Attribute Type, float Power)
{
	m_Type = Type;
	m_Power = Power;


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
	}




	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	lstrcpy(m_Explain, Unicode);
}
