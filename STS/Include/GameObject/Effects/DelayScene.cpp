#include "DelayScene.h"
#include "../../Scene/Scene.h"

CDelayScene::CDelayScene()
{
	m_RenderLayer = ERender_Layer::Black;
	m_Time = 0.f;
}

CDelayScene::~CDelayScene()
{
}

bool CDelayScene::Init()
{
	return true;
}

void CDelayScene::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 3.0f) {
			SetActive(false);
			m_Scene->SetClearSwitch(true);
		}
	}
}
