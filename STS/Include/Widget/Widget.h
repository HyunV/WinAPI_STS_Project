#pragma once
#include "../Ref.h"
//RC�� ���� �ʿ����� ����
//���� : ui�� ��������� ��ǰ������ ��ư, �ٵ��� ����� ���� ��ǰŬ����
//* UI�� ī�޶��� ������ ������ �ȵȴ�.
class CWidget :
    public CRef
{
    friend class CWidgetComponent;
    friend class CWidgetWindow; //���� �����츦 ���� ������ �� �ְ�

protected:
    CWidget();
    CWidget(const CWidget& widget);
    virtual ~CWidget();

protected:
    class CScene* m_Scene; //�ڽ��� � ���� �����ִ���
    class CWidgetWindow* m_Owner; //�� ������ ������ �ִ� ����������� � �༮���� �����ϴ� ����
    int   m_ZOrder; //�����鵵 ��� ����(����)�� �ʿ��ϹǷ� �� ���� ���� �����ش�.
    //bool  m_Visibility; //���̱�, �Ⱥ��̱�
    Vector2 m_Pos; //��ġ
    Vector2 m_Size; //ũ��
    bool m_MouseHovered; //���콺�� �����״��� ����

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
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime); //�߰����� ��ġ������ �ϳ� �� �޾Ƽ� ó��

public:
    bool CollisionMouse(const Vector2& Pos); //���콺 �浹

public:
    virtual void CollisionMouseHoveredCallback(const Vector2& Pos); //���콺 �浹�� �� ��(���콺�� �ö󰥶�) ���ϴ� �Լ�
    virtual void CollisionMouseReleaseCallback(); //���콺�� ����������
};

