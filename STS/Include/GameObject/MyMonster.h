#pragma once
#include "Character.h"

//���Ϳ� �ʿ��� ���
// ���ݿ��� ->  1. ����, 2. ���� 3.����� 4. �� ������

// AI
// �ִ� ��� �� ����?
// �浹ó��
//���� ����ų �� ������ ����
class CMyMonster :
    public CCharacter
{
    friend class CScene;

protected:
    CMyMonster();
    CMyMonster(const CMyMonster& Obj);
    virtual ~CMyMonster();
    
   
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual float InflictDamage(float Damage);

    
private:
    void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
    void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
    void CollisionBegin(CCollider* Src, CCollider* Dest);
    void CollisionEnd(CCollider* Src, CCollider* Dest);

    float m_AttackDir;
    float m_AttackSpeed;
};

