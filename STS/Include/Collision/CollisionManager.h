#pragma once
//�浹 ����ü�� �����ϴ� �Ŵ���
// 
//�浹 ����ü ���� �� ���� ���� �Ǿ� �ϹǷ� ���� �Ѿ�� ��� ���ŵǾ�� �Ѵ�.
#include "../GameInfo.h"
#include "../Singletone.h"

class CCollisionManager
{
private:
	std::unordered_map<std::string, CollisionProfile*> m_mapProfile; //���������� map �ڷᱸ���� ����

public:
	bool Init();

	bool CreateProfile(const std::string& Name, ECollision_Channel Channel, bool Enable,
		ECollision_Interaction BaseIteraction = ECollision_Interaction::Collision);
	//�������� �̸�, � ä��?, Ȱ��ȭ ����, ����, �浹 ����(����Ʈ: �浹)

	//��ȣ�ۿ� ���� �Լ�
	bool SetCollisionInteraction(const std::string& Name, ECollision_Channel Channel,
		ECollision_Interaction Iteraction);
	
	CollisionProfile* FindProfile(const std::string& Name); //������ ã��

public:
	bool CollisionBoxToBox(Vector2& HitPoint, class CColliderBox* Src, class CColliderBox* Dest);
	bool CollisionCircleToCircle(Vector2& HitPoint, class CColliderCircle* Src, class CColliderCircle* Dest);
	//bool CollisionCircleToBox(Vector2& HitPoint, class CColliderCircle* Src, class CColliderBox* Dest);
	bool CollisionBoxToCircle(Vector2& HitPoint, class CColliderBox* Src, class CColliderCircle* Dest);
	bool CollisionPointToBox(Vector2& HitPoint, const Vector2& Src, class CColliderBox* Dest);
	bool CollisionPointToCircle(Vector2& HitPoint, const Vector2& Src, class CColliderCircle* Dest);

public:
	bool CollisionBoxToBox(Vector2& HitPoint, const BoxInfo& Src, const BoxInfo& Dest);
	bool CollisionCircleToCircle(Vector2& HitPoint, const CircleInfo& Src, const CircleInfo& Dest);
	//bool CollisionCircleToBox(Vector2& HitPoint, const CircleInfo& Src, const BoxInfo& Dest);
	bool CollisionBoxToCircle(Vector2& HitPoint, const BoxInfo& Src, const CircleInfo& Dest);
	bool CollisionPointToBox(Vector2& HitPoint, const Vector2& Src, const BoxInfo& Dest);
	bool CollisionPointToCircle(Vector2& HitPoint, const Vector2& Src, const CircleInfo& Dest);

	DECLARE_SINGLE(CCollisionManager)
};

