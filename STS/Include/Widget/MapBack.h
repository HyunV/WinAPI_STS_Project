#pragma once
#include "WidgetWindow.h"
class CMapBack :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CMapBack();
    virtual ~CMapBack();
protected:
    //CSharedPtr<class CButton> m_BackButton;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

    //�� ��� -> �� ���¿��� ī��� ���� �� �� �ִ�
};

