#include "StartWindow.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ImageWidget2.h"
#include "Text.h"
#include "Number.h"
#include "../GameManager.h"

#include "ImageWidget.h"

CStartWindow::CStartWindow()
{
}

CStartWindow::~CStartWindow()
{
}

bool CStartWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	m_hWnd = CGameManager::GetInst()->GetWindowHandle();

	m_Scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"1Up.wav");
	m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Stun.wav");

	SetSize(1280.f, 720.f);

	 CImageWidget2* Back = CreateWidget<CImageWidget2>("Back");

	 Back->SetTexture("StartBack", TEXT("GameBack.bmp"));

	 Back->SetSize(1280.f, 720.f);

	CButton* StartButton = CreateWidget<CButton>("StartButton");

	StartButton->SetTexture("StartButton", TEXT("StartButton.bmp"));
	StartButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	StartButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	StartButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 100.f));
	StartButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	StartButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	StartButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	StartButton->SetPos(540.f, 150.f);
	StartButton->SetZOrder(1);

	StartButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::StartButtonCallback);

	CButton* EditButton = CreateWidget<CButton>("EditButton");

	EditButton->SetTexture("EditButton", TEXT("TopPanel/base1.bmp"));
	EditButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(77.f, 77.f));
	EditButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(77.f, 0.f), Vector2(154.f, 77.f));
	//EditButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 100.f));
	//EditButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	//EditButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	//EditButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	EditButton->SetPos(540.f, 270.f);
	EditButton->SetZOrder(1);

	//EditButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
	//	this, &CStartWindow::EditButtonCallback);


	CButton* SettingButton = CreateWidget<CButton>("SettingButton");
	SettingButton->SetTexture("SettingButton", TEXT("TopPanel/settings.bmp"));
	SettingButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
	SettingButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
	SettingButton->SetButtonStateData(EButton_State::Click, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
	SettingButton->SetPos(1231.f, 3.f);
	SettingButton->SetColorKey(255, 0, 255);
	SettingButton->SetZOrder(1);


	CButton* EndButton = CreateWidget<CButton>("EndButton");

	EndButton->SetTexture("EndButton", TEXT("EditButton.bmp"));
	EndButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	EndButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	EndButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 100.f));
	EndButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	EndButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	EndButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	EndButton->SetPos(540.f, 390.f);
	EndButton->SetZOrder(1);
	EndButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::EndButtonCallback);
	

	CImageWidget* ImageWidget = CreateWidget<CImageWidget>("ImageWidget");

	ImageWidget->SetTexture("ImageWidget", TEXT("check.bmp"));
	ImageWidget->SetColorKey(255, 0, 255);
	ImageWidget->SetImageStateData(ECheckBox_State::Enable, Vector2(100, 0), Vector2(200, 100));
	ImageWidget->SetImageStateData(ECheckBox_State::Disable, Vector2(0, 0), Vector2(100, 100));
	ImageWidget->SetPos(100.f, 100.f);
	ImageWidget->SetZOrder(1);
	//ImageWidget->SetCallback<CStartWindow>(EButton_State::Click,
	//	this, &CStartWindow::CheckImageCallback);

	//�ؽ�Ʈ ���
	m_Text = CreateWidget<CText>("Text");

	m_Text->SetText(TEXT("�ؽ�Ʈ ���!!"));
	m_Text->SetPos(200.f, 50.f);
	m_Text->SetTextColor(255, 0, 0);

	m_Text->EnableShadow(true);
	m_Text->SetShadowOffset(5.f, 5.f);

	m_TextTime = 0.f;

	memset(m_AddText, 0, sizeof(TCHAR) * 32);
	lstrcpy(m_AddText, TEXT("�濰��"));
	m_AddCount = 0;

	m_Hour = CreateWidget<CNumber>("Hour");
	CImageWidget2* Colon = CreateWidget<CImageWidget2>("Colon");
	m_Minute = CreateWidget<CNumber>("Minute");
	m_Second = CreateWidget<CNumber>("Second");

	Colon->SetTexture("Colon", TEXT("Number/Colon.bmp"));
	Colon->SetSize(29.f, 48.f);
	Colon->SetPos(558.f, 100.f);
	Colon->SetColorKey(255, 255, 255);

	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
		wsprintf(FileName, TEXT("Number/%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	m_Hour->SetTexture("Number", vecFileName);
	m_Minute->SetTexture("Number", vecFileName);
	m_Second->SetTexture("Number", vecFileName);

	m_Hour->SetColorKey(255, 255, 255);
	m_Minute->SetColorKey(255, 255, 255);
	m_Second->SetColorKey(255, 255, 255);


	m_Hour->SetSize(29.f, 48.f);
	m_Hour->SetPos(500.f, 100.f);

	m_Minute->SetSize(29.f, 48.f);
	m_Minute->SetPos(587.f, 100.f);

	m_Second->SetSize(29.f, 48.f);
	m_Second->SetPos(655.f, 100.f);

	m_FPSText = CreateWidget<CText>("Text");

	m_FPSText->SetText(TEXT("FPS"));
	m_FPSText->SetPos(900.f, 50.f);
	m_FPSText->SetTextColor(255, 0, 0);

	m_FPSText->EnableShadow(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);

	m_MousePosTextX = CreateWidget<CText>("TextX");
	m_MousePosTextX->SetText(TEXT("MouseX"));
	m_MousePosTextX->SetPos(900.f, 100.f);

	m_MousePosTextY = CreateWidget<CText>("TextY");
	m_MousePosTextY->SetText(TEXT("MouseY"));
	m_MousePosTextY->SetPos(1000.f, 100.f);
	


	return true;
}

void CStartWindow::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	//SYSTEMTIME	Time;

	//GetLocalTime(&Time);

	//m_Hour->SetNumber(Time.wHour);
	//m_Minute->SetNumber(Time.wMinute);
	//m_Second->SetNumber(Time.wSecond);


	//if (m_AddCount < lstrlen(m_AddText))
	//{
	//	m_TextTime += DeltaTime;

	//	if (m_TextTime >= 1.f)
	//	{
	//		m_TextTime -= 1.f;

	//		m_Text->AddText(m_AddText[m_AddCount]);

	//		++m_AddCount;
	//	}
	//}

	//float FPS = CGameManager::GetInst()->GetFPS();

	//char	Text[256] = {};
	//sprintf_s(Text, "FPS : %.5f", FPS);

	//TCHAR	Unicode[256] = {};
	//int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	//MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	//m_FPSText->SetText(Unicode);
	//
	////���콺 ��ǥ


	//POINT ptMouse;
	//GetCursorPos(&ptMouse);
	//ScreenToClient(m_hWnd, &ptMouse);

	////m_MouseMove.x
	//m_MousePos.x = (float)ptMouse.x;
	//m_MousePos.y = (float)ptMouse.y;

	//char MouseTextX[256] = {};
	//char MouseTextY[256] = {};
	//sprintf_s(MouseTextX, "X: %.f", m_MousePos.x);
	//sprintf_s(MouseTextY, "Y: %.f", m_MousePos.y);

	//TCHAR	UnicodeX[256] = {};
	//int LengthX = MultiByteToWideChar(CP_ACP, 0, MouseTextX, -1, 0, 0);
	//MultiByteToWideChar(CP_ACP, 0, MouseTextX, -1, UnicodeX, LengthX);

	//TCHAR	UnicodeY[256] = {};
	//int LengthY = MultiByteToWideChar(CP_ACP, 0, MouseTextY, -1, 0, 0);
	//MultiByteToWideChar(CP_ACP, 0, MouseTextY, -1, UnicodeY, LengthY);

	//m_MousePosTextX->SetText(UnicodeX);
	//m_MousePosTextY->SetText(UnicodeY);

}

void CStartWindow::StartButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CMainScene>();
}

void CStartWindow::EditButtonCallback()
{

}

void CStartWindow::EndButtonCallback()
{
	CGameManager::GetInst()->Exit();
}

void CStartWindow::CheckImageCallback()
{

}

