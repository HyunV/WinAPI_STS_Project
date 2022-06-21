#include "Timer.h"

CTimer::CTimer() : //이니셜라이저
	m_Second{},
	m_Time{},
	m_DeltaTime(0.f),
	m_FPS(0.f),
	m_FPSTime(0.f),
	m_Tick(0)
{
}

CTimer::~CTimer()
{
}

void CTimer::Init()
{
	//고해상도 타이머가 1초가 흘렀을 때 값 받아오기
	// m_Second가 100이라면 실제 시간 1초가 흘렀을때 고해상도는 100초의 시간이 흐름
	QueryPerformanceFrequency(&m_Second); 

	// 현재 고해상도 타이머의 값
	//1초당 100이 흐르면 1/100을 해서  프레임 틱당 0.01초의 시간이 흘러야 한다.
	QueryPerformanceCounter(&m_Time);
}

void CTimer::Update() //프레임마다 작동 게임매니저에서 Logic() 부분에 있음
{
	LARGE_INTEGER Time;
	QueryPerformanceCounter(&Time);

	m_DeltaTime = (Time.QuadPart - m_Time.QuadPart) / (float)m_Second.QuadPart;
	//델타타임:    현재 고해상도 타이머 값 - 이전프레임 고해상도 타이머 값 / 초당 고해상도 타이머 값
	m_Time = Time;

	m_FPSTime += m_DeltaTime; //프레임당 FPSTime이 0.2초가 누적된다 가정
	++m_Tick;

	if (m_Tick == 60) //60프레임이 되었을때 기대할 수 있는 프레임은? 60/0.2 = 300
	{
		m_FPS = m_Tick / m_FPSTime; // 60/0.2 = 300
		m_FPSTime = 0.f; //초기화해줌
		m_Tick = 0;//초기화해줌
	}
}
