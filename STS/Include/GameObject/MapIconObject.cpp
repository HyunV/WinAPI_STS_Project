#include "MapIconObject.h"

CMapIconObject::CMapIconObject()
{
	SetTypeID<CMapIconObject>();
	m_RenderLayer = ERender_Layer::MapIcon;
}

CMapIconObject::~CMapIconObject()
{

}

bool CMapIconObject::Init()
{


	SetPos(640, 2300);
	SetPivot(0.5f, 0.5f);

	SetTexture("MapIcon", TEXT("Map/monster.bmp"));
	SetColorKey(255, 0, 255);
	SetSize(64.f,64.f);

	return true;
}

void CMapIconObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMapIconObject::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CMapIconObject::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
}

void CMapIconObject::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
}
