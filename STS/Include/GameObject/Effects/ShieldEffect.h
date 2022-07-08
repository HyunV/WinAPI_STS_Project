#pragma once
#include "../GameObject.h"
class CShieldEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CShieldEffect();
    virtual ~CShieldEffect();
    float m_Time;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

