#include "DelayRestSound.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"

CDelayRestSound::CDelayRestSound()
{
    m_Time = 0.f;
}

CDelayRestSound::~CDelayRestSound()
{
}

bool CDelayRestSound::Init()
{
    return true;
}

void CDelayRestSound::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (GetActive()) {
		m_Time += DeltaTime;
		if (m_Time >= 3.0f) {
			m_Scene->GetSceneResource()->SoundResume("StageBGM");
			SetActive(false);
			
		}
	}
}
