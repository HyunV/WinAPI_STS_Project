#include "GiveAttribute.h"
#include <sstream>

//어빌리티 활성화 구간
void CGiveAttribute::ActivateAbility(CGameObject* target)
{
	switch (m_Type)
	{
	case Card_Attribute::Damage:
		target->InflictDamage(m_Power);
		break;
	case Card_Attribute::Shield:
		//플레이어 -> addShield(m_Power);
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
		sprintf_s(Text, "피해를 %d 줍니다.", (int)Power);
		break;
	case Card_Attribute::Shield:
		sprintf_s(Text, "방어도를 %d 얻습니다.", (int)Power);
		break;
	case Card_Attribute::DrawCard:
		sprintf_s(Text, "카드를 %d 장 뽑습니다.", (int)Power);
	
	break;
	}




	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	lstrcpy(m_Explain, Unicode);
}
