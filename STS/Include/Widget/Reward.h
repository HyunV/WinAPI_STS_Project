#pragma once
#include "WidgetWindow.h"
class CReward :
    public CWidgetWindow
{
    friend class Cscene;

public:
    CReward();
    virtual ~CReward();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
public:
    //숨겨진 버튼    
    void CardButtonCallBack(); //카드 버튼
    void CardPassButtonCallBack(); //카드 넘기기 버튼
    void GoldButtonCallback(); //골드 버튼
    void PassButtonCallback();  //건너뛰기 버튼
    
    CSharedPtr<class CButton> m_StartButton;
    float m_Time;
};

