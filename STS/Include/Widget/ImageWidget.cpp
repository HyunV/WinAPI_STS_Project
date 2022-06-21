#include "ImageWidget.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/Sound/Sound.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"
#include "../Input.h"
#include "../GameManager.h"

CImageWidget::CImageWidget() :
	m_CheckState(ECheckBox_State::Disable),
	m_CheckStateData{}
{
}

CImageWidget::CImageWidget(const CImageWidget& widget) :
	CWidget(widget)
{
}

CImageWidget::~CImageWidget()
{
}

void CImageWidget::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CImageWidget::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#ifdef UNICODE

void CImageWidget::SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CImageWidget::SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#else
void CButton::SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CButton::SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#endif // UNICODE

void CImageWidget::SetImageStateData(ECheckBox_State State, const Vector2& Start, const Vector2& End)
{
	m_CheckStateData[(int)State].Start = Start;
	m_CheckStateData[(int)State].End = End;
}

bool CImageWidget::Init()
{
	m_hWnd = CGameManager::GetInst()->GetWindowHandle();
	m_Clicked = false;

	return true;
}

void CImageWidget::Update(float DeltaTime)
{
	m_Size = m_CheckStateData[(int)m_CheckState].End - m_CheckStateData[(int)m_CheckState].Start;
	//현재 상태에서 end - start를 빼주어 최종 크기를 잡아준다.
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	if (m_MouseHovered)
	{
		if (CInput::GetInst()->GetMouseLDown())
			m_Clicked = true;

		if (m_Clicked && CInput::GetInst()->GetMouseLUp())  //마우스 뗄 때
		{
			if (m_CheckState == ECheckBox_State::Disable) {
				m_CheckState = ECheckBox_State::Enable;
				//MessageBox(nullptr, TEXT("비활성 -> 활성."), TEXT("^모^"), MB_OK);
			}
			else if (m_CheckState == ECheckBox_State::Enable) {
				m_CheckState = ECheckBox_State::Disable;
				//MessageBox(nullptr, TEXT("활성 -> 비활성."), TEXT("^모^"), MB_OK);
			}
		}
		if (m_Clicked && CInput::GetInst()->GetMouseLPush()) //누르고 있을 때
		{
			m_Clicked = true;


			m_MouseMove.x = (float)ptMouse.x - m_MousePos.x;
			m_MouseMove.y = (float)ptMouse.y - m_MousePos.y;

			m_MousePos.x = (float)ptMouse.x;
			m_MousePos.y = (float)ptMouse.y;


			m_Pos.x = (float)(m_Size.x + m_MousePos.x) * 0.5;
			m_Pos.y = (float)(m_Size.y + m_MousePos.y) * 0.5;

		}
		else
		{
			//m_Clicked = false;
		}
	}
	else
	{
		m_Clicked = false;
	}
}

void CImageWidget::PostUpdate(float DeltaTime)
{
}

void CImageWidget::Render(HDC hDC, float DeltaTime)
{
	Vector2	RenderPos = m_Pos + m_Owner->GetPos(); //위치를 만들어 준다.

	if (m_Texture) //텍스처 있을경우
	{
		if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
		{
			if (m_Texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)(RenderPos.x), (int)(RenderPos.y),
					(int)m_Size.x, (int)m_Size.y,
					m_Texture->GetDC(),
					(int)m_CheckStateData[(int)m_CheckState].Start.x,
					(int)m_CheckStateData[(int)m_CheckState].Start.y,
					(int)m_Size.x, (int)m_Size.y,
					m_Texture->GetColorKey());
				//m_Owner->SetPos(m_MouseMove);
			}

			else
			{
				//BitBlt(hDC, (int)RenderPos.x, (int)RenderPos.y,
				//	(int)m_Size.x, (int)m_Size.y,
				//	m_Texture->GetDC(),
				//	(int)m_CheckStateData[(int)m_CheckState].Start.x,
				//	(int)m_CheckStateData[(int)m_CheckState].Start.y, SRCCOPY);
			}
		}

		else
		{
		}
	}

	else
	{
		Rectangle(hDC, (int)RenderPos.x, (int)RenderPos.y,
			(int)(RenderPos.x + m_Size.x), (int)(RenderPos.y + m_Size.y));
	}
}

void CImageWidget::Render(HDC hDC, const Vector2& Pos, float DeltaTime)
{

}

void CImageWidget::CollisionMouseHoveredCallback(const Vector2& Pos)
{
	CWidget::CollisionMouseHoveredCallback(Pos); //부모함수 호출
}

void CImageWidget::CollisionMouseReleaseCallback()
{
	CWidget::CollisionMouseReleaseCallback(); //부모함수 호출
}

bool CImageWidget::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_Texture)
		return false;

	m_Texture->SetColorKey(r, g, b);

	return true;
}

bool CImageWidget::SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
{
	return true;
}
