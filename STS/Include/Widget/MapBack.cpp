#include "MapBack.h"

#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/BattleScene.h"

#include "../Input.h"
#include "ImageWidget2.h"
CMapBack::CMapBack()
{
}

CMapBack::~CMapBack()
{
}

bool CMapBack::Init()
{
	return true;

	SetSize(1280.f, 1440.f);

	CImageWidget2* Back = CreateWidget<CImageWidget2>("Backk");
	Back->SetTexture("BackImg", TEXT("Back.bmp"));
	Back->SetSize(1280, 2880);
}

void CMapBack::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}
