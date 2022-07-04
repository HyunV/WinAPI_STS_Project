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
#include "../GameObject/BubbleMessage.h"
#include "../GameObject/TurnEffect.h"
#include "../GameObject/MyPlayer.h"
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

    //m_BackLayer->SetEnable(false);

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
    m_SettingButton = CreateWidget<CButton>("SettingButton");
    m_SettingButton->SetTexture("SettingButton", TEXT("TopPanel/settings.bmp"));
    m_SettingButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    m_SettingButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    m_SettingButton->SetButtonStateData(EButton_State::Click, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    m_SettingButton->SetPos(1231.f, 3.f);
    m_SettingButton->SetColorKey(255, 0, 255);
    m_SettingButton->SetZOrder(1);
    m_SettingButton->SetCallback<CTopPanel>(EButton_Sound_State::Click,
        this, &CTopPanel::SettingButtonCallback);
    

    
    m_DeckButton = CreateWidget<CButton>("DeckButton");
    m_DeckButton->SetTexture("DeckButton", TEXT("TopPanel/deck.bmp"));
    m_DeckButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    m_DeckButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    m_DeckButton->SetButtonStateData(EButton_State::Click, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    m_DeckButton->SetPos(1182.f, 3.f);
    m_DeckButton->SetColorKey(255, 0, 255);
    m_DeckButton->SetZOrder(1);
    m_DeckButton->SetCallback<CTopPanel>(EButton_Sound_State::Click,
        this, &CTopPanel::DeckButtonCallback);

    m_DeckCount = CreateWidget<CText>("DeckCount");
    m_DeckCount->SetFont("UI");
    m_DeckCount->SetText(TEXT("10"));
    m_DeckCount->SetPos(1210.f, 20.f);
    m_DeckCount->SetTextColor(255, 255, 255);
    m_DeckCount->EnableShadow(true);
    m_DeckCount->SetShadowOffset(1.f, 1.f);
    m_DeckCount->SetZOrder(2);


    m_MapButton = CreateWidget<CButton>("MapButton");
    m_MapButton->SetTexture("MapButton", TEXT("TopPanel/map.bmp"));
    m_MapButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(39.f, 39.f));
    m_MapButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    m_MapButton->SetButtonStateData(EButton_State::Click, Vector2(39.f, 0.f), Vector2(78.f, 39.f));
    m_MapButton->SetPos(1137.f, 3.f);
    m_MapButton->SetColorKey(255, 0, 255);
    m_MapButton->SetZOrder(1);
    m_MapButton->SetCallback<CTopPanel>(EButton_Sound_State::Click,
        this, &CTopPanel::MapButtonCallback);

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

    m_DrawCardButton = CreateWidget<CButton>("DrawCardButton");
    m_DrawCardButton->SetTexture("DrowCardButton", TEXT("TopPanel/base1.bmp"));
    m_DrawCardButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(77.f, 77.f));
    m_DrawCardButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(77.f, 0.f), Vector2(154.f, 77.f));
    m_DrawCardButton->SetButtonStateData(EButton_State::Click, Vector2(77.f, 0.f), Vector2(154.f, 77.f));
    m_DrawCardButton->SetPos(10.f, 630.f);
    m_DrawCardButton->SetColorKey(255, 0, 255);
    m_DrawCardButton->SetCallback<CTopPanel>(EButton_Sound_State::Click,
        this, &CTopPanel::DrawButtonCallBack);
    
    
    m_DiscardButton = CreateWidget<CButton>("DiscardButton");
    m_DiscardButton->SetTexture("DiscardButton", TEXT("TopPanel/base2.bmp"));
    m_DiscardButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(77.f, 77.f));
    m_DiscardButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(77.f, 0.f), Vector2(154.f, 77.f));
    m_DiscardButton->SetButtonStateData(EButton_State::Click, Vector2(77.f, 0.f), Vector2(154.f, 77.f));
    m_DiscardButton->SetPos(1193.f, 630.f);
    m_DiscardButton->SetColorKey(255, 0, 255);
    m_DiscardButton->SetCallback<CTopPanel>(EButton_Sound_State::Click,
        this, &CTopPanel::DiscardCallBack);

    m_LCountCircle = CreateWidget<CImageWidget2>("LCountCircle");
    m_LCountCircle->SetTexture("LCountCircle", TEXT("TopPanel/countCircle.bmp"));
    m_LCountCircle->SetSize(77.f, 77.f);
    m_LCountCircle->SetPos(35.f, 647.f);
    m_LCountCircle->SetColorKey(255, 0, 255);

    m_RCountCircle = CreateWidget<CImageWidget2>("RCountCircle");
    m_RCountCircle->SetTexture("LCountCircle", TEXT("TopPanel/countCircle.bmp"));
    m_RCountCircle->SetSize(77.f, 77.f);
    m_RCountCircle->SetPos(1163.f, 647.f);
    m_RCountCircle->SetColorKey(255, 0, 255);

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

    m_TurnOffButton = CreateWidget<CButton>("TurnOffButton");
    m_TurnOffButton->SetTexture("TurnOffButton", TEXT("TopPanel/endTurnButton.bmp"));
    m_TurnOffButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(154.f, 154.f));
    m_TurnOffButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(154.f, 0.f), Vector2(308.f, 154.f));
    m_TurnOffButton->SetButtonStateData(EButton_State::Click, Vector2(154.f, 0.f), Vector2(308.f, 154.f));
    m_TurnOffButton->SetPos(1050.f, 500.f);
    m_TurnOffButton->SetColorKey(255, 0, 255);
    m_TurnOffButton->SetCallback<CTopPanel>(EButton_Sound_State::Click,
        this, & CTopPanel::TurnOffCallBack);

    m_TurnOffText = CreateWidget<CText>("TurnOffText");
    m_TurnOffText->SetText(TEXT("턴 종료"));
    m_TurnOffText->SetPos(1125, 565);
    m_TurnOffText->SetTextColor(255, 255, 255);


    m_EnergyUI = CreateWidget<CImageWidget2>("EnergyUI");
    m_EnergyUI->SetTexture("EnergyUI", TEXT("TopPanel/energy.bmp"));
    m_EnergyUI->SetSize(77, 77);
    m_EnergyUI->SetPos(90, 570);
    m_EnergyUI->SetColorKey(255, 0, 255);
    //EnergyUI->SetEnable(false);

    //에너지
    m_Energy = CreateWidget<CText>("Energy");
    m_Energy->SetFont("CostFont");
    m_Energy->SetText(TEXT("00"));
    m_Energy->SetPos(127.f, 590.f);
    m_Energy->SetTextColor(255, 255, 219);
    m_Energy->EnableShadow(true);
    m_Energy->SetShadowOffset(3.f, 3.f);

    m_BackButton = CreateWidget<CButton>("BackButton");
    m_BackButton->SetTexture("BackButton", TEXT("TopPanel/endTurnButton.bmp"));
    m_BackButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(154.f, 154.f));
    m_BackButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(154.f, 0.f), Vector2(308.f, 154.f));
    m_BackButton->SetButtonStateData(EButton_State::Click, Vector2(154.f, 0.f), Vector2(308.f, 154.f));
    m_BackButton->SetPos(50.f, 600.f);
    m_BackButton->SetColorKey(255, 0, 255);
    m_BackButton->SetCallback<CTopPanel>(EButton_Sound_State::Click,
        this, &CTopPanel::BackCallBack);
    m_BackButton->SetEnable(false);

    m_ConfirmButton = CreateWidget<CButton>("ConfirmButton");



    
#ifdef _DEBUG
    m_FPSText = CreateWidget<CText>("FPS");
    m_FPSText->SetText(TEXT("FPS"));
    m_FPSText->SetPos(900.f, 50.f);
    m_FPSText->SetTextColor(255, 0, 0);

    m_FPSText->EnableShadow(true);
    m_FPSText->SetShadowOffset(2.f, 2.f);
#endif // DEBUG

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
   
    int PlayerHP = m_Scene->GetPlayer()->GetHP();
    int PlayerMaxHP = m_Scene->GetPlayer()->GetMaxHP();

    char    Text5[256] = {};
    sprintf_s(Text5, "%d/%d", PlayerHP, PlayerMaxHP);
    TCHAR	Unicode5[256] = {};
    int Length5 = MultiByteToWideChar(CP_ACP, 0, Text5, -1, 0, 0);
    MultiByteToWideChar(CP_ACP, 0, Text5, -1, Unicode5, Length5);
    
    m_LifeUI ->SetText(Unicode5);

#ifdef _DEBUG
    float FPS = CGameManager::GetInst()->GetFPS();

    char	Text4[256] = {};
    sprintf_s(Text4, "FPS : %.5f", FPS);

    TCHAR	Unicode4[256] = {};
    int Length4 = MultiByteToWideChar(CP_ACP, 0, Text4, -1, 0, 0);
    MultiByteToWideChar(CP_ACP, 0, Text4, -1, Unicode4, Length4);

    m_FPSText->SetText(Unicode4);


    //static float CurrentTime = 0.f;

    //CurrentTime += DeltaTime;

    //char    TimeText[64] = {};

    //sprintf_s(TimeText, "Time : %.5f", CurrentTime);
   

#endif // DEBUG


}

void CTopPanel::Render(HDC hDC, float DeltaTime)
{
    CWidgetWindow::Render(hDC, DeltaTime);
#ifdef _DEBUG
    static float CurrentTime = 0.f;
    static int Min = 0;
    CurrentTime += DeltaTime;
    if (CurrentTime >= 60.f) {
        CurrentTime = 0;
        Min++;
    }
    char TimeText[64] = {};
    sprintf_s(TimeText, "Time : %d:%.5f", Min, CurrentTime);
    TextOutA(hDC, 1000, 100, TimeText, strlen(TimeText));
#endif // _DEBUG
}

void CTopPanel::HideOnUI(bool Enable)
{
    m_DrawCardButton->SetEnable(Enable);
    m_LCountCircle->SetEnable(Enable);
    m_LCardCount->SetEnable(Enable);

    m_DiscardButton->SetEnable(Enable);
    m_RCountCircle->SetEnable(Enable);
    m_RCardCount->SetEnable(Enable);


    m_EnergyUI->SetEnable(Enable);
    m_Energy->SetEnable(Enable);

    m_TurnOffButton->SetEnable(Enable);
    m_TurnOffText->SetEnable(Enable);
}

void CTopPanel::TestCallback()
{
    CCardManager::GetInst()->DrawCard(2);
    CCardManager::GetInst()->HandSort();
    m_Scene->SetBlackSwitch(true);
    
    //if (m_Scene->GetPlayer()->GetEnable()) {
    //    m_Scene->GetPlayer()->SetEnable(false);
    //}
    //else {
    //    m_Scene->GetPlayer()->SetEnable(true);
    //}
    
    //CGameManager::GetInst()->Exit();
}

void CTopPanel::SettingButtonCallback()
{
    //m_Scene->GetPlayer()->AddShield(5);
    //CCardManager::GetInst()->DrawCard(2);
    m_Scene->GetPlayer()->SetEnableDamaged(true);
    //m_Scene->GetMonster()->SetEnableAttack(true);
    m_Scene->GetMonster()->SetEnableDamaged(true);
}

void CTopPanel::DeckButtonCallback()
{
    if (!m_Scene->GetBlackSwitch())
    {
        m_CardTemp = CCardManager::GetInst()->GetMainDeck();
        HideOnUI(false);
        m_Scene->SetBlackSwitch(true);
        CCardManager::GetInst()->CardView(m_CardTemp);
        //MessageBox(nullptr, TEXT("2"), TEXT("a"), MB_OK);
        m_BackButton->SetEnable(true);
    }
}

void CTopPanel::MapButtonCallback()
{
    HideOnUI(true);
    m_Scene->SetBlackSwitch(false);
    m_BackButton->SetEnable(true);
   // MessageBox(nullptr, TEXT("3"), TEXT("a"), MB_OK);
}

void CTopPanel::DrawButtonCallBack()
{
    if (CCardManager::GetInst()->getBringCardCount() == 0) {
        CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("Messages");
        Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("뽑을 카드 더미가 비어있다."));
        return;
    }
    if (!m_Scene->GetBlackSwitch())
    {
        m_CardTemp = CCardManager::GetInst()->GetBringDeck();
        HideOnUI(false);
        m_Scene->SetBlackSwitch(true);
        CCardManager::GetInst()->CardView(m_CardTemp);
        m_BackButton->SetEnable(true);
    }
}

void CTopPanel::DiscardCallBack()
{
    if (CCardManager::GetInst()->getDiscardCount() == 0) {
        CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("Messages");
        Message->SetMessageType(EMessageBox_Type::Default);
        Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("버린 카드 더미가 비어있다."));
        return;
    }
    if (!m_Scene->GetBlackSwitch())
    {
        m_CardTemp = CCardManager::GetInst()->GetDiscardDeck();
        HideOnUI(false);
        m_Scene->SetBlackSwitch(true);
        CCardManager::GetInst()->CardView(m_CardTemp);
        //MessageBox(nullptr, TEXT("2"), TEXT("a"), MB_OK);
        m_BackButton->SetEnable(true);
    }
}

void CTopPanel::TurnOffCallBack()
{  
    if (!CCardManager::GetInst()->GetMonstersTurn() 
        && CCardManager::GetInst()->GetPlayerTurn())
    {
        if (CCardManager::GetInst()->GetTurnEffect() == nullptr) 
        {
            //MessageBox(nullptr, TEXT("작동안함"), TEXT("a"), MB_OK);
            CCardManager::GetInst()->SetPlayerTurn(false);
            CCardManager::GetInst()->HandToDiscard();
            CTurnEffect* TurnMessage = m_Scene->CreateObject<CTurnEffect>("TurnMessage");
            TurnMessage->SetTurnMessage(EWhos_Turn::Monster);
            m_Scene->GetMonster()->SetEnableAttack(true);
        }
    }
    
}

void CTopPanel::BackCallBack()
{
    CCardManager::GetInst()->ClearCard(m_CardTemp);
    m_CardTemp.clear();
    m_Scene->SetBlackSwitch(false);
    m_BackButton->SetEnable(false);
    
    HideOnUI(true);
    m_Scene->GetCameraObj()->SetPos(640, 400);  
    
}

void CTopPanel::ConfirmCallBack()
{
}
