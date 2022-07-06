#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR		lpCmdLine,
	_In_ int		nCmdShow)

{
	_CrtDumpMemoryLeaks();

	if (!CGameManager::GetInst()->Init(hInstance)) //�̱��� �ʱ�ȭ ���н�
	{
		CGameManager::DestroyInst(); //�����ְ� ����
		return 0;
	}

	int ReturnValue = CGameManager::GetInst()->Run(); 

	//���� �� �޸� ����, ����� ������ run()�������� ���� ���Դٴ� ��
	CGameManager::DestroyInst();

	return ReturnValue;
}