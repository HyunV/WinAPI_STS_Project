#include "CameraObject.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
CCameraObject::CCameraObject()
{
}

CCameraObject::~CCameraObject()
{
}

bool CCameraObject::Init()
{
	CGameObject::Init();
	SetPos(640, 400);
	SetPivot(0.5f, 0.5f);
	SetSize(10.f, 10.f);
	m_MoveSpeed = 2000.f;

	//CColliderBox* Box = AddCollider<CColliderBox>("Camera");
	//Box->SetExtent(10, 10);
	
	CInput::GetInst()->AddBindFunction<CCameraObject>("CameraUp", Input_Type::Push, 
		this, &CCameraObject::CameraMoveUp);
	CInput::GetInst()->AddBindFunction<CCameraObject>("CameraDown", Input_Type::Push,
		this, &CCameraObject::CameraMoveDown);
	
	return true;
}

void CCameraObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_Pos.y + (1.f - m_Pivot.y) * m_Size.y >= 2880.f)
	{
		m_Pos.y = 2880.f - (1.f - m_Pivot.y) * m_Size.y;
	}

	else if (m_Pos.y - m_Pivot.y * m_Size.y <= 0.f)
	{
		m_Pos.y = m_Pivot.y * m_Size.y;
	}
}

void CCameraObject::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
	Vector2 Pos = m_Pos - m_Scene->GetCamera()->GetPos();
}

void CCameraObject::CameraMoveUp()
{
	if (m_Scene->GetBlackSwitch())	
	MoveDir(Vector2(0.f, -1.f));
}

void CCameraObject::CameraMoveDown()
{
	if (m_Scene->GetBlackSwitch())
	MoveDir(Vector2(0.f, 1.f));
}

void CCameraObject::CameraReset()
{
	SetPos(640, 400);
}
