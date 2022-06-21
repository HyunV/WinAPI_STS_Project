#pragma once
//충돌 구조체를 관리하는 매니저
// 
//충돌 구조체 또한 씬 별로 관리 되야 하므로 씬이 넘어가면 모두 제거되어야 한다.
#include "../GameInfo.h"
#include "../Singletone.h"

class CCollisionManager
{
private:
	std::unordered_map<std::string, CollisionProfile*> m_mapProfile; //프로파일을 map 자료구조로 저장

public:
	bool Init();

	bool CreateProfile(const std::string& Name, ECollision_Channel Channel, bool Enable,
		ECollision_Interaction BaseIteraction = ECollision_Interaction::Collision);
	//프로파일 이름, 어떤 채널?, 활성화 여부, 무시, 충돌 여부(디폴트: 충돌)

	//상호작용 변경 함수
	bool SetCollisionInteraction(const std::string& Name, ECollision_Channel Channel,
		ECollision_Interaction Iteraction);
	
	CollisionProfile* FindProfile(const std::string& Name); //프로필 찾기

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

