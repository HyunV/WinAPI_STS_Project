#pragma once
#include "../GameObject/GameObject.h"


class CCardAbility : public CGameObject
{
	//Ű����

public:
	virtual void ActivateAbility(CGameObject* target);

protected:
	std::string m_Explain; //����
	float m_Power; //���
	//Give
};

