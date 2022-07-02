#include "TopPanel.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../GameManager.h"
#include "../GameObject/CardManager.h"

#include "ImageWidget2.h"
#include "Text.h"
#include "Button.h"

#include "../Scene/BattleScene.h"
#include "../GameObject/MyMonster.h"
CTopPanel::CTopPanel()
{
}

CTopPanel::~CTopPanel()
{
}
//싱글톤으로 써야될듯
bool CTopPanel::Init()
{
    //m_hWnd = CGameManager::GetInst()->GetWindowHandle();
    //이름, 직업 체력, 골드, 포션슬롯,  오른 층 수, (타이머) 지도, 카드, 환경설정, 
    //에너지, 뽑을 카드 더미(숫자), 버릴카드 더미(숫자) 턴 종료(버튼) ,픽버튼(버튼) 보이기 여부
    
    SetSize(1280, 800);
    m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
        "61.mp3");
    CImageWidget2* TopPanel = CreateWidget<CImageWidget2>("TopPanel");

    TopPanel->SetTexture("TopPanel", TEXT("TopPanel/bar.bmp"));
    TopPanel->SetSize(1280.f, 80.f);
    TopPanel->SetColorKey(255, 0, 255);

    m_PlayerName = CreateWidget<CText>("PName");
    m_PlayerName->SetText(TEXT("AR41"));
    m_PlayerName->SetPos(40.f, 5.f);
    m_PlayerName->SetTextColor(255, 255, 255);   
    m_PlayerName->EnableShadow(true);
    m_PlayerName->SetShadowOffset(0.2f, 0.2f);

    m_Job = CreateWidget<CText>("JOB");
    m_Job->SetText(TEXT("아이언클래드"));
    m_Job->SetPos(120.f, 11.f);
    m_Job->SetTextColor(191, 191, 191);
    m_Job->SetFont("PlayerNameFont");
    m_Job->EnableShadow(true);
    m_Job->SetShadowOffset(1.f, 1.f);

    CImageWidget2* LifeImage = CreateWidget<CImageWidget2>("LifeImage");
    LifeImage->SetTexture("LifeImage", TEXT("TopPanel/panelHeart.bmp"));
    LifeImage->SetPos(180.f, 3.f);
    LifeImage->SetSize(39, 39);
    LifeImage->SetColorKey(255, 0, 255);

    m_LifeUI = CreateWidget<CText>("Life");
    m_LifeUI->SetFont("UI");
    m_LifeUI->SetText(TEXT("80/80"));
    m_LifeUI->SetPos(240.f, 10.f);
    m_LifeUI->SetTextColor(212, 57, 43);
    m_LifeUI->EnableShadow(true);
    m_LifeUI->SetShadowOffset(1.f, 1.f);


    CImageWidget2* GoldImage = CreateWidget<CImageWidget2>("GoldImage");
    GoldImage->SetTexture("GoldImage", TEXT("TopPanel/panelGoldBag.bmp"));
    GoldImage->SetPos(280.f, 3.f);
    GoldImage->SetSize(39, 39);
    GoldImage->SetColorKey(255, 0, 255);

    m_GoldUI = CreateWidget<CText>("Gold");
    m_GoldUI->SetFont("UI");
    m_GoldUI->SetText(TEXT("999"));
    m_GoldUI->SetPos(340, 10.f);
    m_GoldUI->SetTextColor(239, 200, 81);
    m_GoldUI->EnableShadow(true);
    m_GoldUI->SetShadowOffset(3.f, 3.f);
    
    //포션
    // 
    // 
    //설정 1846 1910-64 1836 - 84
    CButton* SettingButton = CreateWidget<CButton>("SettingButton");
    SettingButton->SetTexture("SettingButton", TEXT("TopPanel/settings.bmp"));
    SettingButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    SettingButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    SettingButton->SetButtonStateData(EButton_State::Click, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    SettingButton->SetPos(1231.f, 3.f);
    SettingButton->SetColorKey(255, 0, 255);
    SettingButton->SetZOrder(1);
    

    
    CButton* DeckButton = CreateWidget<CButton>("DeckButton");
    DeckButton->SetTexture("DeckButton", TEXT("TopPanel/deck.bmp"));
    DeckButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    DeckButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    DeckButton->SetButtonStateData(EButton_State::Click, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    DeckButton->SetPos(1182.f, 3.f);
    DeckButton->SetColorKey(255, 0, 255);
    DeckButton->SetZOrder(1);

    m_DeckCount = CreateWidget<CText>("DeckCount");
    m_DeckCount->SetFont("UI");
    m_DeckCount->SetText(TEXT("10"));
    m_DeckCount->SetPos(1210.f, 20.f);
    m_DeckCount->SetTextColor(255, 255, 255);
    m_DeckCount->EnableShadow(true);
    m_DeckCount->SetShadowOffset(1.f, 1.f);
    m_DeckCount->SetZOrder(2);


    CButton* MapButton = CreateWidget<CButton>("MapButton");
    MapButton->SetTexture("MapButton", TEXT("TopPanel/map.bmp"));
    MapButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    MapButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    MapButton->SetButtonStateData(EButton_State::Click, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    MapButton->SetPos(1137.f, 3.f);
    MapButton->SetColorKey(255, 0, 255);
    MapButton->SetZOrder(1);

    //타이머, 숫자 추가
   // CButton* TimerButton = CreateWidget<CButton>("TimerButton");
   //TimerButton->SetTexture("TimerButton", TEXT("TopPanel/map.bmp"));
   //TimerButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(64.f, 64.f));
   //TimerButton->SetPos(1560.f, 0.f);

    //층 수
    CButton* FloorButton = CreateWidget<CButton>("FloorButton");
    FloorButton->SetTexture("StairButton", TEXT("TopPanel/floor.bmp"));
    FloorButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    FloorButton->SetPos(500.f, 3.f);
    FloorButton->SetColorKey(255, 0, 255);

    m_FloorUI = CreateWidget<CText>("Floor");
    m_FloorUI->SetFont("UI");
    m_FloorUI->SetText(TEXT("1"));
    m_FloorUI->SetPos(550.f, 10.f);
    m_FloorUI->SetTextColor(255, 246, 226);
    m_FloorUI->EnableShadow(true);
    m_FloorUI->SetShadowOffset(1.f, 1.f);

    //하단 UI

    CButton* DrawCardButton = CreateWidget<CButton>("DrawCardButton");
    DrawCardButton->SetTexture("DrowCardButton", TEXT("TopPanel/base1.bmp"));
    DrawCardButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(77.f, 77.f));
    DrawCardButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(77.f, 0.f), Vector2(154.f, 77.f));
    DrawCardButton->SetPos(10.f, 630.f);
    DrawCardButton->SetColorKey(255, 0, 255);
    
    
    CButton* DiscardButton = CreateWidget<CButton>("DiscardButton");
    DiscardButton->SetTexture("DiscardButton", TEXT("TopPanel/base2.bmp"));
    DiscardButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(77.f, 77.f));
    DiscardButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(77.f, 0.f), Vector2(154.f, 77.f));
    DiscardButton->SetPos(1193.f, 630.f);
    DiscardButton->SetColorKey(255, 0, 255);

    CImageWidget2* LCountCircle = CreateWidget<CImageWidget2>("LCountCircle");
    LCountCircle->SetTexture("LCountCircle", TEXT("TopPanel/countCircle.bmp"));
    LCountCircle->SetSize(77.f, 77.f);
    LCountCircle->SetPos(35.f, 647.f);
    LCountCircle->SetColorKey(255, 0, 255);

    CImageWidget2* RCountCircle = CreateWidget<CImageWidget2>("RCountCircle");
    RCountCircle->SetTexture("LCountCircle", TEXT("TopPanel/countCircle.bmp"));
    RCountCircle->SetSize(77.f, 77.f);
    RCountCircle->SetPos(1163.f, 647.f);

    m_LCardCount = CreateWidget<CText>("LCardCount");
    m_LCardCount->SetText(TEXT("5"));
    m_LCardCount->SetPos(73.f, 673.f);
    m_LCardCount->SetTextColor(255, 255, 255);
    m_LCardCount->EnableShadow(true);
    m_LCardCount->SetShadowOffset(1.f, 1.f);

    m_RCardCount = CreateWidget<CText>("RCardCount");
    m_RCardCount->SetText(TEXT("5"));
    m_RCardCount->SetPos(1200.f, 673.f);
    m_RCardCount->SetTextColor(255, 255, 255);
    m_RCardCount->EnableShadow(true);
    m_RCardCount->SetShadowOffset(1.f, 1.f);

    CButton* TurnOffButton = CreateWidget<CButton>("TurnOutButton");
    TurnOffButton->SetTexture("TurnOffButton", TEXT("TopPanel/endTurnButton.bmp"));
    TurnOffButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(154.f, 154.f));
    TurnOffButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(154.f, 0.f), Vector2(308.f, 154.f));
    TurnOffButton->SetButtonStateData(EButton_State::Click, Vector2(154.f, 0.f), Vector2(308.f, 154.f));
    TurnOffButton->SetPos(1050.f, 500.f);
    TurnOffButton->SetColorKey(255, 0, 255);
    TurnOffButton->SetCallback<CTopPanel>(EButton_Sound_State::Click,
        this, & CTopPanel::TestCallback);

    CText* TurnOffText = CreateWidget<CText>("TurnOffText");
    TurnOffText->SetText(TEXT("턴 종료"));
    TurnOffText->SetPos(1125, 565);
    TurnOffText->SetTextColor(255, 255, 255);


    CImageWidget2* EnergyUI = CreateWidget<CImageWidget2>("EnergyUI");
    EnergyUI->SetTexture("EnergyUI", TEXT("TopPanel/energy.bmp"));
    EnergyUI->SetSize(77, 77);
    EnergyUI->SetPos(90, 570);
    EnergyUI->SetColorKey(255, 0, 255);

    //에너지
    m_Energy = CreateWidget<CText>("Energy");
    m_Energy->SetFont("CostFont");
    m_Energy->SetText(TEXT("00"));
    m_Energy->SetPos(127.f, 590.f);
    m_Energy->SetTextColor(255, 255, 219);
    m_Energy->EnableShadow(true);
    m_Energy->SetShadowOffset(3.f, 3.f);

    return true;
}

void CTopPanel::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);

    int DeckCount = CCardManager::GetInst()->getMaindeckCount();

    char	Text[256] = {};
    sprintf_s(Text, "%d", DeckCount);

    TCHAR	Unicode[256] = {};
    int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
    MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

    m_DeckCount->SetText(Unicode);

    int BringCount = CCardManager::GetInst()->getBringCardCount();
    char	Text1[256] = {};
    sprintf_s(Text1, "%d", BringCount);
    TCHAR	Unicode1[256] = {};
    int Length1 = MultiByteToWideChar(CP_ACP, 0, Text1, -1, 0, 0);
    MultiByteToWideChar(CP_ACP, 0, Text1, -1, Unicode1, Length1);

    m_LCardCount->SetText(Unicode1);

    int DiscardCount = CCardManager::GetInst()->getDiscardCount();
    char	Text2[256] = {};
    sprintf_s(Text2, "%d", DiscardCount);
    TCHAR	Unicode2[256] = {};
    int Length2 = MultiByteToWideChar(CP_ACP, 0, Text2, -1, 0, 0);
    MultiByteToWideChar(CP_ACP, 0, Text2, -1, Unicode2, Length2);

    m_RCardCount->SetText(Unicode2);

    int MaxEnergy = m_Scene->GetPlayer()->GetMaxEnergy();
    int Energy = m_Scene->GetPlayer()->GetEnergy();

    char    Text3[256] = {}; 
    sprintf_s(Text3, "%d/%d", Energy, MaxEnergy);
    TCHAR	Unicode3[256] = {};
    int Length3 = MultiByteToWideChar(CP_ACP, 0, Text3, -1, 0, 0);
    MultiByteToWideChar(CP_ACP, 0, Text3, -1, Unicode3, Length3);

    m_Energy->SetText(Unicode3);
   


}

void CTopPanel::TestCallback()
{
    m_Scene->GetPlayer()->AddShield(5);
    if (m_Scene->GetPlayer()->GetEnable()) {
        m_Scene->GetPlayer()->SetEnable(false);
    }
    else {
        m_Scene->GetPlayer()->SetEnable(true);
    }
    
    //CGameManager::GetInst()->Exit();
}

void CTopPanel::SettingButtonCallback()
{

}
