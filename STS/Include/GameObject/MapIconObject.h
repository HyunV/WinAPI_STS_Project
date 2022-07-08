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
    bool m_MouseHovered;
    Vector2 m_OwnerPos;
    int m_isStageLevel;
    
    bool m_check;
    float m_Time;
    int m_rand;

    void SetType(EMapIcon_Type Type)
    {
        m_Type = Type;
    }
    void SetStageLevel(int value)
    {
        m_isStageLevel = value;
    }
private:
    void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
    void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
    void StartEvent();

    void CreateMonsters();
    void CreateRest();
    void CreateShop();
    void CreateChest();
    void CreateElite();
    void CreateBoss();
    void RandMonsters(int value);
};

