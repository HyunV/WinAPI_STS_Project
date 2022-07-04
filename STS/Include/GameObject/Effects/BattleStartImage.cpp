#include "BattleStartImage.h"

CBattleStartImage::CBattleStartImage()
{
	m_RenderLayer = ERender_Layer::Hand;
}

CBattleStartImage::~CBattleStartImage()
{
}

bool CBattleStartImage::Init()
{
	SetPos(640.f, 300.f);
	SetPivot(0.5f, 0.5f);
	SetSize(230.f,200.f);
	SetTexture("BattleStartLogo", TEXT("Effects/test.bmp"));
	SetColorKey(255, 0, 255);
	
	return true;
}

void CBattleStartImage::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_Pos.x--;

}
