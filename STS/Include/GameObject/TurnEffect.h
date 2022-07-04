#pragma once
#include "GameObject.h"
#include "../Singletone.h"
class CTurnEffect :
    public CGameObject
{
    friend class CScene;

protected:
    CTurnEffect();
    virtual ~CTurnEffect();

private:
    CSharedPtr<class CWidgetComponent> m_WhosTurnText;
    CSharedPtr<class CWidgetComponent> m_TurnCountText;
    EWhos_Turn m_Turn;
    float m_Time;
    
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);

    void SetTurnMessage(EWhos_Turn Type) 
    {
        m_Turn = Type;
    }
};

