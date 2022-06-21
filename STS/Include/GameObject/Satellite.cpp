#include "Satellite.h"

CSatellite::CSatellite()
{
	SetTypeID<CSatellite>();
}

CSatellite::CSatellite(const CSatellite& Obj) :
	CGameObject(Obj)
{
}

CSatellite::~CSatellite()
{
}

bool CSatellite::Init()
{
	SetPos(900.f, 100.f);
	SetSize(30.f, 30.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("Satellite", TEXT("Bullet2.bmp"));
	SetColorKey(255, 0, 255);


	return true;
}

void CSatellite::Update(float DeltaTime)
{
}

void CSatellite::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
	/*Vector2	RenderLT;

	RenderLT = m_Pos - m_Pivot * m_Size;

	Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y, 
		(int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));*/
}
