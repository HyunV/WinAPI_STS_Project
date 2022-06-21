#include "MyMonster.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CMyMonster::CMyMonster()
{
	SetTypeID<CMyMonster>();
}

CMyMonster::CMyMonster(const CMyMonster& Obj)
{
}

CMyMonster::~CMyMonster()
{
}

bool CMyMonster::Init()
{
	CGameObject::Init();

	SetPos(1000.f, 450.f);
	SetSize(250.f, 250.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Puppet", TEXT("Monster/puppet.bmp"));

	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(250.f, 250.f);
	Box->SetCollisionProfile("Monster");

	Box->SetMouseCollisionBeginFunction<CMyMonster>(this, &CMyMonster::CollisionMouseBegin);
	Box->SetMouseCollisionEndFunction<CMyMonster>(this, &CMyMonster::CollisionMouseEnd);
	
	return true;
}

void CMyMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);


}

void CMyMonster::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CMyMonster::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}

float CMyMonster::InflictDamage(float Damage)
{
	return 0.0f;
}

void CMyMonster::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
}

void CMyMonster::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}
