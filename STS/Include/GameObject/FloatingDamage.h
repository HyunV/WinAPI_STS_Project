#pragma once
#include "GameObject.h"
class CFloatingDamage :
    public CGameObject
{
    friend class CScene;

protected:
    CFloatingDamage();
    virtual ~CFloatingDamage();

private:
    CSharedPtr<class CWidgetComponent> m_Damage;
    float m_Time;
    Vector2 m_MoveDamage;
    int m_Count;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    
    CWidgetComponent* GetText() {
        return m_Damage;
    }
};