#include "Timer.h"

CTimer::CTimer() : //�̴ϼȶ�����
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
	//���ػ� Ÿ�̸Ӱ� 1�ʰ� �귶�� �� �� �޾ƿ���
	// m_Second�� 100�̶�� ���� �ð� 1�ʰ� �귶���� ���ػ󵵴� 100���� �ð��� �帧
	QueryPerformanceFrequency(&m_Second); 

	// ���� ���ػ� Ÿ�̸��� ��
	//1�ʴ� 100�� �帣�� 1/100�� �ؼ�  ������ ƽ�� 0.01���� �ð��� �귯�� �Ѵ�.
	QueryPerformanceCounter(&m_Time);
}

void CTimer::Update() //�����Ӹ��� �۵� ���ӸŴ������� Logic() �κп� ����
{
	LARGE_INTEGER Time;
	QueryPerformanceCounter(&Time);

	m_DeltaTime = (Time.QuadPart - m_Time.QuadPart) / (float)m_Second.QuadPart;
	//��ŸŸ��:    ���� ���ػ� Ÿ�̸� �� - ���������� ���ػ� Ÿ�̸� �� / �ʴ� ���ػ� Ÿ�̸� ��
	m_Time = Time;

	m_FPSTime += m_DeltaTime; //�����Ӵ� FPSTime�� 0.2�ʰ� �����ȴ� ����
	++m_Tick;

	if (m_Tick == 60) //60�������� �Ǿ����� ����� �� �ִ� ��������? 60/0.2 = 300
	{
		m_FPS = m_Tick / m_FPSTime; // 60/0.2 = 300
		m_FPSTime = 0.f; //�ʱ�ȭ����
		m_Tick = 0;//�ʱ�ȭ����
	}
}
