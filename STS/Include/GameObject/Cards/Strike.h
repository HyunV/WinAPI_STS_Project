#pragma once
#include "../Card.h"

class CStrike :
    public CCard
{
    friend class CScene;

    //카드 세팅, 카드 능력 세팅, 카드
    //카드 이미지 삽입
    

protected:
    CStrike();
    ~CStrike();

    bool Init();

    void Update(float DeltaTime);

    virtual void Render(HDC hDC, float DeltaTime);

    virtual void useCard();

    virtual void SetAbility();
};

