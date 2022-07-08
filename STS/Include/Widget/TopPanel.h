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
   // HWND m_hWnd;

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
    
    //������ ��ư
    CSharedPtr<class CButton> m_BackButton; //�ڷΰ���
    CSharedPtr<class CText> m_BackButtonText;

    CSharedPtr<class CButton> m_ConfirmButton; //���� ��ư
    CSharedPtr<class CText> m_ConfirmButtonText;

    CSharedPtr<class CButton> m_ProceedButton; //�ѱ�� ��ư
    CSharedPtr<class CText> m_ProceedButtonText;
   
    CSharedPtr<class CButton> m_CenterButton; //��� Ȯ�� ��ư
    CSharedPtr<class CText> m_CenterButtonText;

    // ���� UI �г�
    // ī�� ��ư
    // ��� ���� ��ư (���ӸŴ������� ����)
    //ī�� �Ŵ������� ����ī��

    CSharedPtr<class CButton> m_RestButton;
    //CSharedPtr<class CImageWidget2> m_CampChar;
    CSharedPtr<class CText> m_CampText;
    bool m_UseRest;

    //�й�
    CSharedPtr<class CImageWidget2> m_Banner;
    CSharedPtr<class CText> m_DefeatText;

    //�¸�
    CSharedPtr<class CImageWidget2> m_LeftEye;
    CSharedPtr<class CImageWidget2> m_RightEye;
    

    vector<CCard*> m_CardTemp;
    //������, ���� ī�� ����(����), ����ī�� ����(����) �� ����(��ư) ,�ȹ�ư(��ư) ���̱� ����
    
    CSharedPtr<class CText> m_FPSText;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
public:
    void HideOnUI(bool Enable);
    void HideOnRestUI(bool Enable);

    void TestCallback();
    void SettingButtonCallback();
    void DeckButtonCallback();
    void MapButtonCallback();
    void DrawButtonCallBack();
    void DiscardCallBack();
    void TurnOffCallBack();
    void BackCallBack();
    void ConfirmCallBack();
    void PreceedCallBack();
    void CenterButtonCallBack();

    void RestButtonCallBack();
    void RestButtonCallBack2();

    void ConvertText(int Value, CSharedPtr<class CText> TextWiz);
    void ConvertText(int Value, int Value2, CSharedPtr<class CText> TextWiz);

    void MonstersActivity();
};

