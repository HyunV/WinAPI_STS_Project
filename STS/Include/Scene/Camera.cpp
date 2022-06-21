#include "Camera.h"
#include "../Input.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

void CCamera::Update(float DeltaTime)
{
	if (m_Target) //타겟이 지정되었을 경우
	{
		if (!m_Target->GetActive()) //타겟이 비활성화 된 경우 (타겟이 소멸했을 경우)
			m_Target = nullptr; //타겟이 사라지면 널ptr로
		//이렇식으로 하면 웜즈 같이 포탄 날라가는걸 카메라 전환시 설계가 편해짐

		else
			//그렇지 않으면 타겟의 위치를 가지고 처리한다
			m_Pos = m_Target->GetPos() - m_TargetPivot * m_Resolution + m_TargetOffset;
			//피봇 0.5, * 해상도 1280,720 = 좌상단의 카메라 위치
			// 화면에 어느정도 타겟을 배치하고 타겟을 쫓아갈 것인지
	}

	// 카메라가 월드를 벗어나지 못하도록 만들어준다.
	if (m_Pos.x < 0.f) //x음수이면
		m_Pos.x = 0.f; //0으로 고정

	else if (m_Pos.x + m_Resolution.x > m_WorldResolution.x) //월드 해상도보다 커지면
		m_Pos.x = m_WorldResolution.x - m_Resolution.x;

	if (m_Pos.y < 0.f)
		m_Pos.y = 0.f;

	else if (m_Pos.y + m_Resolution.y > m_WorldResolution.y)
		m_Pos.y = m_WorldResolution.y - m_Resolution.y;

	CInput::GetInst()->ComputeWorldMousePos(m_Pos); //이 값을 계산해두어 
//마우스 월드상의 좌표 위치를 구할 수 있다.
}
