#pragma once

#include "../GameObject.h"

//CCardAbility ��ӹ޾Ƽ�

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
    //���
    TCHAR       m_Explain[256];
    int                 m_Power; 

    //� �۾��� �������� -> Type

    // (���ݷ�)��                  //(3) �ø��ϴ�.
    // 
    //


};

