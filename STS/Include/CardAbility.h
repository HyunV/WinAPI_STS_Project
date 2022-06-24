#pragma once
#include "../GameObject/GameObject.h"


class CCardAbility : public CGameObject
{
	//키워드

public:
	virtual void ActivateAbility(CGameObject* target);

protected:
	std::string m_Explain; //설명
	float m_Power; //계수
	//Give
};

