#pragma once
#include "../Card.h"
#include "../../Widget/WidgetWindow.h"
//
class CStrike :
    public CCard
{
    friend class CScene;



protected:
    CStrike();
    ~CStrike();

    bool Init();

    void Update(float DeltaTime);

    void Render(HDC hDC, float DeltaTime);

    virtual void useCard();

};

