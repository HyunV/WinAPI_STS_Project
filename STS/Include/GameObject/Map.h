#pragma once
#include "GameObject.h"
class CMap :
    public CGameObject
{
    friend class CScene;

protected:
    CMap();
    CMap(const CMap& Obj);
    virtual ~CMap();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);

private:
    CSharedPtr<class CWidgetComponent> m_Scroll;
public:
    vector<class CMapIconObject*> m_Stage;
};

