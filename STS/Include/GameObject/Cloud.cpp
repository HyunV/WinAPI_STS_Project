#include "Cloud.h"
#include "../Scene/Scene.h"

CCloud::CCloud()
{
	m_RenderLayer = ERender_Layer::Effect;
}

CCloud::~CCloud()
{
}

bool CCloud::Init()
{
	m_MoveDirX = 1.f;
	m_MoveSpeed = 10.f;
	return true;
}

void CCloud::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	MoveX(m_MoveDirX);
}
