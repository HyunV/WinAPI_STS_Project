#pragma once
#include "GameObject.h"
class CCloud :
    public CGameObject
{
    friend class CScene;

protected:
    CCloud();
    virtual ~CCloud();

private:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:

};

