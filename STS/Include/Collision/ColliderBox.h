#pragma once
//타입1. 박스 충돌
//(타입2. circle 충돌)
#include "Collider.h"
class CColliderBox :
    public CCollider
{
    friend class CGameObject;

protected:
    CColliderBox();
    CColliderBox(const CColliderBox& collider);
    virtual ~CColliderBox();

protected:
    float m_Width;
    float m_Height;
    BoxInfo m_Info;

public:
    BoxInfo GetInfo() const
    {
        return m_Info;

    }
    
    void SetExtent(float Width, float Height) //박스 가로 세로의 크기를 설정
    {
        m_Width = Width;
        m_Height = Height;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual bool Collision(CCollider* Dest);
    virtual bool CollisionMouse(const Vector2& Mouse);
};

