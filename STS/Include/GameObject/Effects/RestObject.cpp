#include "RestObject.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
CRestObject::CRestObject()
{
	m_RenderLayer = ERender_Layer::Effect;
	m_Time = 0.f;
}

CRestObject::~CRestObject()
{
}

bool CRestObject::Init()
{
	return true;
}

void CRestObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (!m_Scene->GetRestSwitch()) {
		SetActive(false);
		
	}
}
