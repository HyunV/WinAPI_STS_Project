#pragma once
#include "CardAbility.h"
#include "../../CardFlag.h"

class CGiveAttribute :
    public CCardAbility
{
public:
    virtual void ActivateAbility(CGameObject* target);


    void SetType(Card_Attribute Type, float Power);


protected:
    Card_Attribute m_Type;
};

