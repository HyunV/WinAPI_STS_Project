#pragma once

#include "../GameObject.h"

//CCardAbility 상속받아서

//CAttackAbiltiy 3
//CDefenstAbility 3

class CCardAbility : public CGameObject
{
    friend class CScene;
    friend class CCard;
    

protected:
    CCardAbility();
    virtual ~CCardAbility();

public:
    virtual TCHAR* GetExplain();


    virtual void ActivateAbility(CGameObject* owner, CGameObject* target);
protected:
    //계수
    TCHAR       m_Explain[256];
    int                 m_Power; 

    //어떤 작업을 수행핣지 -> Type

    // (공격력)을                  //(3) 올립니다.
    // 
    //


};

