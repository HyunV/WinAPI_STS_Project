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

    //숨겨진 버튼
    CSharedPtr<class CButton> m_StartButton;
    CSharedPtr<class CButton> m_CharacterButton;

    CSharedPtr<class CImageWidget2> m_CharacterBackImage;

    CSharedPtr<class CButton> m_BackButton; //뒤로가기
    CSharedPtr<class CText> m_BackButtonText;

    CSharedPtr<class CButton> m_ConfirmButton; //컨펌 버튼
    CSharedPtr<class CText> m_ConfirmButtonText;

    void StartButtonCallback();
    void CharacterButtonCallback();
    void BackCallBack();
    void ConfirmCallback();
};

