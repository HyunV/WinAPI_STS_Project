#pragma once

#include "GameInfo.h"

class CTimer
{
public:
	CTimer();
	~CTimer();

private:
	LARGE_INTEGER	m_Second; //union ����ü
	//�Լ� ���� �κ� ������ LongLong ������ quadpart�� ��� �ɰ����� ������
	//�ð��� �������ϰ� �ֱ� ���� LARGE_INTEGER�� �����
	LARGE_INTEGER	m_Time;
	float			m_DeltaTime;//�����Ӱ� ������ ������ �ð�(��ŸŸ��) �� ���ϱ� ���� ���ػ� Ÿ�̸Ӹ� �޾ƿ´�.
	
	//FPS ���� ����
	float			m_FPS;
	float			m_FPSTime;
	int				m_Tick;

public:
	//��ŸŸ�� �޾ƿ���
	float GetDeltaTime() const //�޾ƿ� �� ���� ����!
	{
		return m_DeltaTime;
	}
	
	//������ �޾ƿ���
	float GetFPS() const
	{
		return m_FPS;
	}

public:
	void Init();
	void Update();
};

