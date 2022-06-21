#include "Widget.h"

CWidget::CWidget() :
    m_Scene(nullptr),
    m_Owner(nullptr),
    m_ZOrder(0),
    m_MouseHovered(false)
{

}
CWidget::CWidget(const CWidget& widget) :
    CRef(widget)
{
    m_ZOrder = widget.m_ZOrder;
    m_MouseHovered = widget.m_MouseHovered;
}

CWidget::~CWidget()
{

} 

bool CWidget::Init()
{
    return true;
}

void CWidget::Update(float DeltaTime)
{
}

void CWidget::PostUpdate(float DeltaTime)
{
}

void CWidget::Render(HDC hDC, float DeltaTime)
{
}

void CWidget::Render(HDC hDC, const Vector2& Pos, float DeltaTime)
{
}

bool CWidget::CollisionMouse(const Vector2& Pos)
{
    if (Pos.x < m_Pos.x) //위치가 left값보다 작으면 안되고
        return false;
    else if (Pos.x > m_Pos.x + m_Size.x) //right보다 크면 안되고
        return false;

    else if (Pos.y < m_Pos.y) //top보다 작으면 안되고
        return false;

    else if (Pos.y > m_Pos.y + m_Size.y) //bottom보다 크면 안됨
        return false;

    if (!m_MouseHovered) //마우스가 올라간 상태가 아님
        CollisionMouseHoveredCallback(Pos); //
    
    return true;
}

void CWidget::CollisionMouseHoveredCallback(const Vector2& Pos)
{
    m_MouseHovered = true;
}

void CWidget::CollisionMouseReleaseCallback()
{
    m_MouseHovered = false;
}
