#include "PlayerBullet.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"

CPlayerBullet::CPlayerBullet()  :
    m_Damage(0.f)
{
    SetTypeID<CPlayerBullet>();
}

CPlayerBullet::CPlayerBullet(const CPlayerBullet& Obj)  :
    CGameObject(Obj),
    m_Angle(Obj.m_Angle),
    m_Distance(Obj.m_Distance)
{
}

CPlayerBullet::~CPlayerBullet()
{
}

bool CPlayerBullet::Init()
{
    m_MoveSpeed = 700.f;
    m_Distance = 600.f;
    m_Angle = 180.f;

    SetPos(900.f, 100.f);
    SetSize(40.f, 20.f);
    SetPivot(0.5f, 0.5f);

    SetTexture("Dart", TEXT("Bullet1.bmp"));

    SetColorKey(255, 0, 255);

    CColliderCircle* Circle = AddCollider<CColliderCircle>("BBody");
    Circle->SetRadius(25.f);

    Circle->SetCollisionBeginFunction<CPlayerBullet>(this, &CPlayerBullet::CollisionBegin);
    Circle->SetCollisionEndFunction<CPlayerBullet>(this, &CPlayerBullet::CollisionEnd);


    return true;
}

void CPlayerBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    Move(m_Angle);
   /* m_Pos.x = m_Pos.x + cosf(DegreeToRadian(m_Angle)) * m_MoveSpeed * DeltaTime;
    m_Pos.y = m_Pos.y + sinf(DegreeToRadian(m_Angle)) * m_MoveSpeed * DeltaTime;*/

    m_Distance -= m_MoveSpeed * DeltaTime;

    if (m_Distance <= 0.f)
        SetActive(false);
}

void CPlayerBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CPlayerBullet::Render(HDC hDC, float DeltaTime)
{
    CGameObject::Render(hDC, DeltaTime);
    //Vector2	RenderLT;
    //RenderLT = m_Pos - m_Pivot * m_Size - m_Scene->GetCamera()->GetPos();

    //Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y,
    //    (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));
}

void CPlayerBullet::CollisionBegin(CCollider* Src, CCollider* Dest)
{
    SetActive(false);

    CEffect* Effect = m_Scene->CreateObject<CEffect>("HitEffect");

    //Effect->SetPivot(0.5f, 0.5f);
   // Effect->SetPos(Src->GetHitPoint());

    Effect->AddAnimation("LeftHitEffect", false, 0.3f);

    // Damage Ã³¸®
     Dest->GetOwner()->InflictDamage(m_Damage);
}

void CPlayerBullet::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
