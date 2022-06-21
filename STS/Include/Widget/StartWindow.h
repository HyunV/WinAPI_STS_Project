#pragma once
#include "WidgetWindow.h"
#include "ImageWidget.h"
class CStartWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CStartWindow();
    virtual ~CStartWindow();

private:
    CSharedPtr<class CText> m_Text;
    TCHAR m_AddText[32];
    float m_TextTime;
    int m_AddCount;

    CSharedPtr<class CNumber>   m_Hour;
    CSharedPtr<class CNumber>   m_Minute;
    CSharedPtr<class CNumber>   m_Second;
    CSharedPtr<class CText>     m_FPSText;

    CSharedPtr<class CText>     m_MousePosTextX;
    CSharedPtr<class CText>     m_MousePosTextY;

    Vector2 m_MousePos;
    HWND    m_hWnd;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    void StartButtonCallback();
    void EditButtonCallback();
    void EndButtonCallback();
    void CheckImageCallback();
};

