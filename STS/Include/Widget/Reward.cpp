#include "Reward.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/BattleScene.h"
#include "Button.h"
#include "Text.h"
#include "ImageWidget2.h"


CReward::CReward()
{
	m_Time = 0;
}

CReward::~CReward()
{
}

bool CReward::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(1280.f, 720.f);

	CImageWidget2* Back = CreateWidget<CImageWidget2>("Back");

	Back->SetTexture("StartBack", TEXT("Back.bmp"));

	Back->SetSize(1280.f, 720.f);

	CImageWidget2* Panel = CreateWidget<CImageWidget2>("RewardPanel");
	Panel->SetTexture("RewardPanel", TEXT("Reward/rewardSheet.bmp"));
	Panel->SetSize(306, 358);
	Panel->SetPos(487, 200);
	Panel->SetColorKey(255, 0, 255);

	CImageWidget2* selectBanner = CreateWidget<CImageWidget2>("SelectBanner");
	selectBanner->SetTexture("SelectBanner", TEXT("Reward/selectBanner.bmp"));
	selectBanner->SetSize(556, 119);
	selectBanner->SetPos(362, 170);
	selectBanner->SetColorKey(255, 0, 255);

	CText* BannerText = CreateWidget<CText>("BannerText");
	BannerText->SetText(TEXT("Àü¸®Ç°!"));
	BannerText->SetFont("CostFont");
	BannerText->SetPos(640, 200);
	BannerText->SetTextColor(229, 229, 229);
	BannerText->EnableShadow(true);
	BannerText->SetShadowOffset(2.f, 2.f);

	CButton* SelectCardButton = CreateWidget<CButton>("SelectCardButton");
	SelectCardButton->SetTexture("electCardButton", TEXT("Reward/rewardPanel.bmp"));
	SelectCardButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(232.f, 49.f));
	SelectCardButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(232.f, 49.f));
	SelectCardButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(232.f, 49.f));
	SelectCardButton->SetPos(640-116.f, 300.f);
	SelectCardButton->SetColorKey(255, 0, 255);
	SelectCardButton->SetCallback<CReward>(EButton_Sound_State::Click, this, &CReward::CardButtonCallBack);
	SelectCardButton->SetZOrder(1);
	SelectCardButton->SetEnable(true);

	CButton* GoldButton = CreateWidget<CButton>("GoldButton");
	GoldButton->SetTexture("GoldButton", TEXT("Reward/rewardPanel.bmp"));
	GoldButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(232.f, 49.f));
	GoldButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(232.f, 49.f));
	GoldButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(232.f, 49.f));
	GoldButton->SetPos(640 - 116.f, 400.f);
	GoldButton->SetColorKey(255, 0, 255);
	GoldButton->SetCallback<CReward>(EButton_Sound_State::Click, this, &CReward::GoldButtonCallback);
	GoldButton->SetZOrder(1);
	GoldButton->SetEnable(true);

	CButton* CardPassButton = CreateWidget<CButton>("CardPassButton");
	CardPassButton->SetTexture("CardPassButton", TEXT("Reward/takeAll.bmp"));
	
	CardPassButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(0.f, 0.f), Vector2(256.f, 128.f));
	CardPassButton->SetButtonStateData(EButton_State::Normal, Vector2(256.f, 0.f), Vector2(512.f, 128.f));
	CardPassButton->SetButtonStateData(EButton_State::Click, Vector2(0.f, 0.f), Vector2(256.f, 128.f));
	CardPassButton->SetPos(640 - 128.f, 520.f);
	CardPassButton->SetColorKey(255, 0, 255);
	CardPassButton->SetCallback<CReward>(EButton_Sound_State::Click, this, &CReward::CardPassButtonCallBack);
	CardPassButton->SetZOrder(1);
	CardPassButton->SetEnable(true);

	CButton* PassButton = CreateWidget<CButton>("PassButton");
	PassButton->SetTexture("PassButton", TEXT("TopPanel/proceedButton.bmp"));
	PassButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(256.f, 256.f));
	PassButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(256.f, 0.f), Vector2(512.f, 256.f));	
	PassButton->SetButtonStateData(EButton_State::Click, Vector2(256.f, 0.f), Vector2(512.f, 256.f));
	PassButton->SetPos(950.f, 400.f);
	PassButton->SetColorKey(255, 0, 255);
	PassButton->SetCallback<CReward>(EButton_Sound_State::Click, this, &CReward::PassButtonCallback);
	PassButton->SetZOrder(1);
	PassButton->SetEnable(true);
	
	return true;
}

void CReward::Update(float DeltaTime)
{
	if (m_Scene->GetRewardSwitch())
	{
		SetEnable(true);
	}
	CWidgetWindow::Update(DeltaTime);
	//if (!GetEnable()) {
	//	m_Time += DeltaTime;
	//	if (m_Time > 0.1f)
	//	{
	//		SetActive(false);
	//	}		
	//}
}

void CReward::CardButtonCallBack()
{
	int a = 0;
}

void CReward::CardPassButtonCallBack()
{
	int a = 0;
}

void CReward::GoldButtonCallback()
{
	int a = 0;
}

void CReward::PassButtonCallback()
{
	SetEnable(false);
}
