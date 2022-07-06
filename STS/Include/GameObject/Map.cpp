#include "Map.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/ImageWidget2.h"
#include "../Scene/Scene.h"
#include "MapIconObject.h"
CMap::CMap()
{
	SetTypeID<CMap>();
	m_RenderLayer = ERender_Layer::Black;
}

CMap::CMap(const CMap& Obj)	:
	CGameObject(Obj)
{

}

CMap::~CMap()
{
}

bool CMap::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1280.f, 2880.f);
	SetPivot(0.f, 0.f);
	SetTexture("MapLayer", TEXT("map.bmp"));

	m_Scroll = CreateWidgetComponent<CImageWidget2>("Scroll");
	m_Scroll->GetWidget<CImageWidget2>()->SetTexture("Scroll", TEXT("Map/scroll2.bmp"));
	m_Scroll->GetWidget<CImageWidget2>()->SetSize(256, 400);
	m_Scroll->SetPos(300, 200);
	m_Scroll->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);

	//CMapIconObject* Icon = m_Scene->CreateObject<CMapIconObject>("icon1");
	for (int i = 0; i < 10; i++)
	{
		CMapIconObject* Icon = m_Scene->CreateObject<CMapIconObject>("icon1");
		Icon->SetPos(640, 2300 + (i * (-200)));
	}
	return true;
}

void CMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	Vector2 v = m_Scene->GetCameraObj()->GetPos();
	m_Scroll->SetPos(v.x+390.f, v.y-100.f);
}

void CMap::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
