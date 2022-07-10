#pragma once
#include "../GameObject.h"
class CDelayRestSound :
    public CGameObject
{
    friend class CScene;
protected:
    CDelayRestSound();
    virtual ~CDelayRestSound();
    float m_Time;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

