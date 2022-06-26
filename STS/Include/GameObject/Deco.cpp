#include "Deco.h"

CDeco::CDeco()
{
    SetTypeID<CDeco>();
    m_RenderLayer = ERender_Layer::Deco;
}

CDeco::~CDeco()
{
}

bool CDeco::Init()
{
    return true;
}

void CDeco::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
}

void CDeco::Render(HDC hDC, float DeltaTime)
{
    CGameObject::Render(hDC, DeltaTime);
}
