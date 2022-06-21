#pragma once
/*
애니메이션 시퀀스를 하나 가지고 있으면서
움짤 재생빈도, 루프여부 등을 정의하는 객체
//여기서 run info, idle info, attack info 등이 나올텐데 그걸 애니메이션 클래스에서 컨테이너에 담아 관리한다.
*/
//애니시퀀스+애니인포 -> 애니메이션 클래스 
#include "../GameInfo.h"

//Notify: 평타 딜레이 : 활쏘는 스킬을 쓸 때 활 시위를 떼야 나가는것처럼
//내가 원하는 프레임에 함수를 등록하는 시스템 : Notify
struct AnimationNotify
{
	int		Frame; //몇 번째 프레임에 등록할지
	bool	Call;  //현재 모션이 동작될 때 함수가 콜 되는지 여부
	//★콜 변수를 만든 이유:
	/*
		4프레임으로 4개의 모션이 있다.
		| | | |
		2번째 프레임이 Notify가 2개 들어가 있다.
		4개 프레임이 1번 끝날 때 시간이 1초라면 n에서 n+1 로 가는 시간은 0.25초이다.
		이 0.25초로 인해 2번째 프레임 -> 3번째 프레임으로 가는데 Notify 함수가 각각 1번이 아닌
		무수히 많이 호출 될 수 있다. 이를 콜변수를 만들어 함수가 한번 실행되면 더이상 실행되지 않게 제어해준다.
	*/
	std::function<void()>	Function; //실행할 함수

	AnimationNotify() :
		Frame(0),
		Call(false)
	{
	}
};


class CAnimationInfo
{
	friend class CAnimation;
	friend class CGameObject;

private:
	CAnimationInfo();
	~CAnimationInfo();

private:
	CSharedPtr<class CAnimationSequence>	m_Sequence; //시퀀스 받아오기
	int				m_Frame;	// 현재 애니메이션이 동작되는 프레임.
	float			m_Time;		// 애니메이션 프레임을 증가시켜주기 위한 시간값.
								// 3프레임 한바퀴 돌리는데 1초가 걸리면 1프레임당 걸리는 시간은 0.33초, 이 0.33초가 지났는지 판단하는 값

	float			m_FrameTime;	// 한 프레임이 증가하기 위한 시간. (0.33초가 들어오는 변수)
	float			m_PlayTime;		// 모션 한번이 동작되기 위한 시간. (모션 한바퀴 도는 시간) 
									// 1초 지정해주면 1초에 움짤을 끝냄 (롤의 초당 공속 생각하면 편함)

	float			m_PlayScale;	// 재생속도 배율.
	bool			m_Loop;			// 반복해서 재생해야 하는지 여부.
	bool			m_Reverse;		// 역재생 여부.
	std::function<void()>		m_EndFunction;	// 애니메이션이 끝날때마다 호출될 함수 등록.
	
	std::vector<AnimationNotify*>	m_vecNotify; //프레임 이벤트를 여러개 등록할 수 있게 배열로

public:
	template <typename T>
	void SetEndFunction(T* Obj, void(T::* Func)())
	{
		m_EndFunction = std::bind(Func, Obj);
	}

	template <typename T>
	void AddNotify(int Frame, T* Obj, void(T::* Func)()) //몇번째 프레임, 어떤 오브젝트에서, 발생할 이벤트 함수)
	{
		AnimationNotify* Notify = new AnimationNotify;

		Notify->Frame = Frame;
		Notify->Function = std::bind(Func, Obj);

		m_vecNotify.push_back(Notify);
	}
};

