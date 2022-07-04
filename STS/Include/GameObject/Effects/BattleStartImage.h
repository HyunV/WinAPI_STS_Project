#pragma once
#include "../GameObject.h"
class CBattleStartImage :
    public CGameObject
{
    friend class CScene;

protected:
    CBattleStartImage();
    virtual ~CBattleStartImage();
    float m_Time;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

