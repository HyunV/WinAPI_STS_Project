#include "TitleWindow.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/BattleScene.h"
#include "Button.h"
#include "ImageWidget2.h"

CTitleWindow::CTitleWindow()
{
	
}

CTitleWindow::~CTitleWindow()
{
	
}

bool CTitleWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(1280.f, 800.f);

	CImageWidget2* Back = CreateWidget<CImageWidget2>("Back");

	Back->SetTexture("StartBack", TEXT("Back.bmp"));

	Back->SetSize(1280.f, 720.f);


	m_StartButton = CreateWidget<CButton>("StartButton");

	m_StartButton->SetTexture("StartButton", TEXT("StartButton.bmp"));
	m_StartButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	m_StartButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	m_StartButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 100.f));
	m_StartButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));
	
	m_StartButton->SetPos(540.f, 150.f);
	m_StartButton->SetZOrder(1);

	m_StartButton->SetCallback<CTitleWindow>(EButton_Sound_State::Click,
		this, &CTitleWindow::StartButtonCallback);

	m_CharacterButton = CreateWidget<CButton>("CharacterButton");
	m_CharacterButton->SetTexture("CharacterButton", TEXT("ironcladButton.bmp"));
	m_CharacterButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
	m_CharacterButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
	m_CharacterButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
	m_CharacterButton->SetColorKey(255, 0, 255);
	m_CharacterButton->SetPos(340.f, 350.f);
	m_CharacterButton->SetZOrder(2);

	m_CharacterButton->SetCallback<CTitleWindow>(EButton_Sound_State::Click,
		this, &CTitleWindow::CharacterButtonCallback);
	m_CharacterButton->SetEnable(false);

	m_CharacterBackImage = CreateWidget<CImageWidget2>("ironcladPortrait");
	m_CharacterBackImage->SetTexture("ironcladPortrait", TEXT("ironcladPortrait.bmp"));
	m_CharacterBackImage->SetSize(1280.f, 800.f);
	m_CharacterBackImage->SetZOrder(1);
	m_CharacterBackImage->SetEnable(false);

	//히든 버튼

	m_BackButton = CreateWidget<CButton>("BackButton");
	m_BackButton->SetTexture("BackButton", TEXT("TopPanel/cancelButton.bmp"));
	m_BackButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(256.f, 128.f));
	m_BackButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(256.f, 0.f), Vector2(512.f, 128.f));
	m_BackButton->SetButtonStateData(EButton_State::Click, Vector2(256.f, 0.f), Vector2(512.f, 128.f));
	m_BackButton->SetPos(0.f, 600.f);
	m_BackButton->SetColorKey(255, 0, 255);
	m_BackButton->SetCallback<CTitleWindow>(EButton_Sound_State::Click,
		this, &CTitleWindow::BackCallBack);
	m_BackButton->SetZOrder(2);
	m_BackButton->SetEnable(false);

	m_BackButtonText = CreateWidget<CText>("BackButtonText");
	m_BackButtonText->SetFont("UI");
	m_BackButtonText->SetText(TEXT("돌아가기"));
	m_BackButtonText->SetPos(50.f, 620.f);
	m_BackButtonText->SetTextColor(255, 255, 219);
	m_BackButtonText->EnableShadow(true);
	m_BackButtonText->SetZOrder(2);
	m_BackButtonText->SetShadowOffset(1.f, 1.f);
	m_BackButtonText->SetEnable(false);

	m_ConfirmButton = CreateWidget<CButton>("ConfirmButton");
	m_ConfirmButton->SetTexture("ConfirmButton", TEXT("TopPanel/confirmButton.bmp"));
	m_ConfirmButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(256.f, 128.f));
	m_ConfirmButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(256.f, 0.f), Vector2(512.f, 128.f));
	m_ConfirmButton->SetButtonStateData(EButton_State::Click, Vector2(256.f, 0.f), Vector2(512.f, 128.f));
	m_ConfirmButton->SetPos(1024.f, 600.f);
	m_ConfirmButton->SetColorKey(255, 0, 255);
	m_ConfirmButton->SetZOrder(2);
	m_ConfirmButton->SetCallback<CTitleWindow>(EButton_Sound_State::Click,
		this, &CTitleWindow::ConfirmCallback);
	m_ConfirmButton->SetEnable(false);

	m_ConfirmButtonText = CreateWidget<CText>("ConfirmButtonText");
	m_ConfirmButtonText->SetFont("UI");
	m_ConfirmButtonText->SetText(TEXT("출정"));
	m_ConfirmButtonText->SetPos(1224.f, 620.f);
	m_ConfirmButtonText->SetTextColor(255, 255, 219);
	m_ConfirmButtonText->EnableShadow(true);
	m_ConfirmButtonText->SetShadowOffset(1.f, 1.f);
	m_ConfirmButtonText->SetZOrder(2);
	m_ConfirmButtonText->SetEnable(false);

	return true;
}

void CTitleWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CTitleWindow::StartButtonCallback()
{
	m_CharacterButton->SetEnable(true);

	m_BackButton->SetEnable(true);
	m_BackButtonText->SetEnable(true);
}

void CTitleWindow::CharacterButtonCallback()
{
	m_CharacterBackImage->SetEnable(true);

	m_ConfirmButton->SetEnable(true);
	m_ConfirmButtonText->SetEnable(true);
}

void CTitleWindow::BackCallBack()
{
	m_CharacterBackImage->SetEnable(false);
	m_CharacterButton->SetEnable(false);
	m_BackButton->SetEnable(false);
	m_BackButtonText->SetEnable(false);
}

void CTitleWindow::ConfirmCallback()
{
	CSceneManager::GetInst()->CreateScene<CBattleScene>();
}
