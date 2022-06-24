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

void CSceneCollision::CollisionMouse(float DeltaTime) //���콺 �浹�� �켱
{
	//�浹ü, ���콺 �浹�ϱ� ���� ui�� ���� üũ
	size_t WindowCount = m_vecWidgetWindow.size(); //��� ������ �����´�.

	bool MouseCollision = false;

	if (WindowCount >= 1) //������ 1�� �̻��϶� ���� ����
	{
		if (WindowCount > 1)
			std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CSceneCollision::SortWidget);

		Vector2	MousePos = CInput::GetInst()->GetMousePos(); //���콺 ������ �����´�.
		//��� ��ü�� ���� �浹ó�� ����

		CWidget* result = nullptr;

		for (size_t i = 0; i < WindowCount; ++i)
		{
			m_vecWidgetWindow[i]->SortCollision();

			if (m_vecWidgetWindow[i]->CollisionMouse(&result, MousePos))
			{
				if (m_MouseCollisionWidget && m_MouseCollisionWidget != result) //�浹�� �ٸ���
					m_MouseCollisionWidget->CollisionMouseReleaseCallback(); //���콺 �ö� ���� �ƴ϶� �Ǵ�

				// ������ �浹�Ǿ��µ� ������ ���콺�� �浹�Ǵ� �浹ü�� ���� ���
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


	if(!MouseCollision) //���콺�� ui�� �浹�Ȱ� �������
	{
		if (m_MouseCollisionWidget)
		{
			m_MouseCollisionWidget->CollisionMouseReleaseCallback();
			m_MouseCollisionWidget = nullptr;
		}

		size_t	Size = m_vecCollider.size(); //�������� ��� ui�� ���ؼ� �����ְ� �ȴ�. 

		if (Size >= 1) //������� ������
		{
			if (Size > 1)  //������ 1�� �̻��� �� ����
				std::sort(m_vecCollider.begin(), m_vecCollider.end(), CSceneCollision::SortY);
			//vector�� �⺻������ sort����� �������� �ʱ� ������ �˰���
			//���� �տ� �ִ� ��ü�� �浹�ϱ� ���� �������� ����
			Vector2	MouseWorldPos = CInput::GetInst()->GetMouseWorldPos(); //���콺 ������ġ ������
			CollisionProfile* MouseProfile = CInput::GetInst()->GetMouseProfile(); //���콺 ������ ������
			
			//bool	MouseCollision = false; //�浹�� ��ü�� �ִ��� �Ǵ��ϴ� ����

			for (size_t i = 0; i < Size; ++i) //��ü �ݺ�
			{
				CCollider* Dest = m_vecCollider[i];
				
				// �浹 Profile�� �����ͼ� �浹���Ѿ� �ϴ� ��ü���� �Ǵ��Ѵ�.
				const CollisionProfile* SrcProfile = MouseProfile;
				const CollisionProfile* DestProfile = Dest->GetProfile();
				// Profile���� �ٸ� ä�ΰ� ��ȣ�ۿ��� ��� �ؾߵǴ����� �������ִ�.
					// �׷��Ƿ� ���� ä�ι�°�� ��ȣ�ۿ��� ���ͼ� �������� �浹������ �˾Ƴ��� �Ѵ�.
				
				ECollision_Interaction	SrcInteraction = SrcProfile->vecCollisionInteraction[(int)DestProfile->Channel];
				ECollision_Interaction	DestInteraction = DestProfile->vecCollisionInteraction[(int)SrcProfile->Channel];
				
				// ���� �ϳ��� �����ϱ�� �Ǿ� �ִٸ� �浹�� �����.
				if (SrcInteraction == ECollision_Interaction::Ignore ||
					DestInteraction == ECollision_Interaction::Ignore)
					continue;
				
				// �浹�� üũ�Ѵ�.
				if (Dest->CollisionMouse(MouseWorldPos))
				{
					MouseCollision = true;
					
					// ���� �� �浹�� �����Ҷ�.
					if (!Dest->GetMouseCollision())
					{
						// ������ �浹�Ǵ� ��ü�� ���� ��� ���콺���� �浹�� �����Ѵ�.
						if (m_MouseCollision)
							m_MouseCollision->SetMouseCollision(false);
						
						Dest->SetMouseCollision(true); //���콺 �浹�ǰ��ִ�(Ȱ��ȭ)
						
						// �浹 ���� �Լ��� ȣ���Ѵ�.
						Dest->CallMouseCollisionBegin(MouseWorldPos);
					}

					m_MouseCollision = Dest;
					
					break; //�ϳ��� �浹�� �Ͼ�ٸ� break �����ش�
				}
				// �浹�� �Ǵ� ��ü�� ���� �������� (�浹�� �ȵ�)
				else if (Dest->GetMouseCollision())
				{
					m_MouseCollision->CallMouseCollisionEnd(MouseWorldPos);
					m_MouseCollision->SetMouseCollision(false);
					m_MouseCollision = nullptr;
				}
			}
			// MouseCollision ������ false�� �����ϰ� �ִٸ� � ��ü�͵� �浹�� �ȵǾ��ٴ� ���̴�.
				// �׷��Ƿ� �� ��쿡�� ������ �浹�ǰ� �ִ� ��ü�� �ִٸ� ������ �浹�� �ȵǴ� ���̱�
				// ������ ����ó���� ���־�� �Ѵ�.
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

void CSceneCollision::Collision(float DeltaTime) //�ݺ� ���� ���� �浹 üũ
{
	size_t	Size = m_vecCollider.size();
	if (Size > 1)
	{ //�浹ü�鰣 �����ؼ� ��
		for (size_t i = 0 ; i < Size - 1; ++i)
		{
			CCollider* Src = m_vecCollider[i]; //Src : �浹ü A

			for (size_t j = i + 1; j < Size; ++j)
			{
				CCollider* Dest = m_vecCollider[j]; //Dest : �浹ü B

				if (Src->GetOwner() == Dest->GetOwner()) //�浹ü A�� B�� ���� �༮�̸� �浹�� ������ ����.
					//������� Head�� Body�� �΋H�� ������ ����
					continue;

				// �浹 Profile�� �����ͼ� �浹���Ѿ� �ϴ� ��ü���� �Ǵ��Ѵ�.
				const CollisionProfile* SrcProfile = Src->GetProfile();
				const CollisionProfile* DestProfile = Dest->GetProfile();

				// Profile���� �ٸ� ä�ΰ� ��ȣ�ۿ��� ��� �ؾߵǴ����� �������ִ�.
				// �׷��Ƿ� ���� ä�ι�°�� ��ȣ�ۿ��� ���ͼ� �������� �浹������ �˾Ƴ��� �Ѵ�.
				ECollision_Interaction	SrcInteraction = SrcProfile->vecCollisionInteraction[(int)DestProfile->Channel];
				ECollision_Interaction	DestInteraction = DestProfile->vecCollisionInteraction[(int)SrcProfile->Channel];

				// ���� �ϳ��� �����ϱ�� �Ǿ� �ִٸ� �浹�� �����.
				if (SrcInteraction == ECollision_Interaction::Ignore ||
					DestInteraction == ECollision_Interaction::Ignore)
					continue;


				// �浹�� üũ�Ѵ�.
				if (Src->Collision(Dest)) //�浹�� �Ǿ���
				{
					// ���� �� �浹�� �����Ҷ�. (�浹�� ���۵Ǿ��µ� ����Ʈ�� ���� -> ���� �� �浹�� �����ߴ�)
					if (!Src->CheckCollisionList(Dest))
					{
						// ���ο��� ���� �浹ü�� �浹��Ͽ� ����Ѵ�.
						Src->AddCollisionList(Dest);
						Dest->AddCollisionList(Src);

						// �浹 ���� �Լ��� ȣ���Ѵ�.
						Src->CallCollisionBegin(Dest);
						Dest->CallCollisionBegin(Src);
					}
				}

				// �浹�� �Ǵ� ��ü�� ���� ��������(�浹�� �ȵƴµ� ����Ʈ ��Ͽ� �ִ�. -> ���� �� �浹�� ������ ����)
				else if (Src->CheckCollisionList(Dest))
				{
					// ���� ��Ͽ��� �浹ü�� �����ش�.
					Src->DeleteCollisionList(Dest);
					Dest->DeleteCollisionList(Src);

					// �浹 ���� �Լ��� ȣ���Ѵ�.
					Src->CallCollisionEnd(Dest);
					Dest->CallCollisionEnd(Src);
					
					//�浹 ���۰� ���� ���������� �浹�� �������϶� ����ؼ� ������Ʈ�� �ؾ� �� ���� �����ϱ�(ex ������)
					// ��  CollisionBegin �������� ������Ʈ �ϸ� �ǹǷ� ���̰� ��� �ݹ��� �ʿ�� ����.
				}
			}
		}
	}

	m_vecCollider.clear(); //������ �� �����Ӹ��� Ŭ���� ���ش�.
	m_vecWidgetWindow.clear();
}

//������������ ����
bool CSceneCollision::SortY(CCollider* Src, CCollider* Dest)
{
	//��ȣ �ָ�
	return Src->GetBottom() > Dest->GetBottom();
}

bool CSceneCollision::SortWidget(CWidgetWindow* Src, CWidgetWindow* Dest)
{
	return Src->GetZOrder() > Dest->GetZOrder();
}
