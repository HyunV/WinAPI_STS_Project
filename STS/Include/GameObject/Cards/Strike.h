#pragma once
#include "../Card.h"

class CStrike :
    public CCard
{
    friend class CScene;

    //ī�� ����, ī�� �ɷ� ����, ī��
    //ī�� �̹��� ����
    

protected:
    CStrike();
    ~CStrike();

    bool Init();

    void Update(float DeltaTime);

    virtual void Render(HDC hDC, float DeltaTime);

    virtual void useCard();

    virtual void SetAbility();
};

