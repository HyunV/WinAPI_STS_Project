#pragma once
#include "../GameObject.h"
class CPlayerHitEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CPlayerHitEffect();
    virtual ~CPlayerHitEffect();
    float m_Time;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

