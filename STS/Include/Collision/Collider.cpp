#include "Collider.h"
#include "CollisionManager.h"
#include "../GameObject/CardManager.h"
#include "../Input.h"

CCollider::CCollider()  :
    m_Scene(nullptr),
    m_Owner(nullptr),
    m_Profile(nullptr),
    m_MouseCollision(false),
    m_Bottom(0.f),
    m_Check(false)
{
}

CCollider::CCollider(const CCollider& collider) :
    CRef(collider),
    m_ColliderType(collider.m_ColliderType),
    m_Offset(collider.m_Offset),
    m_Scene(nullptr),
    m_Owner(nullptr),
    m_CardOwner(nullptr),
    m_Profile(collider.m_Profile),
    m_MouseCollision(false),
    m_Bottom(0.f),
    m_Check(false)
{
}

CCollider::~CCollider()
{
    auto	iter = m_CollisionList.begin();
    auto	iterEnd = m_CollisionList.end();

    for (; iter != iterEnd; ++iter)
    {
        (*iter)->DeleteCollisionList(this);
    }
}

void CCollider::SetCollisionEnable(bool Enable)
{
    if (m_Profile)
    {
        m_Profile->Enable = Enable;
    }
    
}

void CCollider::SetCollisionProfile(const std::string& Name)
{
    m_Profile = CCollisionManager::GetInst()->FindProfile(Name);
}

void CCollider::AddCollisionList(CCollider* Collider)
{
    //A와 B가 충돌했다면 A의 리스트에는 B가 들어가고 B의 리스트에는 A가 들어가 있을 것이다.
    //고로 누군가 제거되면 반대편에도 알려야된다.
    m_CollisionList.push_back(Collider);
    
}

bool CCollider::CheckCollisionList(CCollider* Collider)
{
    auto	iter = m_CollisionList.begin();
    auto	iterEnd = m_CollisionList.end();

    for (; iter != iterEnd; ++iter)
    {
        if (*iter == Collider)
            return true;
    }

    return false;
}

void CCollider::DeleteCollisionList(CCollider* Collider)
{
    auto	iter = m_CollisionList.begin();
    auto	iterEnd = m_CollisionList.end();

    for (; iter != iterEnd; ++iter)
    {
        if (*iter == Collider)
        {
            m_CollisionList.erase(iter); //찾은 콜라이더를 제거
            return;
        }
    }
}

void CCollider::ClearCollisionList()
{
    auto	iter = m_CollisionList.begin();
    auto	iterEnd = m_CollisionList.end();

    for (; iter != iterEnd; ++iter)
    {
        (*iter)->DeleteCollisionList(this); //전부다 제거
    }

    m_CollisionList.clear();
}

void CCollider::CallCollisionBegin(CCollider* Dest)
{
        if (m_CollisionBegin)
            m_CollisionBegin(this, Dest); //src, Dest 얘네 둘 충돌이 시작했다
}

void CCollider::CallCollisionEnd(CCollider* Dest)
{
    if (m_CollisionEnd)
        m_CollisionEnd(this, Dest);
}

void CCollider::CallMouseCollisionBegin(const Vector2& MousePos)
{
    if (CInput::GetInst()->GetMouseLPush())
    {
        return;
    }
    if (m_MouseCollisionBegin)
        m_MouseCollisionBegin(this, MousePos);   
}

void CCollider::CallMouseCollisionEnd(const Vector2& MousePos)
{
    if (m_MouseCollisionEnd) {
        m_MouseCollisionEnd(this, MousePos);
    }
}

bool CCollider::Init()
{
    m_Profile = CCollisionManager::GetInst()->FindProfile("Default"); //충돌체는 디폴트로 하나 들고있게 한다.

    return true;
}

void CCollider::Update(float DeltaTime)
{
}

void CCollider::PostUpdate(float DeltaTime)
{
}

void CCollider::Render(HDC hDC, float DeltaTime)
{
}

bool CCollider::Collision(CCollider* Dest)
{
    return false;
}

bool CCollider::CollisionMouse(const Vector2& Mouse)
{
    return false;
}
