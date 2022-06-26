#include "StartScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"
#include "../Widget/TopPanel.h"


CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	GetCamera()->SetResolution(1920.f, 1200.f);
	GetCamera()->SetWorldResolution(1920.f, 1200.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	//CreateWidgetWindow<CStartWindow>("StartWindow");
	CreateWidgetWindow<CTopPanel>("TopPanel");

	return true;
}
