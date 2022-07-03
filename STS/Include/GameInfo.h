//유틸리티 모은정도로 보면 될 듯
#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map> 
#include <queue>
/*
해쉬테이블 탐색 자료구조 O(1)의 속도
	* 그냥 map은 이진탐색트리로 O(log(N)), 중복 데이터를 허용하지않고 
	* map보다 데이터가 많을 때 유용
	* 이터레이터로 접근해야됨.
*/
#include <crtdbg.h> //메모리누수 찾아주는 라이브러리, 게임매니저 생성자에 만들어져있음

#include<typeinfo> //서로 다른 두 타입들을 비교할 수 있고 타입을 문자열로 바꿔준다?(id형식으로 사용)
#include<string>
#include<functional> //전역함수, 멤버함수 상관없이 함수포인터 등록하고 콜해주는 기능을 제공
#include <algorithm> //sort 기능 제공
#include <stack>

using namespace std;

#include "Vector2.h"
#include "SharedPtr.h"
#include "Flag.h"
#include "fmod.hpp" //사운드 관련 외부 라이브러리'

#define GRAVITY 9.8f

//리소스 관련 헤더
#pragma comment(lib, "msimg32.lib") //이미지 넣기 위한 라이브러리
#pragma comment(lib, "../Bin/fmod64_vc.lib") //사운드 라이브러리

//경로지정자 관련 변수들
#define ROOT_PATH "RootPath" //절대경로
#define TEXTURE_PATH "TexturePath" //텍스처 이미지 경로
#define SOUND_PATH	"SoundPath"
#define FONT_PATH	"FontPath"
// GameFrameWokk/Bin/Texture

//포인터 삭제 매크로(일반 삭제, 배열 삭제, RC 감소)
#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr;}
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr; }

float RadianToDegree(float Radian); //라디안 -> 도
float DegreeToRadian(float Degree); // 도 -> 라디안

#define DELTA_TIME CGameManager::GetInst()->GetDeltaTime() //델타타임값 가져오는 매크로

struct Resolution //해상도
{
	int Width;
	int Height;
};

struct AnimationFrameData
{
	Vector2 Start; //애니메이션의 시작
	Vector2 End; //애니메이션의 끝
};

struct CollisionProfile //충돌 정보 모음
{
	std::string							Name; //이름
	ECollision_Channel					Channel; //
	bool								Enable;
	std::vector<ECollision_Interaction> vecCollisionInteraction; //상호작용
	/*
	Default,
		Player,
		Monster,
		PlayerAttack,
		MonsterAttack,
		Max
	이것들을 선택정렬해서 충돌처리하냐 무시하냐 세팅한다.
	*/
	CollisionProfile() :
		Enable(true), //초기값 true로 해준 모습
		Name("Noname"),
		Channel(ECollision_Channel::Default)
	{

	}
};

struct BoxInfo
{
	Vector2 LT;
	Vector2 RB; //Size
};

struct CircleInfo
{
	Vector2 Center;
	float Radius;
};
