#include "ColliderBox.h"
#include "../GameObject/GameObject.h" //오너정보 얻기 위해 인클루드
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderCircle.h"

CColliderBox::CColliderBox()    :
    m_Width(10.f),
    m_Height(10.f)
{
    SetTypeID<CColliderBox>();

    m_ColliderType = ECollider_Type::Box;
}

CColliderBox::CColliderBox(const CColliderBox& collider)    :
    CCollider(collider),
    m_Width(collider.m_Width),
    m_Height(collider.m_Height),
    m_Info(collider.m_Info)
{
}

CColliderBox::~CColliderBox()
{
}

bool CColliderBox::Init()
{
    if (!CCollider::Init())
        return false;

    return true;
}

void CColliderBox::Update(float DeltaTime)
{
    CCollider::Update(DeltaTime);
}

void CColliderBox::PostUpdate(float DeltaTime)
{
    CCollider::PostUpdate(DeltaTime);

    //여기서 위치계산 하고 상자의 위치를 만들어준다
    Vector2	Pos = m_Owner->GetPos(); //오너의 위치를 얻어온다
    Vector2	Size(m_Width, m_Height);

    m_Info.LT = Pos + m_Offset - Size / 2.f; //오프셋과 떨어진 충돌체 - (사이즈 / 2)[중간점 기준 반반] 하면 해당 충돌체의 위치
    m_Info.RB = Pos + m_Offset + Size / 2.f;

    m_Bottom = m_Info.RB.y;
}

void CColliderBox::Render(HDC hDC, float DeltaTime)
{
#ifdef _DEBUG

    HBRUSH	Brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Green);

    if (!m_CollisionList.empty() || m_MouseCollision) //리스트가 비어있지 않으면(충돌중이라는 의미)
        Brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Red);

    CCamera* Camera = m_Scene->GetCamera();

    RECT	RenderRC;

    RenderRC.left = (long)(m_Info.LT.x - Camera->GetPos().x);
    RenderRC.top = (long)(m_Info.LT.y - Camera->GetPos().y);
    RenderRC.right = (long)(m_Info.RB.x - Camera->GetPos().x);
    RenderRC.bottom = (long)(m_Info.RB.y - Camera->GetPos().y);

    FrameRect(hDC, &RenderRC, Brush);

#endif // _DEBUG
}

bool CColliderBox::Collision(CCollider* Dest) //어떤 물체끼리 부딫혔는지 체크
{
    switch (Dest->GetColliderType())
    {
    case ECollider_Type::Box:
        return CCollisionManager::GetInst()->CollisionBoxToBox(m_HitPoint, this, (CColliderBox*)Dest);
    case ECollider_Type::Circle:
        return CCollisionManager::GetInst()->CollisionBoxToCircle(m_HitPoint, this, (CColliderCircle*)Dest);
    }

    return false;
}

bool CColliderBox::CollisionMouse(const Vector2& Mouse)
{
    return CCollisionManager::GetInst()->CollisionPointToBox(m_HitPoint, Mouse, m_Info);
}
