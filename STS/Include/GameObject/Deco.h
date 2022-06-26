#pragma once
#include "GameObject.h"
class CDeco :
    public CGameObject
{
    friend class CScene;

protected:
    CDeco();
    virtual ~CDeco();

protected:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
};

