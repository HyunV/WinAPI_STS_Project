#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
CBullet::CBullet() :
    m_Damage(0.f)
{
    SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& Obj) :
    CGameObject(Obj),
    m_Angle(Obj.m_Angle),
    m_Distance(Obj.m_Distance)
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
    m_MoveSpeed = 200.f;
    m_Distance = 1000.f;
    m_Angle = 180.f;
    //m_Index = 0;

    SetPos(900.f, 100.f);
    SetSize(30.f, 37.f);
    SetPivot(0.5f, 0.5f);

    SetTexture("BloonBullet1", TEXT("Bullet_A.bmp"));
    SetColorKey(255, 0, 255);

    CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

    Circle->SetRadius(25.f);

    Circle->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
    Circle->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);

    //CColliderBox* Box = AddCollider<CColliderBox>("Body");
    //Box->SetExtent(25.f, 25.f);
    //Box->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
    //Box->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);
    return true;
}

void CBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
    Move(m_Angle);
    
    //투사체 색 변경
    //if (m_Index == 0) {
    //  SetTexture("BloonBullet1", TEXT("Bullet_A.bmp"));
    //  SetColorKey(255, 0, 255);
    //}
    //else if (m_Index == 1) {
    //    SetTexture("BloonBullet2", TEXT("Bullet_B.bmp"));
    //    SetColorKey(255, 0, 255);
    //}   
    //else {
    //    SetTexture("BloonBullet3", TEXT("Bullet_C.bmp"));
    //    SetColorKey(255, 0, 255);
    //}

    ///m_Pos.x = m_Pos.x + cosf(DegreeToRadian(m_Angle)) * m_MoveSpeed * DeltaTime;
   // m_Pos.y = m_Pos.y + sinf(DegreeToRadian(m_Angle)) * m_MoveSpeed * DeltaTime;

    m_Distance -= m_MoveSpeed * DeltaTime;

    //m_Index = (m_Index+1)%3;

    if (m_Distance <= 0.f)
        SetActive(false);
}

void CBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CBullet::Render(HDC hDC, float DeltaTime)
{
    CGameObject::Render(hDC, DeltaTime);
   /* Vector2 RenderLT;

    RenderLT = m_Pos - m_Pivot * m_Size;

    Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y,
        (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));*/
}

void CBullet::CollisionBegin(CCollider* Src, CCollider* Dest)
{
    SetActive(false);

    CEffect* Effect = m_Scene->CreateObject<CEffect>("HitEffect");

    Effect->SetPivot(0.5f, 0.5f);
    Effect->SetPos(Src->GetHitPoint());

    Effect->AddAnimation("LeftHitEffect", false, 0.3f);

    Dest->GetOwner()->InflictDamage(m_Damage);
}

void CBullet::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
