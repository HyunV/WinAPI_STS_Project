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
    //������ ��ư    
    void CardButtonCallBack(); //ī�� ��ư
    void CardPassButtonCallBack(); //ī�� �ѱ�� ��ư
    void GoldButtonCallback(); //��� ��ư
    void PassButtonCallback();  //�ǳʶٱ� ��ư
    
    CSharedPtr<class CButton> m_StartButton;
    float m_Time;
};

