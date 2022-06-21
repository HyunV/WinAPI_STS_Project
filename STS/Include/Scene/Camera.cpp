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
	if (m_Target) //Ÿ���� �����Ǿ��� ���
	{
		if (!m_Target->GetActive()) //Ÿ���� ��Ȱ��ȭ �� ��� (Ÿ���� �Ҹ����� ���)
			m_Target = nullptr; //Ÿ���� ������� ��ptr��
		//�̷������� �ϸ� ���� ���� ��ź ���󰡴°� ī�޶� ��ȯ�� ���谡 ������

		else
			//�׷��� ������ Ÿ���� ��ġ�� ������ ó���Ѵ�
			m_Pos = m_Target->GetPos() - m_TargetPivot * m_Resolution + m_TargetOffset;
			//�Ǻ� 0.5, * �ػ� 1280,720 = �»���� ī�޶� ��ġ
			// ȭ�鿡 ������� Ÿ���� ��ġ�ϰ� Ÿ���� �Ѿư� ������
	}

	// ī�޶� ���带 ����� ���ϵ��� ������ش�.
	if (m_Pos.x < 0.f) //x�����̸�
		m_Pos.x = 0.f; //0���� ����

	else if (m_Pos.x + m_Resolution.x > m_WorldResolution.x) //���� �ػ󵵺��� Ŀ����
		m_Pos.x = m_WorldResolution.x - m_Resolution.x;

	if (m_Pos.y < 0.f)
		m_Pos.y = 0.f;

	else if (m_Pos.y + m_Resolution.y > m_WorldResolution.y)
		m_Pos.y = m_WorldResolution.y - m_Resolution.y;

	CInput::GetInst()->ComputeWorldMousePos(m_Pos); //�� ���� ����صξ� 
//���콺 ������� ��ǥ ��ġ�� ���� �� �ִ�.
}
