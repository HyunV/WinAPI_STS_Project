#pragma once
#include "../GameObject.h"
class CRestObject :
    public CGameObject
{
    friend class CScene;
protected:
    CRestObject();
    virtual ~CRestObject();
    float m_Time;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

