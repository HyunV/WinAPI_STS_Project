#pragma once
//�浹ü ���� �Ϸ��� "�浹ü" ��ü�� �ʿ��ϴ�. �� "�浹ü"�� Ŭ����
// �� Ŭ������ ���� ������Ʈ���� �ҷ��ͼ� ����� �� �ְ� �� ������ �� �ְ� ����
//�浹ü�� ������ �� ������ Ref ��ӹ޾Ƽ� ����
#include "../Ref.h"
class CCollider :
    public CRef
{
    friend class CGameObject;
    friend class CCollisionManager;

protected:
    CCollider();
    CCollider(const CCollider& collider);
    virtual ~CCollider() = 0; //���������Լ�, �߻�Ŭ���� �뵵�� �������� ���
                               // �̸� �̿��ؼ� Circle Collider, Box Collider ������ ���� �� ����

protected: //������ �־�� �� ����
    class CScene*       m_Scene; //� ���� ���� �־�� �ϴ°�? �ϴ� ����
    class CGameObject*  m_Owner; //�浹ü�� ������ �ִ� ���δ� who?
    class CCard*        m_CardOwner;
    ECollider_Type      m_ColliderType; //�浹ü ��� (�ڽ�, �� ���..)

    Vector2             m_Offset;       // Owner�κ��� �󸶸�ŭ ������ �������� ���� ����
    CollisionProfile*   m_Profile;      //� Collision ������ �������� ���� ����   
    Vector2             m_HitPoint;
    float               m_Bottom;

    //�浹�� ������ 2������ ����ְ� �����Ѵ�. �浹�� ���۵� ��, �浹�� ������ ��
    // 
    // �Լ������Ϳ��� CCollider* 2���� �޴� ������ ���� �浹�� �� ��ü�� ���ڷ� �Ѱ��ֱ� ���ؼ��̴�.
    std::function<void(CCollider*, CCollider*)> m_CollisionBegin;
    std::function<void(CCollider*, CCollider*)> m_CollisionEnd;

    //���콺 �浹 ���� �Լ� ������
    std::function<void(CCollider*, const Vector2&)> m_MouseCollisionBegin;
    std::function<void(CCollider*, const Vector2&)> m_MouseCollisionEnd;

    /*
���� �����ӿ� �� ��ü�� �浹�ǰ� ���� �����ӿ��� �� ��ü�� �浹�� �Ǿ��ٸ� ��� �浹�� �ǰ� �ִ� ���·�
�Ǵ��ؾ� �Ѵ�.
�׷��� �̷� �Ǵ��� �ϱ� ���ؼ��� ���� �����ӿ��� �� ��ü�� ���� �浹�� �Ǿ������� ���� ������ �ʿ��� ���̴�.
�׷��Ƿ� �浹ü�� ���� �����ӿ� �浹�Ǿ��� �浹ü�� ��Ƶ� �ʿ䰡 �ִ�.
*/
    //�ǽð����� �浹���� �Ǵ��ϱ� ���� �߰� ���Ի����� ����ϹǷ� ����Ʈ
    std::list<CSharedPtr<CCollider>> m_CollisionList; //�浹�� ��ü�� ����� ��� ����Ʈ
    //�浹�� �Ǿ��µ� �� ����Ʈ �ȿ� �ƹ��͵� ���ٸ� ���� �� �浹�� ���۵Ǿ��ٴ� �ǹ�
    //����Ʈ�� ������ ��� �浹���� ����. �̰ɷ� ���� Begin, End �Ǵ�.

    bool        m_MouseCollision;//���콺�� �浹ü�� �ƴϹǷ� bool������ �Ǵ��� ������ �����.
    int         m_MouseCollisionCount;
    bool        m_Check;

    //���� ���콺�� �������� �浹�Ǹ� �ȵȴ�. �ϳ����� �浹 (ex �������ִ� Npc)
    //#2. ���콺�� UI>���幰ü �� �켱�浹 �ؾ��ϳ�.(�κ��丮 ������� ���Ͷ� �浹�� �� ����)

public:
    void SetMouseCollision(bool Collision)
    {
        m_MouseCollision = Collision;
    }

    void SetOffset(const Vector2& Offset)
    {
        m_Offset = Offset;
    }

    void SetOffset(float x, float y)
    {
        m_Offset = Vector2(x, y);
    }

    Vector2 GetOffset() {
        return m_Offset;
    }
public:
    bool GetMouseCollision()    const
    {
        return m_MouseCollision;
    }
    float GetBottom()   const
    {
        return m_Bottom;
    }
    const Vector2& GetHitPoint()   const
    {
        return m_HitPoint;
    }
    class CGameObject* GetOwner()   const
    {
        return m_Owner;
    }
    class CCard* GetCardOwner() const
    {
        return m_CardOwner;
    }
    class CScene* GetScene()    const
    {
        return m_Scene;
    }

    ECollider_Type GetColliderType()    const
    {
        return m_ColliderType;
    }

    const CollisionProfile* GetProfile()    const
    {
        return m_Profile;
    }


public:
    void SetCollisionEnable(bool Enable);

public:
    void SetCollisionProfile(const std::string& Name); 
    void AddCollisionList(CCollider* Collider); //�浹�� ����Ʈ�� �߰��ϴ� �Լ�
    bool CheckCollisionList(CCollider* Collider); //����Ʈ ��Ͽ� �ִ��� üũ
    void DeleteCollisionList(CCollider* Collider); //����Ʈ ����
    void ClearCollisionList(); // ����Ʈ ����
    
    void CallCollisionBegin(CCollider* Dest);
    void CallCollisionEnd(CCollider* Dest);

    void CallMouseCollisionBegin(const Vector2& MousePos);
    void CallMouseCollisionEnd(const Vector2& MousePos);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual bool Collision(CCollider* Dest);
    virtual bool CollisionMouse(const Vector2& Mouse); //���콺 ��ġ�� ���޹޾� �浹�� �������ִ� �Լ�

public:
    template <typename T>
    void SetCollisionBeginFunction(T* Obj, void(T::* Func)(CCollider*, CCollider*))
    {
        m_CollisionBegin = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
        //������ ���ڸ� ���ʴ�� �Ѱ��� �� �ְ� ���, (�� �Ųٷ� �־ ������ �Ͼ�� �ʰ� �������Ѽ� ��1���� Obj, 2���� Func��)
    }

    template <typename T>
    void SetCollisionEndFunction(T* Obj, void(T::* Func)(CCollider*, CCollider*))
    {
        m_CollisionEnd = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
    }

    template <typename T>
    void SetMouseCollisionBeginFunction(T* Obj, void(T::* Func)(CCollider*, const Vector2&))
    {
        m_MouseCollisionBegin = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
    }

    template <typename T>
    void SetMouseCollisionEndFunction(T* Obj, void(T::* Func)(CCollider*, const Vector2&))
    {
        m_MouseCollisionEnd = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
    }
};


