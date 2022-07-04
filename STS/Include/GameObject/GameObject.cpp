#include "GameObject.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneCollision.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Collision/Collider.h"

CGameObject::CGameObject() :
	m_Scene(nullptr),
	m_Animation(nullptr),
	m_TimeScale(1.f),
	m_MoveSpeed(0.f),
	m_RenderLayer(ERender_Layer::Default),
	m_PhysicsSimulate(false),
	m_Ground(false),
	m_GravityAccel(10.f),
	m_FallTime(0.f),
	m_FallStartY(0.f),
	m_Jump(false),
	m_JumpVelocity(0.f),
	m_MoveObject(false),
	m_MovingObject(0),
	m_DirValue(1),
	m_EnableAttack(false),
	m_UsedCard(false),
	m_SelectedCard(false),
	m_CardControl(false),
	m_HP(1),
	m_MaxHP(1),
	m_Time(0.f)
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& Obj) :
	CRef(Obj),
	m_Scene(nullptr),
	m_Pos(Obj.m_Pos),
	m_Size(Obj.m_Size),

	m_Pivot(Obj.m_Pivot),
	m_TimeScale(Obj.m_TimeScale),
	m_PhysicsSimulate(Obj.m_PhysicsSimulate),
	m_Ground(false),
	m_GravityAccel(Obj.m_GravityAccel),
	m_FallTime(0.f),
	m_FallStartY(0.f),
	m_Jump(false),
	m_JumpVelocity(Obj.m_JumpVelocity),
	m_Shield(0),
	m_MaxEnergy(0),
	m_Energy(Obj.m_MaxEnergy),
	m_AttackCard(false),
	m_HP(1),
	m_MaxHP(1),
	m_Time(0.f)
{
}

CGameObject::~CGameObject()
{
	{
		auto	iter = m_ColliderList.begin();
		auto	iterEnd = m_ColliderList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->ClearCollisionList();
		}
	}

	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->SetActive(false);
		}
	}
	SAFE_DELETE(m_Animation);
}


//원하는 충돌체를 뽑아오기
CCollider* CGameObject::FindCollider(const std::string& Name)
{
	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
			return *iter;
	}

	return nullptr;
}

void CGameObject::SetTexture(const std::string& Name)
{
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CGameObject::SetTexture(CTexture* Texture)
{
	m_Texture = Texture;
}

void CGameObject::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CGameObject::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#ifdef UNICODE
void CGameObject::SetTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CGameObject::SetTextureFullPath(const std::string& Name,
	const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}
#else
void CGameObject::SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CGameObject::SetTextureFullPath(const std::string& Name,
	const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}
#endif

bool CGameObject::SetColorKey(unsigned char r, unsigned char g, unsigned char b, int Index)
{
	if (!m_Texture)
		return false;

	m_Texture->SetColorKey(r, g, b, Index);

	return true;
}
bool CGameObject::SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_Texture)
		return false;

	m_Texture->SetColorKeyAll(r, g, b);

	return true;
}

void CGameObject::CreateAnimation()
{
	m_Animation = new CAnimation;

	m_Animation->m_Owner = this;
	m_Animation->m_Scene = m_Scene;
}

void CGameObject::AddAnimation(const std::string& SequenceName, bool Loop, float PlayTime, float PlayScale, bool Reverse)
{
	m_Animation->AddAnimation(SequenceName, Loop, PlayTime, PlayScale, Reverse);
}

void CGameObject::SetPlayTime(const std::string& Name, float PlayTime)
{
	m_Animation->SetPlayTime(Name, PlayTime);
}

void CGameObject::SetPlayScale(const std::string& Name, float PlayScale)
{
	m_Animation->SetPlayScale(Name, PlayScale);
}

void CGameObject::SetPlayLoop(const std::string& Name, bool Loop)
{
	m_Animation->SetPlayLoop(Name, Loop);
}

void CGameObject::SetPlayReverse(const std::string& Name, bool Reverse)
{
	m_Animation->SetPlayReverse(Name, Reverse);
}

void CGameObject::SetCurrentAnimation(std::string& Name)
{
	m_Animation->SetCurrentAnimation(Name);
}

void CGameObject::ChangeAnimation(const std::string& Name)
{
	m_Animation->ChangeAnimation(Name);
}

bool CGameObject::CheckCurrentAnimation(const std::string& Name)
{
	return m_Animation->CheckCurrentAnimation(Name);
}

void CGameObject::MoveDir(const Vector2& Dir)
{
	m_Pos += Dir * m_MoveSpeed * DELTA_TIME * m_TimeScale;
}

void CGameObject::Move(const Vector2& MoveValue)
{
	m_Pos += MoveValue * m_TimeScale;
}

void CGameObject::Move(float Angle)
{
	Vector2	Dir;
	Dir.x = cosf(DegreeToRadian(Angle));
	Dir.y = sinf(DegreeToRadian(Angle));

	m_Pos += Dir * m_MoveSpeed * DELTA_TIME * m_TimeScale;
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
	if (m_MoveObject) //무브 적용 
	{
		m_MovingObject += m_DirValue * m_MoveSpeed * DELTA_TIME * m_TimeScale;
		
		if (m_MovingObject > 8.f && m_DirValue == 1) {
			m_DirValue = -1;
		}
		if (m_MovingObject < -8.f && m_DirValue == -1) {
			m_DirValue = 1;
		}

	}

	// 중력 적용
	if (!m_Ground && m_PhysicsSimulate) //땅을 안밟고 물리시뮬이 켜졌을때
	{
		// 떨어지는 시간을 누적시켜준다.
		m_FallTime += DeltaTime * m_GravityAccel;

		// 9.8 m/s^2
		// t초 후 y값
		// V:속도 A:가속도 G:중력
		// y = V * A - 0.5f * G * t * t
		// 0 = -0.5fGA^2 VA - y
		//이차 방정식이 나오니 근의 공식을 이용해서 해를 구하면 좋음
		float Velocity = 0.f;

		if (m_Jump)
			Velocity = m_JumpVelocity * m_FallTime; //속도 = 점프속도 * 떨어지는 시간

		m_Pos.y = m_FallStartY - (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime);
		//최종 Y위치: 떨어지기 시작한 지점의 Y - ((포물선 공식)속도 - 0.5중력 * (떨어지는)시간^2)
	}

	if (m_Animation) //애니메이션이 있으면 애니메이션 업데이트도 해준다.
		m_Animation->Update(DeltaTime * m_TimeScale);
	{
		auto	iter = m_ColliderList.begin();
		auto	iterEnd = m_ColliderList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_ColliderList.erase(iter);
				iterEnd = m_ColliderList.end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(DeltaTime);
			++iter;
		}
	}

	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_WidgetComponentList.erase(iter);
				iterEnd = m_WidgetComponentList.end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(DeltaTime);
			++iter;
		}
	}
}

void CGameObject::PostUpdate(float DeltaTime) //업데이트 후 업데이트 처리해주는 함수
{
	//이런 수식을 update에 넣으면 이동을 하기 전에 이동을 계산하니까 한 프레임 씩 밀릴 수 있다.
	m_Move = m_Pos - m_PrevPos; //(m_pos가 이전 프레임 위치값)

	// 애니메이션이 동작될 경우 이미지 크기로 사이즈를 결정하기 때문에 여기에서 사이즈를
	// 다시 구해주도록 한다.
	if (m_Animation)
	{
		CAnimationInfo* Current = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData = Current->m_Sequence->GetFrame(Current->m_Frame);

		m_Size = FrameData.End - FrameData.Start;
		//애니메이션이 바뀌어 사이즈가 바뀌더라도 발밑값을 구할 수 있다.
	}

	{
		auto	iter = m_ColliderList.begin();
		auto	iterEnd = m_ColliderList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_ColliderList.erase(iter);
				iterEnd = m_ColliderList.end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(DeltaTime);

			m_Scene->GetCollision()->AddCollider(*iter); //충돌체 추가

			++iter;
		}
	}

	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_WidgetComponentList.erase(iter);
				iterEnd = m_WidgetComponentList.end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(DeltaTime);
			++iter;
		}
	}
}

void CGameObject::Render(HDC hDC, float DeltaTime)
{
	Vector2	Pos;
	Vector2	CameraPos;
	Vector2	Resolution;

	if (m_Scene)
	{
		CameraPos = m_Scene->GetCamera()->GetPos();
		Resolution = m_Scene->GetCamera()->GetResolution();
		Pos = m_Pos - m_Scene->GetCamera()->GetPos();
	}
	else
	{
		CScene* Scene = CSceneManager::GetInst()->GetScene();
		Pos = m_Pos - Scene->GetCamera()->GetPos();
		CameraPos = Scene->GetCamera()->GetPos();
		Resolution = Scene->GetCamera()->GetResolution();
	}

	if (m_Animation)
	{
		CAnimationInfo* Current = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData = Current->m_Sequence->GetFrame(Current->m_Frame);
		//프레임정보를 뽑아온다

		Vector2	Size = FrameData.End - FrameData.Start;

		Vector2	RenderLT;

		RenderLT = Pos - m_Pivot * Size;

		Vector2	CullPos = m_Pos - m_Pivot * Size;

		if (CullPos.x > CameraPos.x + Resolution.x)
			return;

		else if (CullPos.x + Size.x < CameraPos.x)
			return;

		else if (CullPos.y > CameraPos.y + Resolution.y)
			return;

		else if (CullPos.y + Size.y < CameraPos.y)
			return;

		if (Current->m_Sequence->GetTextureType() == ETexture_Type::Sprite)
		{
			if (Current->m_Sequence->GetTexture()->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetDC(),
					(int)FrameData.Start.x, (int)FrameData.Start.y, (int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetColorKey());
				//출력할 핸들, 위치x, 위치y, 너비w, 높이h, 
				//이미지 핸들, 이미지의위치x, 이미지의 위치 y, 이미지의너비w, 이미지의 높이 h, 컬러키로 색상처리
			}

			else //일반 프레임 이미지 일시 
			{
				BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y, (int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetDC(),
					(int)FrameData.Start.x, (int)FrameData.Start.y, SRCCOPY);
				//출력할 핸들, 위치x, 위치y, 너비w, 높이h, 이미지의 시작지점 위치 x, y, 이미지의 출력방법(SRCCOPY: 원본 출력)
			}
		}

		else
		{
			if (Current->m_Sequence->GetTexture()->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetDC(Current->m_Frame),
					(int)FrameData.Start.x, (int)FrameData.Start.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetColorKey());
			}

			else
			{
				BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetDC(Current->m_Frame),
					(int)FrameData.Start.x, (int)FrameData.Start.y, SRCCOPY);
			}
		}
	}

	else
	{
		if (m_Texture)
		{
			Vector2	RenderLT;

			RenderLT = Pos - m_Pivot * m_Size;

			Vector2	CullPos = m_Pos - m_Pivot * m_Size;

			if (CullPos.x > CameraPos.x + Resolution.x)
				return;

			else if (CullPos.x + m_Size.x < CameraPos.x)
				return;

			else if (CullPos.y > CameraPos.y + Resolution.y)
				return;

			else if (CullPos.y + m_Size.y < CameraPos.y)
				return;

			if (m_Texture->GetEnableColorKey())
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					///////////////////////////////////////////////////
					if (m_MoveObject) {
						TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y+ (int)m_MovingObject,
							(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
							0, 0, (int)m_Size.x, (int)m_Size.y, m_Texture->GetColorKey());
					}
					else 
					{
							TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
								(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
								0, 0, (int)m_Size.x, (int)m_Size.y, m_Texture->GetColorKey());
					}
				}

				else
				{
				}
			}

			else
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
						0, 0, SRCCOPY);
				}

				else
				{
				}
			}
		}
	}

	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, DeltaTime);
		++iter;
	}

	m_PrevPos = m_Pos;
}

float CGameObject::InflictDamage(float Damage)
{
	return Damage;
}

void CGameObject::SetCollisionEnable(bool Enable)
{
	if (m_ColliderList.size())
	{
		m_ColliderList.front()->SetCollisionEnable(Enable);
	}	
}
