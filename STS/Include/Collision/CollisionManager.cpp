#include "CollisionManager.h"
#include "ColliderBox.h"
#include "ColliderCircle.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CCollisionManager::Init()
{
	//�浹 ���� ���� ���̺� 

	CreateProfile("Default", ECollision_Channel::Default, true); //����������� ����Ʈ���ڷ� �浹 ó��
	CreateProfile("Player", ECollision_Channel::Player, true, ECollision_Interaction::Ignore);
	CreateProfile("Monster", ECollision_Channel::Monster, true, ECollision_Interaction::Ignore);
	CreateProfile("PlayerAttack", ECollision_Channel::PlayerAttack, true, ECollision_Interaction::Ignore);
	CreateProfile("MonsterAttack", ECollision_Channel::MonsterAttack, true, ECollision_Interaction::Ignore);
	CreateProfile("Mouse", ECollision_Channel::Mouse, true, ECollision_Interaction::Collision);

	CreateProfile("Card", ECollision_Channel::Card, true, ECollision_Interaction::Ignore);

	//�÷��̾�, ����, ���� �� �浹ó�� ��� ���÷� ��Ƴ���

	//�� ��ȣ�ۿ� ����
	SetCollisionInteraction("Player", ECollision_Channel::Default, ECollision_Interaction::Collision);
	//�÷��̾� : ����Ʈ ä���� ������Ʈ(�浹) ���踦 �浹�� ó�� 

	SetCollisionInteraction("Player", ECollision_Channel::MonsterAttack, ECollision_Interaction::Collision);
	//�÷��̾ ���� ���ݿ� ���� �� �ְ� �ȴ�.

	SetCollisionInteraction("Player", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	//�÷��̾ ���Ϳ� ����
	SetCollisionInteraction("Player", ECollision_Channel::Mouse, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Mouse, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Card, ECollision_Interaction::Collision);

	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Default, ECollision_Interaction::Collision);
	//���� : ����Ʈ�ʹ� �浹ó�� -> ���� �΋H���� ����� �� �ְ�
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Monster, ECollision_Interaction::Collision);

	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Player, ECollision_Interaction::Collision);

	SetCollisionInteraction("Card", ECollision_Channel::Mouse, ECollision_Interaction::Collision);
	SetCollisionInteraction("Card", ECollision_Channel::Monster, ECollision_Interaction::Collision);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& Name, ECollision_Channel Channel, bool Enable, ECollision_Interaction BaseIteraction)
{
	CollisionProfile* Profile = FindProfile(Name); //�ҷ�����

	if (Profile) //�̹� ���� ��
		return false;

	Profile = new CollisionProfile; //�������� ����ü ����

	//�Է��� ���� �������
	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;
	Profile->vecCollisionInteraction.resize((size_t)ECollision_Channel::Max); //ä�� 5���̴� 5����ŭ �������� ����

	for (int i = 0; i < (int)ECollision_Channel::Max; ++i)
	{
		Profile->vecCollisionInteraction[i] = BaseIteraction;  //���� ä�ε� �浹, ���� ���� 
		//�ٸ� �������ϰ� �񱳽� ���� �浹 or ���� ���� �̷��� ����
	}

	m_mapProfile.insert(std::make_pair(Name, Profile)); //�ڷᱸ���� ����صд�.

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& Name, ECollision_Channel Channel, ECollision_Interaction Iteraction)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (!Profile) //find ���н�
		return false;

	Profile->vecCollisionInteraction[(int)Channel] = Iteraction;
	//�� ä�� �ε����� ���� ��ȣ�ۿ��� ���ڷ� ���� Iteraction(�浹, ����)���� ���ش�

	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& Name)
{
	auto	iter = m_mapProfile.find(Name);

	if (iter == m_mapProfile.end())
		return nullptr;

	return iter->second;
}

bool CCollisionManager::CollisionBoxToBox(Vector2& HitPoint, CColliderBox* Src, CColliderBox* Dest)
{
	if (CollisionBoxToBox(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}
	return false;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& HitPoint, CColliderCircle* Src, CColliderCircle* Dest)
{
	if (CollisionCircleToCircle(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;

	}
	return false;
}



bool CCollisionManager::CollisionBoxToCircle(Vector2& HitPoint, CColliderBox* Src, CColliderCircle* Dest)
{
	if (CollisionBoxToCircle(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& HitPoint, const Vector2& Src, CColliderBox* Dest)
{
	if (CollisionPointToBox(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& HitPoint, const Vector2& Src, CColliderCircle* Dest)
{
	if (CollisionPointToCircle(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

//bool CCollisionManager::CollisionCircleToBox(Vector2& HitPoint, CColliderCircle* Src, CColliderBox* Dest)
//{
//	if (CollisionCircleToBox(HitPoint, Src->GetInfo(), Dest->GetInfo()))
//	{
//		Dest->m_HitPoint = HitPoint;
//		return true;
//	}
//	return false;
//}

bool CCollisionManager::CollisionBoxToBox(Vector2& HitPoint, const BoxInfo& Src, const BoxInfo& Dest)
{
	//����κ� ���� �׸��׷����鼭 �����غ���
	//�浹�� �ȵǴ� ����
	if (Src.LT.x > Dest.RB.x)
		return false;

	else if (Src.LT.y > Dest.RB.y)
		return false;

	else if (Src.RB.x < Dest.LT.x)
		return false;

	else if (Src.RB.y < Dest.LT.y)
		return false;

	float Left = Src.LT.x > Dest.LT.x ? Src.LT.x : Dest.LT.x; //ū ���� ����
	float Top = Src.LT.y > Dest.LT.y ? Src.LT.y : Dest.LT.y; //ū ���� ����
	float Right = Src.RB.x < Dest.RB.x ? Src.RB.x : Dest.RB.x; // ���� ���� ����
	float Bottom = Src.RB.y < Dest.RB.y ? Src.RB.y : Dest.RB.y;// ���� ���� ����

	//LT, RB�� ���ϰ� 2�� �����ָ� ������ �簢�� ��� �κ��� ���� ��
	HitPoint.x = (Left + Right) / 2.f; //�����պκ�
	HitPoint.y = (Top + Bottom) / 2.f;

	return true;
}
//�̰͵� ���α�
bool CCollisionManager::CollisionCircleToCircle(Vector2& HitPoint, const CircleInfo& Src, const CircleInfo& Dest)
{
	// ���� ������ �Ÿ��� ���Ѵ�.
	float Dist = Src.Center.Distance(Dest.Center);

	bool result = Dist <= Src.Radius + Dest.Radius;

	HitPoint = (Src.Center + Dest.Center) / 2.f;

	return result;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& HitPoint, const BoxInfo& Src, const CircleInfo& Dest)
{
	// ���� ������ �簢���� ��, �� ���� Ȥ�� ��, �Ʒ� ������ �����ϴ��� �Ǵ��Ѵ�.
	if ((Src.LT.x <= Dest.Center.x && Dest.Center.x <= Src.RB.x) ||
		(Src.LT.y <= Dest.Center.y && Dest.Center.y <= Src.RB.y))
	{
		// �簢���� ���� ��������ŭ Ȯ���Ѵ�.
		BoxInfo	RC = Src;
		RC.LT.x -= Dest.Radius;
		RC.LT.y -= Dest.Radius;
		RC.RB.x += Dest.Radius;
		RC.RB.y += Dest.Radius;

		// Ȯ��� �簢�� �ȿ� ���� ������ ���´ٸ� �浹�� ���̴�.
		if (RC.LT.x > Dest.Center.x)
			return false;

		else if (RC.LT.y > Dest.Center.y)
			return false;

		else if (RC.RB.x < Dest.Center.x)
			return false;

		else if (RC.RB.y < Dest.Center.y)
			return false;

		// ��Ʈ����Ʈ.
		BoxInfo	CircleBox;
		CircleBox.LT = Dest.Center - Dest.Radius;
		CircleBox.RB = Dest.Center + Dest.Radius;

		float Left = Src.LT.x > CircleBox.LT.x ? Src.LT.x : CircleBox.LT.x;
		float Top = Src.LT.y > CircleBox.LT.y ? Src.LT.y : CircleBox.LT.y;
		float Right = Src.RB.x < CircleBox.RB.x ? Src.RB.x : CircleBox.RB.x;
		float Bottom = Src.RB.y < CircleBox.RB.y ? Src.RB.y : CircleBox.RB.y;

		HitPoint.x = (Left + Right) / 2.f;
		HitPoint.y = (Top + Bottom) / 2.f;

		return true;
	}

	Vector2	Pos[4] =
	{
		Src.LT,
		Vector2(Src.RB.x, Src.LT.y),
		Vector2(Src.LT.x, Src.RB.y),
		Src.RB
	};

	// 4���� ���� �ϳ��� �� �ȿ� ���´ٸ� �浹�� ���̴�.
	for (int i = 0; i < 4; ++i)
	{
		float Dist = Dest.Center.Distance(Pos[i]);

		if (Dist <= Dest.Radius)
		{
			BoxInfo	CircleBox;
			CircleBox.LT = Dest.Center - Dest.Radius;
			CircleBox.RB = Dest.Center + Dest.Radius;

			float Left = Src.LT.x > CircleBox.LT.x ? Src.LT.x : CircleBox.LT.x;
			float Top = Src.LT.y > CircleBox.LT.y ? Src.LT.y : CircleBox.LT.y;
			float Right = Src.RB.x < CircleBox.RB.x ? Src.RB.x : CircleBox.RB.x;
			float Bottom = Src.RB.y < CircleBox.RB.y ? Src.RB.y : CircleBox.RB.y;

			HitPoint.x = (Left + Right) / 2.f;
			HitPoint.y = (Top + Bottom) / 2.f;

			return true;
		}
	}

	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& HitPoint, const Vector2& Src, const BoxInfo& Dest)
{
	//�簢�� �ȿ� ���� �ִٸ� true
	if (Dest.LT.x > Src.x)
		return false;

	else if (Dest.LT.y > Src.y)
		return false;

	else if (Dest.RB.x < Src.x)
		return false;

	else if (Dest.RB.y < Src.y)
		return false;

	HitPoint = Src;

	return true;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& HitPoint, const Vector2& Src, const CircleInfo& Dest)
{
	//�������� ���� ���� �� ���� distance�� ���غ���
	//�� ���̸� ���ؼ� �� �Ÿ��� ���������� �۰ų� ������ �浹
	float Dist = Dest.Center.Distance(Src);

	if (Dist <= Dest.Radius)
	{
		HitPoint = Src;

		return true;
	}

	return false;
}

/*
//������ § �ڵ� 
bool CCollisionManager::CollisionCircleToBox(Vector2& HitPoint, const CircleInfo& Src, const BoxInfo& Dest)
{
	//SRC : Circle
	//Dest : Box

	//1. ���� ������ ��ŭ �ڽ��� ũ�⸦ �ø���.
	float Left = Dest.LT.x - Src.Radius;
	float Top = Dest.LT.y - Src.Radius;
	float Right = Dest.RB.x + Src.Radius;
	float Bottom = Dest.RB.y + Src.Radius;

	//�浹 ó�� 1. Ȯ���� �簢���� ���� �߽��� ������ 
	
	//�̰� �ݴ�� ó������
	if (Src.Center.x < Left)
		return false;
	else if (Src.Center.y < Top)
		return false;
	else if (Src.Center.x > Right)
		return false;
	else if (Src.Center.y > Bottom)
		return false;

	//���� ó�� 2. �簢���� �������� �� �ȿ� ���� �浹
	Vector2 LeftTop(Left, Top);
	Vector2 RightTop(Right, Top);
	Vector2 LeftBottom(Left, Bottom);
	Vector2 RightBottom(Right, Bottom);

	float DistLeftTop = Src.Center.Distance(LeftTop);
	float DistRightTop = Src.Center.Distance(RightTop);
	float DistLeftBottom = Src.Center.Distance(LeftBottom);
	float DistRightBottom = Src.Center.Distance(RightBottom);

	if (DistLeftTop > Src.Radius)
		return false;
	else if (DistRightTop > Src.Radius)
		return false;
	else if (DistLeftBottom > Src.Radius)
		return false;
	else if (DistRightBottom > Src.Radius)
		return false;

	//��Ʈ����Ʈ..?

	return true;
		// ���� ������ �簢���� ��, �� ���� Ȥ�� ��, �Ʒ� ������ �����ϴ��� �Ǵ��Ѵ�.
		
}*/
