#include "FrontObj.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"
CFrontObj::CFrontObj()
{
	SetTypeID<CFrontObj>();
	m_RenderLayer = ERender_Layer::Black;
}

CFrontObj::CFrontObj(const CFrontObj& Obj):
	CGameObject(Obj)
{
}

CFrontObj::~CFrontObj()
{
}

bool CFrontObj::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1280.f, 2880.f);
	SetPivot(0.f, 0.f);
	SetTexture("BlackLayer", TEXT("Back.bmp"));
	return true;
}

void CFrontObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CFrontObj::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
