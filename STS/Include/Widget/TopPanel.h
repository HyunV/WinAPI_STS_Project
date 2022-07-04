#pragma once
#include "WidgetWindow.h"
#include "../GameInfo.h"
#include "../GameObject/Card.h"
class CTopPanel :
    public CWidgetWindow 
{
    friend class CScene;

protected:
    CTopPanel();
    virtual ~CTopPanel();

private:
    HWND m_hWnd;

    CSharedPtr<class CText> m_PlayerName; //이름
    CSharedPtr<class CText> m_Job; //직업
    
    
    CSharedPtr<class CText> m_LifeUI; //체력

    CSharedPtr<class CText> m_GoldUI; //골드
    CSharedPtr<class CText> m_FloorUI; //오른 층 수
    //std::vector<CSharedPtr<class CButton>> m_Potion; //포션

     
    //상단 버튼 UI
    CSharedPtr<class CButton> m_SettingButton;
    CSharedPtr<class CButton> m_DeckButton;
    CSharedPtr<class CText> m_DeckCount;
    CSharedPtr<class CButton> m_MapButton;
    
    //하단 UI
    CSharedPtr<class CButton> m_DrawCardButton; //뽑을 카드 버튼
    CSharedPtr<class CImageWidget2> m_LCountCircle;
    CSharedPtr<class CText> m_LCardCount;
        
    CSharedPtr<class CButton> m_DiscardButton; //버릴 카드 버튼 
    CSharedPtr<class CImageWidget2> m_RCountCircle;
    CSharedPtr<class CText> m_RCardCount;

    
    CSharedPtr<class CImageWidget2> m_EnergyUI; //에너지 UI 버튼
    CSharedPtr<class CText> m_Energy;
    
    CSharedPtr<class CButton> m_TurnOffButton;
    CSharedPtr<class CText> m_TurnOffText;
    

    CSharedPtr<class CButton> m_BackButton;
    CSharedPtr<class CButton> m_ConfirmButton;
    vector<CCard*> m_CardTemp;
    //에너지, 뽑을 카드 더미(숫자), 버릴카드 더미(숫자) 턴 종료(버튼) ,픽버튼(버튼) 보이기 여부
    
    CSharedPtr<class CText> m_FPSText;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
public:
    void HideOnUI(bool Enable);

    void TestCallback();
    void SettingButtonCallback();
    void DeckButtonCallback();
    void MapButtonCallback();
    void DrawButtonCallBack();
    void DiscardCallBack();
    void TurnOffCallBack();
    void BackCallBack();
    void ConfirmCallBack();
};

