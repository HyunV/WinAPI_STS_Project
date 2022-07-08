#pragma once
#include "Character.h"

//몬스터에 필요한 기능
// 공격여부 ->  1. 공격, 2. 버프 3.디버프 4. 알 수없음

// AI
// 주는 골드 및 보상?
// 충돌처리
//몬스터 가리킬 시 나오는 버프
class CMyMonster :
    public CCharacter
{
    friend class CScene;

protected:
    CMyMonster();
    virtual ~CMyMonster();
    
   
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
    void UseBuff();
};

