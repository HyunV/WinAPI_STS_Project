#pragma once
#include "../GameObject.h"
class CGameOver :
    public CGameObject
{
    friend class CScene;
protected:
    CGameOver();
    virtual ~CGameOver();
    float m_Time;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

