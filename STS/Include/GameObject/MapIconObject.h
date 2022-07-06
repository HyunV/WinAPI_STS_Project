#pragma once
#include "GameObject.h"
class CMapIconObject :
    public CGameObject
{
    friend class CScene;
protected:
    CMapIconObject();
    virtual ~CMapIconObject();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    EMapIcon_Type m_Type;

    void SetType(EMapIcon_Type Type)
    {
        m_Type = Type;
    }
private:
    void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
    void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
};

