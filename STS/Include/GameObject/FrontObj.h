#pragma once
#include "GameObject.h"
class CFrontObj :
    public CGameObject
{
    friend class CScene;

protected:
    CFrontObj();
    virtual ~CFrontObj();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
};

