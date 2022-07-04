#pragma once
#include "GameObject.h"
class CBubbleMessage :
    public CGameObject
{
    friend class CScene;

protected:
    CBubbleMessage();
    virtual ~CBubbleMessage();

private:
    EMessageBox_Type m_Type;
    CSharedPtr<class CWidgetComponent> m_Message;
    float m_Time;
   

public:

    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    void SetMessageType(EMessageBox_Type Type) {
        m_Type = Type;
    }
    CWidgetComponent* GetMessages() {
        return m_Message;
    }
};

