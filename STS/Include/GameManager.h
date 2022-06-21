//게임에 필요한 각종 요소들을 관리하는 클래스(싱글)
#pragma once

#include "GameInfo.h"
#include "Singletone.h"

/*
게임의 흐름을 구성하는 단계
1. 사용자의 입력
2. 입력받은 내용에 대해서 데이터 업데이트
인공지능들의 데이터 업데이트
3. 업데이트된 데이터를 토대로 충돌을 수행.
4. 출력이 되어야 하는 물체들을 판단.
5. 화면에 출력이 되어야 하는 물체들을 출력.
*/

class CGameManager
{

private:
	HINSTANCE	m_hInst;	// 인스턴스 핸들러
	HWND		m_hWnd;		// 창 핸들러
	HDC			m_hDC;		// 그리기 핸들러 (도화지라고 생각)
	
	//백버퍼
	/* 출력 -> 초기화 -> 출력 과정에서 화면의 깜빡임이나 잔상이 발생하므로
	별도의 temp 화면을 구성하여 거기서 그린 후 보여지는 화면에 출력하는 방식*/
	HDC			m_hBackDC;
	HBITMAP		m_hBackBmp;
	HBITMAP		m_hBackPrevBmp;

	//시간 관련 변수
	class CTimer* m_Timer; //타이머 전방선언 
	// 헤더는 좀 더 무겁기 때문에 헤더 의존성을 줄이고자 쓰는 방식
	
	float		m_FrameLimitTime; 
	
	float		m_DeltaTime; // 현재 프레임과 이전프레임의 시간 차
	
	Resolution m_RS; //게임 인포 헤더에 있는 해상도

	float m_TimeScale; //시간 배율 함수

	HBRUSH m_Brush[(int)EBrush_Type::Max];
	HPEN   m_Pen[(int)EBrush_Type::Max];

	bool	m_EditMode;

	static bool m_Loop; //루프 여부 변수

public:
	bool GetEditMode()	const
	{
		return m_EditMode;
	}
	HBRUSH GetBrush(EBrush_Type Type) const
	{
		return m_Brush[(int)Type];
	}
	HPEN GetPen(EBrush_Type Type) const
	{
		return m_Pen[(int)Type];
	}

	Resolution GetResolution() const
	{
		return m_RS; //높이와 너비를 반환
	}
	float GetDeltaTime() const
	{
		return m_DeltaTime;
	}
	HDC GetWindowDC() const
	{
		return m_hDC;
	}
	HWND GetWindowHandle() const
	{
		return m_hWnd;
	}
	HINSTANCE GetWindowInstance() const
	{
		return m_hInst;
	}
	float GetTimeScale() const
	{
		return m_TimeScale;
	}
public:
	void SetTimeScale(float Scale)
	{
		m_TimeScale = Scale;
	}

	float GetFPS()	const;

	void Exit();

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	//델타타임: 컴퓨터간 프레임으로 입력차이를 커버하기 위해 쓰는 변수
	//입력 -> 갱신 -> 충돌 -> 출력
	void Logic();
	void Input(float DeltaTime);
	bool Update(float DeltaTime); //씬 교체 여부로 판단하기 위해 bool로 바꿔줌
	bool PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(float DeltaTime);

private:
	void Register();
	bool Create();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	DECLARE_SINGLE(CGameManager)
};

