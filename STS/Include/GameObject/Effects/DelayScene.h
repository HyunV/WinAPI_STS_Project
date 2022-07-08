#pragma once
#include "../GameObject.h"
class CDelayScene :
    public CGameObject
{
    friend class CScene;
protected:
    CDelayScene();
    virtual ~CDelayScene();
    float m_Time;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};


