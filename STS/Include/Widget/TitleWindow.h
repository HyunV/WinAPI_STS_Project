#pragma once
#include "WidgetWindow.h"
class CTitleWindow :
    public CWidgetWindow
{
    friend class CScene;


protected:
    CTitleWindow();
    virtual ~CTitleWindow();

private:
    virtual bool Init();
    virtual void Update(float DeltaTime);
public:

    //������ ��ư
    CSharedPtr<class CButton> m_StartButton;
    CSharedPtr<class CButton> m_EndButton;


    CSharedPtr<class CButton> m_CharacterButton;

    CSharedPtr<class CImageWidget2> m_CharacterBackImage;

    CSharedPtr<class CButton> m_BackButton; //�ڷΰ���
    CSharedPtr<class CText> m_BackButtonText;

    CSharedPtr<class CButton> m_ConfirmButton; //���� ��ư
    CSharedPtr<class CText> m_ConfirmButtonText;


    CSharedPtr<class CText> m_CharacterText;
    CSharedPtr<class CText> m_CharacterText2;
    CSharedPtr<class CText> m_CharacterText3;

    CSharedPtr<class CText> m_SelectCharacter;

    Vector2 v;

    void StartButtonCallback();
    void EndButtonCallback();
    void CharacterButtonCallback();
    void BackCallBack();
    void ConfirmCallback();
};

