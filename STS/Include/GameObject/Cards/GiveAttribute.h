#pragma once
#include "CardAbility.h"
#include "../../CardFlag.h"

class CGiveAttribute :
    public CCardAbility
{
    friend class CScene;
public:
    virtual void ActivateAbility(CGameObject* owner, CGameObject* target);


    void SetType(Card_Attribute Type, float Power);


protected:
    Card_Attribute m_Type;
};

