#include "GameManager.h"
#include "resource.h"
#include "Timer.h"
#include "GameObject/Player.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Collision/CollisionManager.h"

DEFINITION_SINGLE(CGameManager) //게임매니저 포인터 타입의 m_Inst를 nullptr로 설정
bool CGameManager::m_Loop = true;

CGameManager::CGameManager()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
CGameManager::~CGameManager()
{
	//delete m_Player;
	CSceneManager::DestroyInst();

	CPathManager::DestroyInst();

	CCollisionManager::DestroyInst();

	CInput::DestroyInst();

	CResourceManager::DestroyInst();

	SAFE_DELETE(m_Timer);

	SelectObject(m_hBackDC, m_hBackPrevBmp);
	DeleteObject(m_hBackBmp);
	DeleteDC(m_hBackDC);

	for (int i = 0; i < (int)EBrush_Type::Max; ++i)
	{
		DeleteObject(m_Brush[i]);
	}

	for (int i = 0; i < (int)EBrush_Type::Max; ++i)
	{
		DeleteObject(m_Pen[i]);
	}

	ReleaseDC(m_hWnd, m_hDC); //DC 제거
}

float CGameManager::GetFPS() const
{
	return m_Timer->GetFPS();
}

void CGameManager::Exit()
{
	DestroyWindow(m_hWnd);
}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst; //윈도우가 구분할 수 있는 창의 고유한 식별번호인 인스턴스를 받아옴

	m_RS.Width = 1280;
	m_RS.Height = 720;

	//SetTexture("BackGround", TEXT("BackGround.bmp"));

	Register(); //wcex 구조체 초기화

	Create(); // 윈도우 창 생성 및 출력


	// 경로 관리자 초기화
	if (!CPathManager::GetInst()->Init())
		return false;

	// 리소스 관리자 초기화
	if (!CResourceManager::GetInst()->Init())
		return false;

	//충돌 관리자
	if (!CCollisionManager::GetInst()->Init())
		return false;
	
	//인풋 관리자 
	if (!CInput::GetInst()->Init(m_hWnd))
		return false;	

	//씬 관리자
	if (!CSceneManager::GetInst()->Init())
		return false;

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ타이머
	m_Timer = new CTimer;
	m_Timer->Init();

	//DC 그리기
	m_hDC = GetDC(m_hWnd);
	m_FrameLimitTime = 1 / 60.f;

	m_hBackDC = CreateCompatibleDC(m_hDC);
	m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_RS.Width, m_RS.Height);
	m_hBackPrevBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);

	m_TimeScale = 1.f;

	m_Brush[(int)EBrush_Type::Red] = CreateSolidBrush(RGB(255, 0, 0));
	m_Brush[(int)EBrush_Type::Green] = CreateSolidBrush(RGB(0, 255, 0));
	m_Brush[(int)EBrush_Type::Black] = CreateSolidBrush(RGB(0, 0, 0));
	m_Brush[(int)EBrush_Type::Blue] = CreateSolidBrush(RGB(0, 0, 255));
	m_Brush[(int)EBrush_Type::Yellow] = CreateSolidBrush(RGB(255, 255, 0));

	m_Pen[(int)EBrush_Type::Red] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	m_Pen[(int)EBrush_Type::Green] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	m_Pen[(int)EBrush_Type::Black] = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	m_Pen[(int)EBrush_Type::Blue] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	m_Pen[(int)EBrush_Type::Yellow] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));

	//플레이어 생성 초기화

 /*  m_Player = new CPlayer;

   m_Player->Init();

  m_Player->SetPos(100.f, 100.f);
   m_Player->SetSize(100.f, 100.f);
   m_Player->SetPivot(0.5f, 0.5f);*/

	return true;
}

int CGameManager::Run()
{
	MSG msg; //운영체제의 메시지를 받아오기 위한 구조체
	/*
	GetMessage : 메시지 큐에서 메시지 꺼내오는 함수, ※ 큐가 비어있어도 빠져나올 수 없음(블로킹모드) 
	할 일 없으면 데드타임으로 이어짐

	PeekMessage : 메시지 큐에서 메시지 꺼내오는 함수, ※ 큐가 비어있으면 false 보내고 빠져나옴
	*/
	while (m_Loop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg); //받아온 메시지로 입력키 판단(WM_KEYDOWN, WM_CHAR..) 
			//※ 문자 키는 WM_KEYDOWN -> WM_CHAR 로 이벤트가 이어짐
			
			DispatchMessage(&msg); //큐에 꺼내온 메시지를 WndProc로 보내줌
		}
		else //큐가 없을 때(놀고 있을 때) 
		{
			Logic(); //게임 작동
		}
	}
	return (int)msg.wParam;
}

void CGameManager::Logic() //인게임 구현부분
{
	//타이머 셋팅
	m_Timer->Update();
	float DeltaTime = m_Timer->GetDeltaTime() * m_TimeScale;

	m_DeltaTime = DeltaTime;

	//모든 게임은 1.입력->2.갱신->3.충돌->4.출력 으로 이어짐. 
	Input(DeltaTime); // 이벤트를 입력받음
	
	if (Update(DeltaTime)) //씬이 교체되면 처음부터 다시 동작
		return;
	//Update(DeltaTime); //화면에 갱신

	if (PostUpdate(DeltaTime))
		return;

	Collision(DeltaTime); //스킬이 적에 닿았는지 같은 여부
	Render(DeltaTime); //바뀐 이벤트들 처리
}

void CGameManager::Input(float DeltaTime)
{
	CInput::GetInst()->Update(DeltaTime);
}

bool CGameManager::Update(float DeltaTime)
{
	CResourceManager::GetInst()->Update();

	return CSceneManager::GetInst()->Update(DeltaTime);
}

bool CGameManager::PostUpdate(float DeltaTime)
{
	CInput::GetInst()->PostUpdate(DeltaTime);
	return CSceneManager::GetInst()->PostUpdate(DeltaTime);
}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime) //화면 출력 영역
{
	//Rectangle(m_hBackDC, -1, -1, m_RS.Width + 1, m_RS.Height + 1);
	//CGameManager::Render(hDC, DeltaTime);

	CSceneManager::GetInst()->Render(m_hBackDC, DeltaTime);

	CInput::GetInst()->Render(m_hBackDC, DeltaTime);

	BitBlt(m_hDC, 0, 0, m_RS.Width, m_RS.Height, m_hBackDC, 0, 0, SRCCOPY);
	//플레이어
	//m_Player->Render(m_hDC, DeltaTime);

	////델타타임 출력
	//char FPSText[64] = {};
	////유니코드는 실수문자열 처리가 잘 안되서 멀티바이트로 처리
	//sprintf_s(FPSText, "DeltatTime : %.5f", DeltaTime); //FPSText를 소수점 5자리로 표현방식으로 바꿔서 만들어줌
	//TextOutA(m_hDC, 1000, 50, FPSText, strlen(FPSText));


	////그냥 타이머 출력
	//static float CurrentTime = 0.f;
	//static int Min = 0;
	//CurrentTime += DeltaTime;
	//if (CurrentTime >= 60.f) {
	//	CurrentTime = 0;
	//	Min++;
	//}
	//char TimeText[64] = {};
	//sprintf_s(TimeText, "Time : %d:%.5f", Min,CurrentTime);
	//TextOutA(m_hDC, 1000, 100, TimeText, strlen(TimeText));

	////델타타임을 이용한 물체 이동
	//static float Top = 100.f;
	//static float Bottom = 200.f;
	//Top += 1.f * DeltaTime;
	//Bottom += 1.f * DeltaTime;
	//Rectangle(m_hDC, 800, Top, 900, Bottom);
}

void CGameManager::Register()
{
	WNDCLASSEXW wcex; //레지스터에 등록할 윈도우 클래스 구조체들
	//이 밑에는 윈도우가 어떤 형태로 쓸건지 설정해줌.

	wcex.cbSize = sizeof(WNDCLASSEX); //왜 쓰는지 알 수 없지만 일단 써줘야댐
	wcex.style = CS_HREDRAW | CS_VREDRAW; //H: 가로 V: 세로 //클라이언트 크기 바뀔 시 다시그리기
	wcex.lpfnWndProc = WndProc; //함수포인터로 윈도우 프로시저 받음
	//메시지 큐에 메시지를 꺼내서 호출할 함수를 윈도우 프로시저에다가 지정해줌
	//WndProc 함수를 보면 받는 인자 기준이 있음, 마치 정렬 기준 정하듯이 사용하기 위해 함수포인터로 받은 것.

	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hInstance = m_hInst; //윈도우 인스턴스 지정해줌 우리는 게임매니저 헤더서 m_hInst를 싱글톤으로 쓰려고 이걸로 지정.
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON3)); //아이콘 세팅
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //마우스 커서 모양(기본)
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //클라이언트 화면 기본 색상(화이트)
	wcex.lpszMenuName = nullptr; //메뉴 사용 여부, 쓸거면 MAKEINTRESOURCEW(IDC_MY220428)
	wcex.lpszClassName = TEXT("GameFramework"); //클래스 이름 szWindowClass //이름 이상하게 하니까 안나오네?
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON3)); //미니 아이콘 세팅

	RegisterClassExW(&wcex); //이 함수를 통해 세팅한 것들을 등록한다.
}

bool CGameManager::Create()
{
	m_hWnd = CreateWindowW(TEXT("GameFramework"), TEXT("Slay the Spire"), WS_OVERLAPPEDWINDOW, 100, 0, 0, 0, nullptr, nullptr, m_hInst, nullptr);
	//		= CreateWindoW(1.윈도우 클래스에 등록한 이름, 2.타이틀바 이름, 3.창 어떻게 생성될지, 4,5. 창 생성 위치, 6,7: 가로, 세로 , 8.부모윈도우 핸들 지정, 9. 메뉴핸들 지정, 10.윈도우 인스턴스(hInstance), 11. 
	//10번인자는 정상적으로 생성되면 HWND를 반환해줌 실패시 0 반환
	if (!m_hWnd)
	{
		return false;
	}

	//해상도설정: 깡으로 FHD로 하면 메뉴같은거 추가해줄때 FHD 기준 벗어날 수 있기 때문에 고정세팅 해줌 

	RECT rc = { 0, 0, m_RS.Width, m_RS.Height }; //사각형 구조체 LEFT, TOP, RIGHT, BOTTOM

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); //현재 실제 윈도우 크기 불러움

	MoveWindow(m_hWnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, TRUE);

	ShowWindow(m_hWnd, SW_SHOW); //화면 출력
	UpdateWindow(m_hWnd); //화면 갱신

	return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//키보드 입력 혹은 이벤트 발생 시 처리하는 프로시저
{
	switch (message)
	{
	case WM_DESTROY:
		m_Loop = false;
		PostQuitMessage(0);
		break;
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}