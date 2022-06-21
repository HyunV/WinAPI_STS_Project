//���ӿ� �ʿ��� ���� ��ҵ��� �����ϴ� Ŭ����(�̱�)
#pragma once

#include "GameInfo.h"
#include "Singletone.h"

/*
������ �帧�� �����ϴ� �ܰ�
1. ������� �Է�
2. �Է¹��� ���뿡 ���ؼ� ������ ������Ʈ
�ΰ����ɵ��� ������ ������Ʈ
3. ������Ʈ�� �����͸� ���� �浹�� ����.
4. ����� �Ǿ�� �ϴ� ��ü���� �Ǵ�.
5. ȭ�鿡 ����� �Ǿ�� �ϴ� ��ü���� ���.
*/

class CGameManager
{

private:
	HINSTANCE	m_hInst;	// �ν��Ͻ� �ڵ鷯
	HWND		m_hWnd;		// â �ڵ鷯
	HDC			m_hDC;		// �׸��� �ڵ鷯 (��ȭ����� ����)
	
	//�����
	/* ��� -> �ʱ�ȭ -> ��� �������� ȭ���� �������̳� �ܻ��� �߻��ϹǷ�
	������ temp ȭ���� �����Ͽ� �ű⼭ �׸� �� �������� ȭ�鿡 ����ϴ� ���*/
	HDC			m_hBackDC;
	HBITMAP		m_hBackBmp;
	HBITMAP		m_hBackPrevBmp;

	//�ð� ���� ����
	class CTimer* m_Timer; //Ÿ�̸� ���漱�� 
	// ����� �� �� ���̱� ������ ��� �������� ���̰��� ���� ���
	
	float		m_FrameLimitTime; 
	
	float		m_DeltaTime; // ���� �����Ӱ� ������������ �ð� ��
	
	Resolution m_RS; //���� ���� ����� �ִ� �ػ�

	float m_TimeScale; //�ð� ���� �Լ�

	HBRUSH m_Brush[(int)EBrush_Type::Max];
	HPEN   m_Pen[(int)EBrush_Type::Max];

	bool	m_EditMode;

	static bool m_Loop; //���� ���� ����

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
		return m_RS; //���̿� �ʺ� ��ȯ
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
	//��ŸŸ��: ��ǻ�Ͱ� ���������� �Է����̸� Ŀ���ϱ� ���� ���� ����
	//�Է� -> ���� -> �浹 -> ���
	void Logic();
	void Input(float DeltaTime);
	bool Update(float DeltaTime); //�� ��ü ���η� �Ǵ��ϱ� ���� bool�� �ٲ���
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

