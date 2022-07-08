#pragma once
#include "../GameObject.h"
class CDelayObject :
    public CGameObject
{
    friend class CScene;
protected:
    CDelayObject();
    virtual ~CDelayObject();
    float m_Time;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

