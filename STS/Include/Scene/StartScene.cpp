#include "StartScene.h"
#include "Camera.h"
#include "../Widget/TitleWindow.h"
CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	GetCamera()->SetResolution(1280.f, 800.f);
	GetCamera()->SetWorldResolution(1280.f, 800.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CreateWidgetWindow<CTitleWindow>("TitleWindow");
	return true;
}
