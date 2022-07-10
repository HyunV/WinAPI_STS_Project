#include "TitleWindow.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/BattleScene.h"
#include "Button.h"
#include "ImageWidget2.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/Deco.h"
#include "../GameObject/Cloud.h"
#include "../GameObject/FrontObj.h"
#include "../GameManager.h"

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

	m_Scene->GetSceneResource()->LoadSound("UI", "mouseHovered", false, "02.MouseHovered.wav");
	m_Scene->GetSceneResource()->LoadSound("UI", "UIClick", false, "03.Click.wav");
	m_Scene->GetSceneResource()->LoadSound("UI", "AttackSound", false,
		"04_Attack1.ogg");

	SetSize(1280.f, 800.f);
	//v = (0.f, 0.f);
	//CImageWidget2* Back = CreateWidget<CImageWidget2>("Back");

	CBackObj* Back = m_Scene->CreateObject<CBackObj>("titleBack");
	Back->SetTexture("StartBack", TEXT("Title/titleBack.bmp"));
	Back->SetSize(1280, 720);

	CDeco* BackTower = m_Scene->CreateObject<CDeco>("BackTower");
	BackTower->SetTexture("BackTower", TEXT("Title/titleBack2.bmp"));
	BackTower->SetSize(1280, 792);
	BackTower->SetColorKey(255, 0, 255);
	
	
	//구름
	CCloud* Cloud1 = m_Scene->CreateObject<CCloud>("Cloud1");
	Cloud1->SetTexture("Cloud1", TEXT("Title/Cloud/Cloud1.bmp"));
	Cloud1->SetSize(938, 302);
	Cloud1->SetPos(100, 100);
	Cloud1->SetMoveDirX(-1.f);
	Cloud1->SetColorKey(255, 0, 255);

	CCloud* Cloud2 = m_Scene->CreateObject<CCloud>("Cloud2");
	Cloud2->SetTexture("Cloud2", TEXT("Title/Cloud/Cloud2.bmp"));
	Cloud2->SetSize(930, 190);
	Cloud2->SetPos(-300, 300);
	Cloud2->SetMoveDirX(1.f);
	Cloud2->SetColorKey(255, 0, 255);

	CCloud* Cloud3 = m_Scene->CreateObject<CCloud>("Cloud3");
	Cloud3->SetTexture("Cloud3", TEXT("Title/Cloud/Cloud3.bmp"));
	Cloud3->SetSize(1025, 501);
	Cloud3->SetPos(780, 100);
	Cloud3->SetMoveDirX(-1.f);
	Cloud3->SetColorKey(255, 0, 255);

	CCloud* Cloud4 = m_Scene->CreateObject<CCloud>("Cloud4");
	Cloud4->SetTexture("Cloud4", TEXT("Title/Cloud/Cloud4.bmp"));
	Cloud4->SetSize(1026, 404);
	Cloud4->SetPos(900, 100);
	Cloud4->SetMoveDirX(-3.f);
	Cloud4->SetColorKey(255, 0, 255);

	CCloud* Cloud5 = m_Scene->CreateObject<CCloud>("Cloud5");
	Cloud5->SetTexture("Cloud5", TEXT("Title/Cloud/Cloud5.bmp"));
	Cloud5->SetSize(925, 365);
	Cloud5->SetPos(0, 450);
	Cloud5->SetMoveDirX(1.f);
	Cloud5->SetColorKey(255, 0, 255);

	CCloud* Cloud6 = m_Scene->CreateObject<CCloud>("Cloud6");
	Cloud6->SetTexture("Cloud6", TEXT("Title/Cloud/Cloud6.bmp"));
	Cloud6->SetSize(797, 204);
	Cloud6->SetPos(-800, 400);
	Cloud6->SetMoveDirX(1.f);
	Cloud6->SetColorKey(255, 0, 255);


	CFrontObj* Logo = m_Scene->CreateObject<CFrontObj>("Logo");
	Logo->SetTexture("Logo", TEXT("Title/Logo.bmp"));
	Logo->SetSize(360, 320);
	Logo->SetPivot(0.5, 0.5);
	Logo->SetPos(640, 360);
	Logo->SetColorKey(255, 0, 255);

	
	//Back->SetSize(1280.f, 720.f);


	m_StartButton = CreateWidget<CButton>("StartButton");

	m_StartButton->SetTexture("StartButton", TEXT("Title/startButton.bmp"));
	m_StartButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 60.f));
	m_StartButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 60.f));
	m_StartButton->SetButtonStateData(EButton_State::Click, Vector2(200.f, 0.f), Vector2(400.f, 60.f));
	//m_StartButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));
	m_StartButton->SetColorKey(255, 0, 255);
	m_StartButton->SetPos(50.f, 500.f);
	m_StartButton->SetZOrder(1);
	m_StartButton->SetCallback<CTitleWindow>(EButton_Sound_State::Click,
		this, &CTitleWindow::StartButtonCallback);
	m_StartButton->SetSound(EButton_Sound_State::MouseHovered, "mouseHovered");
	m_StartButton->SetSound(EButton_Sound_State::Click, "UIClick");

	m_EndButton = CreateWidget<CButton>("EndButton");

	m_EndButton->SetTexture("EndButton", TEXT("Title/endButton.bmp"));
	m_EndButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 60.f));
	m_EndButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 60.f));
	m_EndButton->SetButtonStateData(EButton_State::Click, Vector2(200.f, 0.f), Vector2(400.f, 60.f));
	m_EndButton->SetColorKey(255, 0, 255);
	m_EndButton->SetPos(50.f, 580.f);
	m_EndButton->SetZOrder(1);
	m_EndButton->SetCallback<CTitleWindow>(EButton_Sound_State::Click,
		this, &CTitleWindow::EndButtonCallback);
	m_EndButton->SetSound(EButton_Sound_State::MouseHovered, "mouseHovered");
	m_EndButton->SetSound(EButton_Sound_State::Click, "UIClick");


	m_CharacterButton = CreateWidget<CButton>("CharacterButton");
	m_CharacterButton->SetTexture("CharacterButton", TEXT("ironcladButton.bmp"));
	m_CharacterButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(120.f, 120.f));
	m_CharacterButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(120.f, 120.f));
	m_CharacterButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(120.f, 120.f));
	m_CharacterButton->SetColorKey(255, 0, 255);
	m_CharacterButton->SetPos(580.f, 520.f);
	m_CharacterButton->SetZOrder(2);

	m_CharacterButton->SetCallback<CTitleWindow>(EButton_Sound_State::Click,
		this, &CTitleWindow::CharacterButtonCallback);
	m_CharacterButton->SetEnable(false);

	m_CharacterButton->SetSound(EButton_Sound_State::MouseHovered, "mouseHovered");
	m_CharacterButton->SetSound(EButton_Sound_State::Click, "AttackSound");

	m_CharacterBackImage = CreateWidget<CImageWidget2>("ironcladPortrait");
	m_CharacterBackImage->SetTexture("ironcladPortrait", TEXT("ironcladPortrait.bmp"));
	m_CharacterBackImage->SetSize(1280.f, 800.f);
	m_CharacterBackImage->SetZOrder(1);
	m_CharacterBackImage->SetEnable(false);


	m_SelectCharacter = CreateWidget<CText>("SelectCharacterText");
	m_SelectCharacter->SetFont("UI");
	m_SelectCharacter->SetText(TEXT("캐릭터를 선택하십시오"));
	m_SelectCharacter->SetPos(640.f, 650.f);
	m_SelectCharacter->SetTextColor(254, 245, 225);
	m_SelectCharacter->EnableShadow(true);
	m_SelectCharacter->SetShadowOffset(1.f, 1.f);
	m_SelectCharacter->SetZOrder(2);
	m_SelectCharacter->SetEnable(false);

	//캐릭터 설명 창
	m_CharacterText = CreateWidget<CText>("IroncladText");
	m_CharacterText->SetFont("TurnMessageFont");
	m_CharacterText->SetText(TEXT("아이언클래드"));
	m_CharacterText->SetPos(324.f, 174.f);
	m_CharacterText->SetTextColor(239, 200, 81);
	m_CharacterText->EnableShadow(true);
	m_CharacterText->SetShadowOffset(1.f, 1.f);
	m_CharacterText->SetZOrder(2);
	m_CharacterText->SetEnable(false);

	m_CharacterText2 = CreateWidget<CText>("ExplainText2");
	m_CharacterText2->SetFont("PlayerExplainFont");
	m_CharacterText2->SetText(TEXT("아이언클래드의 살아남은 병사입니다."));
	m_CharacterText2->SetPos(374.f, 274.f);
	m_CharacterText2->SetTextColor(255, 255, 255);
	m_CharacterText2->EnableShadow(true);
	m_CharacterText2->SetShadowOffset(1.f, 1.f);
	m_CharacterText2->SetZOrder(2);
	m_CharacterText2->SetEnable(false);

	m_CharacterText3 = CreateWidget<CText>("ExplainText3");
	m_CharacterText3->SetFont("PlayerExplainFont");
	m_CharacterText3->SetText(TEXT("악마의 힘을 사용하기 위해 영혼을 팔았습니다."));
	m_CharacterText3->SetPos(420.f, 310.f);
	m_CharacterText3->SetTextColor(255, 255, 255);
	m_CharacterText3->EnableShadow(true);
	m_CharacterText3->SetShadowOffset(1.f, 1.f);
	m_CharacterText3->SetZOrder(2);
	m_CharacterText3->SetEnable(false);

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
	m_BackButton->SetSound(EButton_Sound_State::MouseHovered, "mouseHovered");
	m_BackButton->SetSound(EButton_Sound_State::Click, "UIClick");

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
	m_ConfirmButton->SetSound(EButton_Sound_State::MouseHovered, "mouseHovered");
	m_ConfirmButton->SetSound(EButton_Sound_State::Click, "UIClick");

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
	m_SelectCharacter->SetEnable(true);

	m_BackButton->SetEnable(true);
	m_BackButtonText->SetEnable(true);

	m_StartButton->SetEnable(false);
	m_EndButton->SetEnable(false);
}

void CTitleWindow::EndButtonCallback()
{
	CGameManager::GetInst()->Exit();
}

void CTitleWindow::CharacterButtonCallback()
{
	m_CharacterBackImage->SetEnable(true);
	m_SelectCharacter->SetEnable(false);

	m_ConfirmButton->SetEnable(true);
	m_ConfirmButtonText->SetEnable(true);

	m_CharacterText->SetEnable(true);
	m_CharacterText2->SetEnable(true);
	m_CharacterText3->SetEnable(true);
}

void CTitleWindow::BackCallBack()
{
	m_CharacterBackImage->SetEnable(false);
	m_CharacterButton->SetEnable(false);
	m_BackButton->SetEnable(false);
	m_BackButtonText->SetEnable(false);
	m_ConfirmButton->SetEnable(false);
	m_ConfirmButtonText->SetEnable(false);
	m_SelectCharacter->SetEnable(false);
	m_CharacterText->SetEnable(false);
	m_CharacterText2->SetEnable(false);
	m_CharacterText3->SetEnable(false);

	m_StartButton->SetEnable(true);
	m_EndButton->SetEnable(true);
}

void CTitleWindow::ConfirmCallback()
{
	CSceneManager::GetInst()->CreateScene<CBattleScene>();
}
