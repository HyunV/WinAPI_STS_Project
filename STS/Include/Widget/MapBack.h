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

    //맵 모드 -> 이 상태에선 카드와 맵을 볼 수 있다
};

