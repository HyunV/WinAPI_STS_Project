#pragma once
#include "../Ref.h"
//RC가 굳이 필요하진 않음
//위젯 : ui를 만들기위한 부품같은것 버튼, 바등을 만들기 위한 부품클래스
//* UI는 카메라의 영향을 받으면 안된다.
class CWidget :
    public CRef
{
    friend class CWidgetComponent;
    friend class CWidgetWindow; //위젯 윈도우를 통해 생성할 수 있게

protected:
    CWidget();
    CWidget(const CWidget& widget);
    virtual ~CWidget();

protected:
    class CScene* m_Scene; //자신의 어떤 씬에 속해있는지
    class CWidgetWindow* m_Owner; //이 위젯을 가지고 있는 위젯윈도우는 어떤 녀석인지 구분하는 변수
    int   m_ZOrder; //위젯들도 출력 순서(정렬)이 필요하므로 이 값을 통해 정해준다.
    //bool  m_Visibility; //보이기, 안보이기
    Vector2 m_Pos; //위치
    Vector2 m_Size; //크기
    bool m_MouseHovered; //마우스가 가르켰는지 여부

public:
    const Vector2& GetPos() const
    {
        return m_Pos;
    }
    const Vector2& GetSize()	const
    {
        return m_Size;
    }

    int GetZOrder() const
    {
        return m_ZOrder;
    }

public:
    void SetPos(float x, float y)
    {
        m_Pos.x = x;
        m_Pos.y = y;
    }

    void SetPos(const Vector2& Pos)
    {
        m_Pos = Pos;
    }

    void SetSize(float x, float y)
    {
        m_Size.x = x;
        m_Size.y = y;
    }

    void SetSize(const Vector2& Size)
    {
        m_Size = Size;
    }

    void SetZOrder(int ZOrder)
    {
        m_ZOrder = ZOrder;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime); //추가적인 위치정보를 하나 더 받아서 처리

public:
    bool CollisionMouse(const Vector2& Pos); //마우스 충돌

public:
    virtual void CollisionMouseHoveredCallback(const Vector2& Pos); //마우스 충돌이 될 때(마우스가 올라갈때) 콜하는 함수
    virtual void CollisionMouseReleaseCallback(); //마우스가 떨어졌을때
};

