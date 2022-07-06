#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR		lpCmdLine,
	_In_ int		nCmdShow)

{
	_CrtDumpMemoryLeaks();

	if (!CGameManager::GetInst()->Init(hInstance)) //싱글톤 초기화 실패시
	{
		CGameManager::DestroyInst(); //없애주고 종료
		return 0;
	}

	int ReturnValue = CGameManager::GetInst()->Run(); 

	//종료 시 메모리 정리, 여기로 왔으면 run()루프문을 빠져 나왔다는 뜻
	CGameManager::DestroyInst();

	return ReturnValue;
}