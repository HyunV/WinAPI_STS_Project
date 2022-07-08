#include "DelayObject.h"
#include "../../Scene/Scene.h"
CDelayObject::CDelayObject()
{
	m_RenderLayer = ERender_Layer::Black;
	m_Time = 0.f;
}

CDelayObject::~CDelayObject()
{
}

bool CDelayObject::Init()
{
	return true;
}

void CDelayObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 1.0f) {
			SetActive(false);

			m_Scene->SetMapSwitch(true);
			m_Scene->SetStageIcon(true);
			m_Scene->GetCameraObj()->SetAutoCamera();
			m_Scene->GameSet();
		}
	}
}
