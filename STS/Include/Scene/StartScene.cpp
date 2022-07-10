#include "StartScene.h"
#include "Camera.h"
#include "../Widget/TitleWindow.h"
#include "SceneResource.h"
CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	GetSceneResource()->LoadSound("BGM", "TitleBGM", true, "01.Title.ogg");
	GetSceneResource()->SoundPlay("TitleBGM");

	GetCamera()->SetResolution(1280.f, 800.f);
	GetCamera()->SetWorldResolution(1280.f, 800.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);
	
	CreateWidgetWindow<CTitleWindow>("TitleWindow");
	return true;
}
