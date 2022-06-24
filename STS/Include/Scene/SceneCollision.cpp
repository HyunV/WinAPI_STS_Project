#include "SceneCollision.h"
#include "../Collision/Collider.h"
#include "../Input.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/Widget.h"

CSceneCollision::CSceneCollision() :
	m_MouseCollision(nullptr),
	m_MouseCollisionWidget(nullptr)
{
	m_vecCollider.reserve(500);
}

CSceneCollision::~CSceneCollision()
{
}

void CSceneCollision::AddCollider(CCollider* Collider)
{
	m_vecCollider.push_back(Collider);
}

void CSceneCollision::AddWidgetWindow(CWidgetWindow* Window)
{
	m_vecWidgetWindow.push_back(Window);
}

void CSceneCollision::CollisionMouse(float DeltaTime) //마우스 충돌이 우선
{
	//충돌체, 마우스 충돌하기 전에 ui를 먼저 체크
	size_t WindowCount = m_vecWidgetWindow.size(); //모든 위젯을 가져온다.

	bool MouseCollision = false;

	if (WindowCount >= 1) //사이즈 1개 이상일때 정렬 수행
	{
		if (WindowCount > 1)
			std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CSceneCollision::SortWidget);

		Vector2	MousePos = CInput::GetInst()->GetMousePos(); //마우스 포지션 가져온다.
		//모든 물체에 대해 충돌처리 수행

		CWidget* result = nullptr;

		for (size_t i = 0; i < WindowCount; ++i)
		{
			m_vecWidgetWindow[i]->SortCollision();

			if (m_vecWidgetWindow[i]->CollisionMouse(&result, MousePos))
			{
				if (m_MouseCollisionWidget && m_MouseCollisionWidget != result) //충돌이 다르면
					m_MouseCollisionWidget->CollisionMouseReleaseCallback(); //마우스 올라간 상태 아니라 판단

				// 위젯이 충돌되었는데 기존에 마우스와 충돌되던 충돌체가 있을 경우
				if (m_MouseCollision)
				{
					m_MouseCollision->SetMouseCollision(false);
					m_MouseCollision->CallMouseCollisionEnd(CInput::GetInst()->GetMouseWorldPos());
					m_MouseCollision = nullptr;
				}

				m_MouseCollisionWidget = result;

				MouseCollision = true;

				break;
			}
		}
	}


	if(!MouseCollision) //마우스가 ui랑 충돌된게 없을경우
	{
		if (m_MouseCollisionWidget)
		{
			m_MouseCollisionWidget->CollisionMouseReleaseCallback();
			m_MouseCollisionWidget = nullptr;
		}

		size_t	Size = m_vecCollider.size(); //보여지는 모든 ui에 대해서 갖고있게 된다. 

		if (Size >= 1) //비어있지 않으면
		{
			if (Size > 1)  //정렬은 1개 이상일 때 진행
				std::sort(m_vecCollider.begin(), m_vecCollider.end(), CSceneCollision::SortY);
			//vector는 기본적으로 sort기능이 제공되지 않기 때문에 알고리즘
			//가장 앞에 있는 물체와 충돌하기 위한 내림차순 정렬
			Vector2	MouseWorldPos = CInput::GetInst()->GetMouseWorldPos(); //마우스 월드위치 가져옴
			CollisionProfile* MouseProfile = CInput::GetInst()->GetMouseProfile(); //마우스 프로필 가져옴
			
			//bool	MouseCollision = false; //충돌된 물체가 있는지 판단하는 변수

			for (size_t i = 0; i < Size; ++i) //전체 반복
			{
				CCollider* Dest = m_vecCollider[i];
				
				// 충돌 Profile을 가져와서 충돌시켜야 하는 물체인지 판단한다.
				const CollisionProfile* SrcProfile = MouseProfile;
				const CollisionProfile* DestProfile = Dest->GetProfile();
				// Profile에는 다른 채널과 상호작용을 어떻게 해야되는지가 정해져있다.
					// 그러므로 상대방 채널번째의 상호작용을 얻어와서 무시인지 충돌인지를 알아내야 한다.
				
				ECollision_Interaction	SrcInteraction = SrcProfile->vecCollisionInteraction[(int)DestProfile->Channel];
				ECollision_Interaction	DestInteraction = DestProfile->vecCollisionInteraction[(int)SrcProfile->Channel];
				
				// 둘중 하나라도 무시하기로 되어 있다면 충돌을 멈춘다.
				if (SrcInteraction == ECollision_Interaction::Ignore ||
					DestInteraction == ECollision_Interaction::Ignore)
					continue;
				
				// 충돌을 체크한다.
				if (Dest->CollisionMouse(MouseWorldPos))
				{
					MouseCollision = true;
					
					// 이제 막 충돌을 시작할때.
					if (!Dest->GetMouseCollision())
					{
						// 기존에 충돌되던 물체가 있을 경우 마우스와의 충돌을 해제한다.
						if (m_MouseCollision)
							m_MouseCollision->SetMouseCollision(false);
						
						Dest->SetMouseCollision(true); //마우스 충돌되고있다(활성화)
						
						// 충돌 시작 함수를 호출한다.
						Dest->CallMouseCollisionBegin(MouseWorldPos);
					}

					m_MouseCollision = Dest;
					
					break; //하나라도 충돌이 일어났다면 break 시켜준다
				}
				// 충돌이 되던 물체가 서로 떨어질때 (충돌이 안됨)
				else if (Dest->GetMouseCollision())
				{
					m_MouseCollision->CallMouseCollisionEnd(MouseWorldPos);
					m_MouseCollision->SetMouseCollision(false);
					m_MouseCollision = nullptr;
				}
			}
			// MouseCollision 변수가 false를 유지하고 있다면 어떤 물체와도 충돌이 안되었다는 것이다.
				// 그러므로 이 경우에는 기존에 충돌되고 있던 물체가 있다면 지금은 충돌이 안되는 것이기
				// 때문에 예외처리를 해주어야 한다.
			if (!MouseCollision)
			{
				if (m_MouseCollision)
				{
					m_MouseCollision->SetMouseCollision(false);
					m_MouseCollision = nullptr;
				}
			}
		}
	}
}

void CSceneCollision::Collision(float DeltaTime) //반복 돌려 각각 충돌 체크
{
	size_t	Size = m_vecCollider.size();
	if (Size > 1)
	{ //충돌체들간 정렬해서 비교
		for (size_t i = 0 ; i < Size - 1; ++i)
		{
			CCollider* Src = m_vecCollider[i]; //Src : 충돌체 A

			for (size_t j = i + 1; j < Size; ++j)
			{
				CCollider* Dest = m_vecCollider[j]; //Dest : 충돌체 B

				if (Src->GetOwner() == Dest->GetOwner()) //충돌체 A와 B가 같은 녀석이면 충돌할 이유가 없다.
					//예를들면 Head와 Body가 부딫힐 이유가 없다
					continue;

				// 충돌 Profile을 가져와서 충돌시켜야 하는 물체인지 판단한다.
				const CollisionProfile* SrcProfile = Src->GetProfile();
				const CollisionProfile* DestProfile = Dest->GetProfile();

				// Profile에는 다른 채널과 상호작용을 어떻게 해야되는지가 정해져있다.
				// 그러므로 상대방 채널번째의 상호작용을 얻어와서 무시인지 충돌인지를 알아내야 한다.
				ECollision_Interaction	SrcInteraction = SrcProfile->vecCollisionInteraction[(int)DestProfile->Channel];
				ECollision_Interaction	DestInteraction = DestProfile->vecCollisionInteraction[(int)SrcProfile->Channel];

				// 둘중 하나라도 무시하기로 되어 있다면 충돌을 멈춘다.
				if (SrcInteraction == ECollision_Interaction::Ignore ||
					DestInteraction == ECollision_Interaction::Ignore)
					continue;


				// 충돌을 체크한다.
				if (Src->Collision(Dest)) //충돌이 되었다
				{
					// 이제 막 충돌을 시작할때. (충돌이 시작되었는데 리스트에 없다 -> 이제 막 충돌을 시작했다)
					if (!Src->CheckCollisionList(Dest))
					{
						// 서로에게 상대방 충돌체를 충돌목록에 등록한다.
						Src->AddCollisionList(Dest);
						Dest->AddCollisionList(Src);

						// 충돌 시작 함수를 호출한다.
						Src->CallCollisionBegin(Dest);
						Dest->CallCollisionBegin(Src);
					}
				}

				// 충돌이 되던 물체가 서로 떨어질때(충돌은 안됐는데 리스트 목록에 있다. -> 이제 막 충돌이 끝나는 상태)
				else if (Src->CheckCollisionList(Dest))
				{
					// 서로 목록에서 충돌체를 지워준다.
					Src->DeleteCollisionList(Dest);
					Dest->DeleteCollisionList(Src);

					// 충돌 종료 함수를 호출한다.
					Src->CallCollisionEnd(Dest);
					Dest->CallCollisionEnd(Src);
					
					//충돌 시작과 끝을 나눈이유는 충돌이 진행중일때 계속해서 업데이트를 해야 할 일이 있으니까(ex 힐장판)
					// 그  CollisionBegin 같은데서 업데이트 하면 되므로 무겁게 계속 콜백할 필요는 없다.
				}
			}
		}
	}

	m_vecCollider.clear(); //끝나면 매 프레임마다 클리어 해준다.
	m_vecWidgetWindow.clear();
}

//내림차순으로 정렬
bool CSceneCollision::SortY(CCollider* Src, CCollider* Dest)
{
	//부호 주목
	return Src->GetBottom() > Dest->GetBottom();
}

bool CSceneCollision::SortWidget(CWidgetWindow* Src, CWidgetWindow* Dest)
{
	return Src->GetZOrder() > Dest->GetZOrder();
}
