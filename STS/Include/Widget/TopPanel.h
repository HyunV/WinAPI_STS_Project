#pragma once
#include "WidgetWindow.h"
#include "../GameInfo.h"
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

    CSharedPtr<class CText> m_DeckCount;

    CSharedPtr<class CText> m_Energy;

    CSharedPtr<class CText> m_LCardCount;
    CSharedPtr<class CText> m_RCardCount;

    bool TurnOff;

    //에너지, 뽑을 카드 더미(숫자), 버릴카드 더미(숫자) 턴 종료(버튼) ,픽버튼(버튼) 보이기 여부
    
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
public:
    void TestCallback();
    void SettingButtonCallback();
};

