#include "BackObj.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"
#include "Deco.h"

CBackObj::CBackObj()
{
	SetTypeID<CBackObj>();
	m_RenderLayer = ERender_Layer::Back;
}

CBackObj::CBackObj(const CBackObj& Obj):
	CGameObject(Obj)
{
}

CBackObj::~CBackObj()
{
}

bool CBackObj::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1280.f, 800.f);
	SetPivot(0.f, 0.f);

	SetTexture("BattleScene", TEXT("Scene/scene2.bmp"));

	//BackImages.push_back(TEXT("Scene/B.bmp"));
	//BackImages.push_back(TEXT("Scene/C.bmp"));
	//BackImages.push_back(TEXT("Scene/D.bmp"));

	//BackImageSizes.push_back(Vector2(1280, 512));
	//BackImageSizes.push_back(Vector2(1280, 185));
	//BackImageSizes.push_back(Vector2(1280, 244));

	//m_Scene->GetSceneResource()->LoadTexture("BackImg", BackImages);

	//CDeco* BackImgA = CreateObject<CDeco>("A");
	return true;
}

void CBackObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBackObj::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
