#pragma once
#include "../GameInfo.h"
//�浹 ������ �������ִ� Ŭ����
//�߰��� �������� ����� �ֵ� ����Ʈ�� ���� �������ش�.
//�ݸ����� �΋H�� �Լ��� �����̰�, �ݶ��̴��� ��ü 
class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	std::vector<class CCollider*> m_vecCollider;
	std::vector<class CWidgetWindow*>	m_vecWidgetWindow; // �� ������ �� �浹 �켱����, ��� �켱������ �����ְ� ������ �� �ְ� ���ش�.
	class CCollider* m_MouseCollision;
	class CWidget* m_MouseCollisionWidget;
	int m_MouseCollisionCount;
public:
	//������Ʈ ���� �Լ��� �ʿ���� �浹ó���� �����״�.
	void AddCollider(class CCollider* Collider);
	void AddWidgetWindow(class CWidgetWindow* Window);
	void CollisionMouse(float DeltaTime);
	void Collision(float DeltaTime);

private:
	static bool SortY(class CCollider* Src, class CCollider* Dest);
	//������������ �����ؾ� ���� �տ� �ִ� ��ü�� �浹�� �Ͼ��.

	static bool SortWidget(class CWidgetWindow* Src, class CWidgetWindow* Dest);
	static bool SortCard(class CCollider* Src, class CCollider* Dest);
	static bool SelectedSort(class CCollider* Src, class CCollider* Dest);
};

