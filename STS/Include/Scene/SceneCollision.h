#pragma once
#include "../GameInfo.h"
//충돌 로직을 관리해주는 클래스
//중간에 없어지고 생기는 애들 리스트를 만들어서 관리해준다.
//콜리전은 부딫힌 함수들 모음이고, 콜라이더는 객체 
class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	std::vector<class CCollider*> m_vecCollider;
	std::vector<class CWidgetWindow*>	m_vecWidgetWindow; // 이 위젯들 간 충돌 우선순위, 출력 우선순위를 정해주고 세팅할 수 있게 해준다.
	class CCollider* m_MouseCollision;
	class CWidget* m_MouseCollisionWidget;
	int m_MouseCollisionCount;
public:
	//업데이트 관련 함수는 필요없고 충돌처리만 만들어뒀다.
	void AddCollider(class CCollider* Collider);
	void AddWidgetWindow(class CWidgetWindow* Window);
	void CollisionMouse(float DeltaTime);
	void Collision(float DeltaTime);

private:
	static bool SortY(class CCollider* Src, class CCollider* Dest);
	//내림차순으로 정렬해야 제일 앞에 있는 물체와 충돌이 일어난다.

	static bool SortWidget(class CWidgetWindow* Src, class CWidgetWindow* Dest);
	static bool SortCard(class CCollider* Src, class CCollider* Dest);
	static bool SelectedSort(class CCollider* Src, class CCollider* Dest);
};

