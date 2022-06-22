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
	//충돌 관계 설정 테이블 

	CreateProfile("Default", ECollision_Channel::Default, true); //안적어놨지만 디폴트인자로 충돌 처리
	CreateProfile("Player", ECollision_Channel::Player, true, ECollision_Interaction::Ignore);
	CreateProfile("Monster", ECollision_Channel::Monster, true, ECollision_Interaction::Ignore);
	CreateProfile("PlayerAttack", ECollision_Channel::PlayerAttack, true, ECollision_Interaction::Ignore);
	CreateProfile("MonsterAttack", ECollision_Channel::MonsterAttack, true, ECollision_Interaction::Ignore);
	CreateProfile("Mouse", ECollision_Channel::Mouse, true, ECollision_Interaction::Collision);

	CreateProfile("Card", ECollision_Channel::Card, true, ECollision_Interaction::Ignore);

	//플레이어, 몬스터, 공격 등 충돌처리 모두 무시로 잡아놓고

	//※ 상호작용 세팅
	SetCollisionInteraction("Player", ECollision_Channel::Default, ECollision_Interaction::Collision);
	//플레이어 : 디폴트 채널인 오브젝트(충돌) 관계를 충돌로 처리 

	SetCollisionInteraction("Player", ECollision_Channel::MonsterAttack, ECollision_Interaction::Collision);
	//플레이어가 몬스터 공격에 맞을 수 있게 된다.

	SetCollisionInteraction("Player", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	//플레이어가 몬스터에 몸빵
	SetCollisionInteraction("Player", ECollision_Channel::Mouse, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Mouse, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Card, ECollision_Interaction::Collision);

	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Default, ECollision_Interaction::Collision);
	//공격 : 디폴트와는 충돌처리 -> 벽에 부딫히면 사라질 수 있게
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Monster, ECollision_Interaction::Collision);

	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Player, ECollision_Interaction::Collision);

	SetCollisionInteraction("Card", ECollision_Channel::Mouse, ECollision_Interaction::Collision);
	SetCollisionInteraction("Card", ECollision_Channel::Monster, ECollision_Interaction::Collision);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& Name, ECollision_Channel Channel, bool Enable, ECollision_Interaction BaseIteraction)
{
	CollisionProfile* Profile = FindProfile(Name); //불러오기

	if (Profile) //이미 존재 시
		return false;

	Profile = new CollisionProfile; //프로파일 구조체 생성

	//입력한 정보 등록해줌
	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;
	Profile->vecCollisionInteraction.resize((size_t)ECollision_Channel::Max); //채널 5개이니 5개만큼 리사이즈 해줌

	for (int i = 0; i < (int)ECollision_Channel::Max; ++i)
	{
		Profile->vecCollisionInteraction[i] = BaseIteraction;  //각각 채널들 충돌, 무시 결정 
		//다른 프로파일과 비교시 전부 충돌 or 전부 무시 이렇게 세팅
	}

	m_mapProfile.insert(std::make_pair(Name, Profile)); //자료구조에 등록해둔다.

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& Name, ECollision_Channel Channel, ECollision_Interaction Iteraction)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (!Profile) //find 실패시
		return false;

	Profile->vecCollisionInteraction[(int)Channel] = Iteraction;
	//이 채널 인덱스에 들어온 상호작용을 인자로 들어온 Iteraction(충돌, 무시)으로 해준다

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
	//여기부분 자주 그림그려보면서 생각해보기
	//충돌이 안되는 예외
	if (Src.LT.x > Dest.RB.x)
		return false;

	else if (Src.LT.y > Dest.RB.y)
		return false;

	else if (Src.RB.x < Dest.LT.x)
		return false;

	else if (Src.RB.y < Dest.LT.y)
		return false;

	float Left = Src.LT.x > Dest.LT.x ? Src.LT.x : Dest.LT.x; //큰 값을 리턴
	float Top = Src.LT.y > Dest.LT.y ? Src.LT.y : Dest.LT.y; //큰 값을 리턴
	float Right = Src.RB.x < Dest.RB.x ? Src.RB.x : Dest.RB.x; // 작은 값을 리턴
	float Bottom = Src.RB.y < Dest.RB.y ? Src.RB.y : Dest.RB.y;// 작은 값을 리턴

	//LT, RB을 더하고 2로 나눠주면 교집합 사각형 가운데 부분이 나올 것
	HitPoint.x = (Left + Right) / 2.f; //교집합부분
	HitPoint.y = (Top + Bottom) / 2.f;

	return true;
}
//이것도 봐두기
bool CCollisionManager::CollisionCircleToCircle(Vector2& HitPoint, const CircleInfo& Src, const CircleInfo& Dest)
{
	// 센터 사이의 거리를 구한다.
	float Dist = Src.Center.Distance(Dest.Center);

	bool result = Dist <= Src.Radius + Dest.Radius;

	HitPoint = (Src.Center + Dest.Center) / 2.f;

	return result;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& HitPoint, const BoxInfo& Src, const CircleInfo& Dest)
{
	// 원의 중점이 사각형의 좌, 우 영역 혹은 위, 아래 영역에 존재하는지 판단한다.
	if ((Src.LT.x <= Dest.Center.x && Dest.Center.x <= Src.RB.x) ||
		(Src.LT.y <= Dest.Center.y && Dest.Center.y <= Src.RB.y))
	{
		// 사각형을 원의 반지름만큼 확장한다.
		BoxInfo	RC = Src;
		RC.LT.x -= Dest.Radius;
		RC.LT.y -= Dest.Radius;
		RC.RB.x += Dest.Radius;
		RC.RB.y += Dest.Radius;

		// 확장된 사각형 안에 원의 중점이 들어온다면 충돌된 것이다.
		if (RC.LT.x > Dest.Center.x)
			return false;

		else if (RC.LT.y > Dest.Center.y)
			return false;

		else if (RC.RB.x < Dest.Center.x)
			return false;

		else if (RC.RB.y < Dest.Center.y)
			return false;

		// 히트포인트.
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

	// 4개의 점중 하나라도 원 안에 들어온다면 충돌한 것이다.
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
	//사각형 안에 점이 있다면 true
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
	//반지름과 원에 중점 과 점의 distance를 구해보고
	//그 길이를 비교해서 점 거리가 반지름보다 작거나 같으면 충돌
	float Dist = Dest.Center.Distance(Src);

	if (Dist <= Dest.Radius)
	{
		HitPoint = Src;

		return true;
	}

	return false;
}

/*
//숙제로 짠 코드 
bool CCollisionManager::CollisionCircleToBox(Vector2& HitPoint, const CircleInfo& Src, const BoxInfo& Dest)
{
	//SRC : Circle
	//Dest : Box

	//1. 원의 반지름 만큼 박스의 크기를 늘린다.
	float Left = Dest.LT.x - Src.Radius;
	float Top = Dest.LT.y - Src.Radius;
	float Right = Dest.RB.x + Src.Radius;
	float Bottom = Dest.RB.y + Src.Radius;

	//충돌 처리 1. 확장한 사각형에 원에 중심이 들어가지면 
	
	//이건 반대로 처리해줌
	if (Src.Center.x < Left)
		return false;
	else if (Src.Center.y < Top)
		return false;
	else if (Src.Center.x > Right)
		return false;
	else if (Src.Center.y > Bottom)
		return false;

	//예외 처리 2. 사각형의 꼭지점이 원 안에 오면 충돌
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

	//히트포인트..?

	return true;
		// 원의 중점이 사각형의 좌, 우 영역 혹은 위, 아래 영역에 존재하는지 판단한다.
		
}*/
