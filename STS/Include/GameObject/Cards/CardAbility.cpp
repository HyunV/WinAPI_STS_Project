#include "CardAbility.h"

CCardAbility::CCardAbility()
{
	m_Power = 0;
	m_Explain[0] = {};
}

CCardAbility::~CCardAbility()
{
}

TCHAR* CCardAbility::GetExplain()
{
	return m_Explain;
}

void CCardAbility::ActivateAbility(CGameObject* owner, CGameObject* target)
{
}
