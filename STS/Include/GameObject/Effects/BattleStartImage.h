#pragma once
#include "../GameObject.h"
class CBattleStartImage :
    public CGameObject
{
    friend class CScene;

protected:
    CBattleStartImage();
    virtual ~CBattleStartImage();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

