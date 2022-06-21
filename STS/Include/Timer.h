#pragma once

#include "GameInfo.h"

class CTimer
{
public:
	CTimer();
	~CTimer();

private:
	LARGE_INTEGER	m_Second; //union 공용체
	//함수 정의 부분 가보면 LongLong 변수에 quadpart로 얘네 쪼가리가 모여있음
	//시간을 디테일하게 넣기 위해 LARGE_INTEGER로 사용함
	LARGE_INTEGER	m_Time;
	float			m_DeltaTime;//프레임과 프레임 사이의 시간(델타타임) 을 구하기 위해 고해상도 타이머를 받아온다.
	
	//FPS 관련 변수
	float			m_FPS;
	float			m_FPSTime;
	int				m_Tick;

public:
	//델타타임 받아오기
	float GetDeltaTime() const //받아온 값 수정 금지!
	{
		return m_DeltaTime;
	}
	
	//프레임 받아오기
	float GetFPS() const
	{
		return m_FPS;
	}

public:
	void Init();
	void Update();
};

