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

    CSharedPtr<class CText> m_PlayerName; //�̸�
    CSharedPtr<class CText> m_Job; //����
    
    
    CSharedPtr<class CText> m_LifeUI; //ü��

    CSharedPtr<class CText> m_GoldUI; //���
    CSharedPtr<class CText> m_FloorUI; //���� �� ��
    //std::vector<CSharedPtr<class CButton>> m_Potion; //����

     
    //��� ��ư UI
    CSharedPtr<class CButton> m_SettingButton;
    CSharedPtr<class CButton> m_DeckButton;
    CSharedPtr<class CText> m_DeckCount;
    CSharedPtr<class CButton> m_MapButton;
    
    //�ϴ� UI
    CSharedPtr<class CButton> m_DrawCardButton; //���� ī�� ��ư
    CSharedPtr<class CImageWidget2> m_LCountCircle;
    CSharedPtr<class CText> m_LCardCount;
        
    CSharedPtr<class CButton> m_DiscardButton; //���� ī�� ��ư 
    CSharedPtr<class CImageWidget2> m_RCountCircle;
    CSharedPtr<class CText> m_RCardCount;

    
    CSharedPtr<class CImageWidget2> m_EnergyUI; //������ UI ��ư
    CSharedPtr<class CText> m_Energy;
    
    CSharedPtr<class CButton> m_TurnOffButton;
    CSharedPtr<class CText> m_TurnOffText;
    

    CSharedPtr<class CButton> m_BackButton;
    CSharedPtr<class CButton> m_ConfirmButton;
    vector<CCard*> m_CardTemp;
    //������, ���� ī�� ����(����), ����ī�� ����(����) �� ����(��ư) ,�ȹ�ư(��ư) ���̱� ����
    
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

