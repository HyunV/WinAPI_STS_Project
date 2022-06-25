#include "TopPanel.h"
#include "ImageWidget2.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../GameManager.h"
#include "Text.h"
#include "Button.h"

CTopPanel::CTopPanel()
{
}

CTopPanel::~CTopPanel()
{
}
//싱글톤으로 써야될듯
bool CTopPanel::Init()
{
    //이름, 직업 체력, 골드, 포션슬롯,  오른 층 수, (타이머) 지도, 카드, 환경설정, 
    //에너지, 뽑을 카드 더미(숫자), 버릴카드 더미(숫자) 턴 종료(버튼) ,픽버튼(버튼) 보이기 여부
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
    SettingButton->SetPos(1231.f, 3.f);
    SettingButton->SetColorKey(255, 0, 255);

    
    CButton* DeckButton = CreateWidget<CButton>("DeckButton");
    DeckButton->SetTexture("DeckButton", TEXT("TopPanel/deck.bmp"));
    DeckButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    DeckButton->SetPos(1182.f, 3.f);
    DeckButton->SetColorKey(255, 0, 255);

    m_DeckCount = CreateWidget<CText>("DeckCount");
    m_DeckCount->SetFont("UI");
    m_DeckCount->SetText(TEXT("10"));
    m_DeckCount->SetPos(1210.f, 20.f);
    m_DeckCount->SetTextColor(255, 255, 255);
    m_DeckCount->EnableShadow(true);
    m_DeckCount->SetShadowOffset(1.f, 1.f);


    CButton* MapButton = CreateWidget<CButton>("MapButton");
    MapButton->SetTexture("MapButton", TEXT("TopPanel/map.bmp"));
    MapButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    MapButton->SetPos(1137.f, 3.f);
    MapButton->SetColorKey(255, 0, 255);

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

    CButton* CardButton = CreateWidget<CButton>("CardButton");
    CardButton->SetTexture("CardButton", TEXT("TopPanel/base1.bmp"));
    CardButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(77.f, 77.f));
    CardButton->SetPos(0.f, 723.f);

    CImageWidget2* DeckShadow = CreateWidget<CImageWidget2>("DeckShadow");
    DeckShadow->SetTexture("DeckShadow", TEXT("TopPanel/deckButton/Shadow.bmp"));
    DeckShadow->SetSize(128.f, 128.f);
    DeckShadow->SetPos(0.f, 1072.f);
    
    CButton* DiscardButton = CreateWidget<CButton>("DiscardButton");
    DiscardButton->SetTexture("DiscardBase", TEXT("TopPanel/discardButton/base.bmp"));
    DiscardButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(128.f, 128.f));
    DiscardButton->SetPos(1792.f, 1072.f);

    //CImageWidget2* DiscardShadow = CreateWidget<CImageWidget2>("DiscardShadow");
    //DiscardShadow->SetTexture("DiscardShadow", TEXT("TopPanel/discardButton/Shadow.bmp"));
    //DiscardShadow->SetSize(128.f, 128.f);
    //DiscardShadow->SetPos(1792.f, 1072.f);

    //CImageWidget2* LCountCircle = CreateWidget<CImageWidget2>("LCountCircle");
    //LCountCircle->SetTexture("LCountCircle", TEXT("TopPanel/countCircle.bmp"));
    //LCountCircle->SetSize(128.f, 128.f);
    //LCountCircle->SetPos(0.f, 1072.f);

    //CImageWidget2* RCountCircle = CreateWidget<CImageWidget2>("RCountCircle");
    //RCountCircle->SetTexture("LCountCircle", TEXT("TopPanel/countCircle.bmp"));
    //RCountCircle->SetSize(128.f, 128.f);
    //RCountCircle->SetPos(0.f, 1072.f);

    LCardCount = CreateWidget<CText>("LCardCount");
    LCardCount->SetText(TEXT("5"));
    LCardCount->SetPos(100.f, 1150.f);
    LCardCount->SetTextColor(255, 255, 255);
    LCardCount->EnableShadow(true);
    LCardCount->SetShadowOffset(1.f, 1.f);

    RCardCount = CreateWidget<CText>("RCardCount");
    RCardCount->SetText(TEXT("5"));
    RCardCount->SetPos(1800.f, 1150.f);
    RCardCount->SetTextColor(255, 255, 255);
    RCardCount->EnableShadow(true);
    RCardCount->SetShadowOffset(1.f, 1.f);

    CButton* TurnOffButton = CreateWidget<CButton>("TurnOutButton");
    TurnOffButton->SetTexture("TurnOffButton", TEXT("TopPanel/endTurnButton.bmp"));
    TurnOffButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(256.f, 256.f));
    TurnOffButton->SetPos(1500.f, 900.f);


    //하단 UI
    //에너지
    m_Energy = CreateWidget<CText>("Energy");
    m_Energy->SetText(TEXT("3/3"));
    m_Energy->SetPos(200.f, 1000.f);
    m_Energy->SetTextColor(255, 255, 219);
    m_Energy->EnableShadow(true);
    m_Energy->SetShadowOffset(3.f, 3.f);

    return true;
}

void CTopPanel::Update(float DeltaTime)
{
    CWidgetWindow::Update(DeltaTime);
}
