#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "SceneResource.h"
#include "Camera.h"
#include "SceneCollision.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/CardManager.h"

CScene::CScene()
{
	m_Resource = new CSceneResource;
	m_Camera = new CCamera;
	m_Collision = new CSceneCollision;
	m_SceneUsedCard = false;
	m_BlackLayerSwitch = false;
}

CScene::~CScene()
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].clear();
	}
	SAFE_DELETE(m_Collision);
	SAFE_DELETE(m_Camera);
	SAFE_DELETE(m_Resource);
}

void CScene::SetTileMap(CTileMap* TileMap)
{
	m_TileMap = TileMap;
}

void CScene::SetPlayer(CGameObject* Player)
{
	m_Player = Player;
}

void CScene::SetCameraObj(CGameObject* Camera)
{
	m_CameraObj = Camera;
}

void CScene::SetMonster(CGameObject* Monster)
{
	m_Monster = Monster;
}

void CScene::SetMap(CGameObject* Map)
{
	m_Map = Map;
}

bool CScene::Init()
{
	return true;
}

void CScene::Update(float DeltaTime)
{
	std::list<CSharedPtr<class CGameObject>>::iterator iter;
	std::list<CSharedPtr<class CGameObject>>::iterator iterEnd;
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		iter = m_ObjList[i].begin();
		iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive()) //활성화 false로 되어있다면
			{
				//리스트에서 제거하는 순간 shared ptr의 소멸자가 호출되어 rc가 감소
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end(); //이터레이터 특성 상 다시 받아와야됨
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

	auto iter1 = m_vecWidgetWindow.begin();
	auto iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->Update(DeltaTime);
		++iter1;
	}

	m_Camera->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
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

	auto iter1 = m_vecWidgetWindow.begin();
	auto iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->PostUpdate(DeltaTime);
		++iter1;
	}

	iter1 = m_vecWidgetWindow.begin();
	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		m_Collision->AddWidgetWindow(*iter1); // 콜리전이 매 프레임마다 위젯윈도우를 가진다.
		//끝나면 씬콜리저 클래스에서 클리어 함수가 실행된다. 새로 받고 정리 -> 반복
		++iter1;
	}

	m_Collision->CollisionMouse(DeltaTime);

	m_Collision->Collision(DeltaTime);
}

void CScene::Render(HDC hDC, float DeltaTime)
{
	//오브젝트 그리고 위젯 컴포넌트를 깔게 재설계
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].sort(SortY);
		m_ObjList[i].sort(SortCard2);
		m_ObjList[i].sort(SortCard);


		auto iter = m_ObjList[i].begin();
		auto iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
				continue;
			}			
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Render(hDC, DeltaTime);

			auto iter2 = m_WidgetComponentList.begin();
			auto iterEnd2 = m_WidgetComponentList.end();
			for (; iter2 != iterEnd2;)
			{
				if (!(*iter2)->GetActive())
				{
					iter2 = m_WidgetComponentList.erase(iter2);
					iterEnd2 = m_WidgetComponentList.end();
					continue;
				}
				++iter2;
			}
			
			iter2 = m_WidgetComponentList.begin();
			iterEnd2 = m_WidgetComponentList.end();
			for (; iter2 != iterEnd2;)
			{
				if (!(*iter2)->GetWidget()->GetEnable())
				{
					iter2++;
					continue;
				}
				if ((*iter2)->GetOwner() == (*iter)) {
					(*iter2)->Render(hDC, DeltaTime);
				}
				++iter2;
			}
			//오브젝트 이터 
			++iter;
		}
	}

	// WidgetComponent 출력
	 //제거될 위젯 컴포넌트는 제거한다.
	//{
	//	auto	iter = m_WidgetComponentList.begin();
	//	auto	iterEnd = m_WidgetComponentList.end();
	//	for (; iter != iterEnd;)
	//	{		
	//		if (!(*iter)->GetActive())
	//		{
	//			iter = m_WidgetComponentList.erase(iter);
	//			iterEnd = m_WidgetComponentList.end();
	//			continue;
	//		}
	//		++iter;
	//	}

	//	// 정렬한다.
	//	m_WidgetComponentList.sort(SortYWidgetComponent);

	//	iter = m_WidgetComponentList.begin();
	//	iterEnd = m_WidgetComponentList.end();

	//	for (; iter != iterEnd; ++iter)
	//	{
	//		if (!(*iter)->GetOwner()->GetEnable())
	//		{			
	//			continue;
	//		}

	//		(*iter)->Render(hDC, DeltaTime);
	//	}
	//}

	// 월드공간의 물체가 출력된 이후에 UI를 출력한다.
	if (m_vecWidgetWindow.size() > 1)
		std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CScene::SortWidget);

	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->Render(hDC, DeltaTime);
		++iter1;
	}

	// UI를 출력한 이후에 마우스를 출력한다.
}

bool CScene::SortY(const CSharedPtr<class CGameObject>& Src, const CSharedPtr<class CGameObject>& Dest)
{
	//오브젝트 출력을 레이어 기준으로 구현할 예정 백그라운드 -> 오브젝트 -> 이펙트
	// 발밑 기준으로 정렬을 진행해야 하기 때문에 발밑의 Y를 구해준다.
	float SrcY = Src->GetPos().y + (1.f - Src->GetPivot().y) * Src->GetSize().y; //(오브젝트 y 전체 길이 )
	// 피봇이 만약 0.7이면 0.3만큼 더해서 y를 구해줘야 한다.
	// GetPos(0.7) + (0.3)
	float	DestY = Dest->GetPos().y + (1.f - Dest->GetPivot().y) * Dest->GetSize().y;
	
	return SrcY < DestY;
}

bool CScene::SortYWidgetComponent(const CSharedPtr<class CWidgetComponent>& Src, const CSharedPtr<class CWidgetComponent>& Dest)
{
	return Src->GetBottom() < Dest->GetBottom();
}

bool CScene::SortWidget(const CSharedPtr<CWidgetWindow>& Src, const CSharedPtr<CWidgetWindow>& Dest)
{
	return Src->GetZOrder() < Dest->GetZOrder();
}

bool CScene::SortCard(const CSharedPtr<class CGameObject>& Src, const CSharedPtr<class CGameObject>& Dest)
{

	return Src->GetSelectedCard() < Dest->GetSelectedCard();
}

bool CScene::SortCard2(const CSharedPtr<class CGameObject>& Src, const CSharedPtr<class CGameObject>& Dest)
{

	return Src->GetPos().x < Dest->GetPos().x;
}
