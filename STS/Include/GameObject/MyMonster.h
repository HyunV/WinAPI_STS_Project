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

private:
    CSharedPtr<class CWidgetComponent> m_HPBarFrame;
    CSharedPtr<class CWidgetComponent> m_HPBar;
    CSharedPtr<class CWidgetComponent> m_NameBar;

    CSharedPtr<class CWidgetComponent> m_HPText;

    CSharedPtr<class CWidgetComponent> m_TestButton;
    

    int m_MaxHP;
    int m_HP;
    int m_AttackDamage;
    int m_Shield;
    vector<wstring> m_HpBarFiles;
    
   
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual float InflictDamage(float Damage);

    
    void AddShield(int shield) {
        m_Shield += shield;
    }
    void MinusShield(int shield) {
        m_Shield -= shield;
    }
private:
    void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
    void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
    void CollisionBegin(CCollider* Src, CCollider* Dest);
    void CollisionEnd(CCollider* Src, CCollider* Dest);
};

