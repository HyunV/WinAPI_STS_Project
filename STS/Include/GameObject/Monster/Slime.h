#pragma once
#include "../Character.h"
class CSlime :
    public CCharacter
{
    friend class CScene;

protected:
    CSlime();
    virtual ~CSlime();


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual float InflictDamage(float Damage);
    virtual void MonstersAI();
    virtual bool ActivateMonster(EMonsterStatus m_NextStatus);
    void CheckNextMonster();
    void EndCallbackMonster();

private:
    void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
    void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
    void CollisionBegin(CCollider* Src, CCollider* Dest);
    void CollisionEnd(CCollider* Src, CCollider* Dest);

    float m_AttackDir;
    float m_AttackSpeed;

    int m_MonAttackDamage;
    bool m_UseTurn; //행동을 취했는지
    int m_Count;

    CWidgetComponent* m_IntantIcon;
    CWidgetComponent* m_IntantDamage;
    EMonsterStatus m_NextStatus;
    virtual void AddShield(int Shield);
    void randomattack();
};



