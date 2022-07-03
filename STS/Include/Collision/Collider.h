#pragma once
//충돌체 관리 하려면 "충돌체" 자체가 필요하다. 그 "충돌체"인 클래스
// 이 클래스를 게임 오브젝트에서 불러와서 사용할 수 있게 끔 공유할 수 있게 설계
//충돌체는 공유할 수 있으니 Ref 상속받아서 만듬
#include "../Ref.h"
class CCollider :
    public CRef
{
    friend class CGameObject;
    friend class CCollisionManager;

protected:
    CCollider();
    CCollider(const CCollider& collider);
    virtual ~CCollider() = 0; //순수가상함수, 추상클래스 용도로 쓰기위해 사용
                               // 이를 이용해서 Circle Collider, Box Collider 식으로 만들어서 쓸 예정

protected: //가지고 있어야 될 내용
    class CScene*       m_Scene; //어떤 씬에 속해 있어야 하는가? 하는 정보
    class CGameObject*  m_Owner; //충돌체를 가지고 있는 주인님 who?
    class CCard*        m_CardOwner;
    ECollider_Type      m_ColliderType; //충돌체 모양 (박스, 원 등등..)

    Vector2             m_Offset;       // Owner로부터 얼마만큼 떨어져 있을지에 대한 정보
    CollisionProfile*   m_Profile;      //어떤 Collision 파일을 쓰는지에 대한 정보   
    Vector2             m_HitPoint;
    float               m_Bottom;

    //충돌의 시점을 2가지로 잡아주게 설계한다. 충돌이 시작될 때, 충돌이 떨어질 때
    // 
    // 함수포인터에서 CCollider* 2개를 받는 이유는 서로 충돌된 두 물체를 인자로 넘겨주기 위해서이다.
    std::function<void(CCollider*, CCollider*)> m_CollisionBegin;
    std::function<void(CCollider*, CCollider*)> m_CollisionEnd;

    //마우스 충돌 관련 함수 포인터
    std::function<void(CCollider*, const Vector2&)> m_MouseCollisionBegin;
    std::function<void(CCollider*, const Vector2&)> m_MouseCollisionEnd;

    /*
현재 프레임에 두 물체가 충돌되고 다음 프레임에도 두 물체가 충돌이 되었다면 계속 충돌이 되고 있는 상태로
판단해야 한다.
그런데 이런 판단을 하기 위해서는 이전 프레임에서 두 물체가 서로 충돌이 되었는지에 대한 정보가 필요할 것이다.
그러므로 충돌체는 이전 프레임에 충돌되었던 충돌체를 담아둘 필요가 있다.
*/
    //실시간으로 충돌여부 판단하기 위해 중간 삽입삭제가 빈번하므로 리스트
    std::list<CSharedPtr<CCollider>> m_CollisionList; //충돌된 물체의 목록을 담는 리스트
    //충돌이 되었는데 이 리스트 안에 아무것도 없다면 이제 막 충돌이 시작되었다는 의미
    //리스트에 있으면 계속 충돌중인 상태. 이걸로 위에 Begin, End 판단.

    bool        m_MouseCollision;//마우스는 충돌체는 아니므로 bool변수로 판단할 변수로 만든다.
    int         m_MouseCollisionCount;
    bool        m_Check;

    //또한 마우스는 여러개랑 충돌되면 안된다. 하나랑만 충돌 (ex 겹쳐져있는 Npc)
    //#2. 마우스는 UI>월드물체 로 우선충돌 해야하낟.(인벤토리 열어놓고 몬스터랑 충돌될 수 있음)

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
    void AddCollisionList(CCollider* Collider); //충돌시 리스트에 추가하는 함수
    bool CheckCollisionList(CCollider* Collider); //리스트 목록에 있는지 체크
    void DeleteCollisionList(CCollider* Collider); //리스트 제거
    void ClearCollisionList(); // 리스트 비우기
    
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
    virtual bool CollisionMouse(const Vector2& Mouse); //마우스 위치를 전달받아 충돌을 수행해주는 함수

public:
    template <typename T>
    void SetCollisionBeginFunction(T* Obj, void(T::* Func)(CCollider*, CCollider*))
    {
        m_CollisionBegin = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
        //각각의 인자를 차례대로 넘겨줄 수 있게 등록, (값 거꾸로 넣어서 대참사 일어나지 않게 고정시켜서 들어감1번은 Obj, 2번은 Func로)
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


