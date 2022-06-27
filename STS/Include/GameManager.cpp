#include "GameManager.h"
#include "resource.h"
#include "Timer.h"
#include "GameObject/Player.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Collision/CollisionManager.h"

DEFINITION_SINGLE(CGameManager) //���ӸŴ��� ������ Ÿ���� m_Inst�� nullptr�� ����
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

	ReleaseDC(m_hWnd, m_hDC); //DC ����
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
	m_hInst = hInst; //�����찡 ������ �� �ִ� â�� ������ �ĺ���ȣ�� �ν��Ͻ��� �޾ƿ�

	m_RS.Width = 1280;
	m_RS.Height = 720;

	//SetTexture("BackGround", TEXT("BackGround.bmp"));

	Register(); //wcex ����ü �ʱ�ȭ

	Create(); // ������ â ���� �� ���


	// ��� ������ �ʱ�ȭ
	if (!CPathManager::GetInst()->Init())
		return false;

	// ���ҽ� ������ �ʱ�ȭ
	if (!CResourceManager::GetInst()->Init())
		return false;

	//�浹 ������
	if (!CCollisionManager::GetInst()->Init())
		return false;
	
	//��ǲ ������ 
	if (!CInput::GetInst()->Init(m_hWnd))
		return false;	

	//�� ������
	if (!CSceneManager::GetInst()->Init())
		return false;

	//�ѤѤѤѤѤѤѤѤѤѤ�Ÿ�̸�
	m_Timer = new CTimer;
	m_Timer->Init();

	//DC �׸���
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

	//�÷��̾� ���� �ʱ�ȭ

 /*  m_Player = new CPlayer;

   m_Player->Init();

  m_Player->SetPos(100.f, 100.f);
   m_Player->SetSize(100.f, 100.f);
   m_Player->SetPivot(0.5f, 0.5f);*/

	return true;
}

int CGameManager::Run()
{
	MSG msg; //�ü���� �޽����� �޾ƿ��� ���� ����ü
	/*
	GetMessage : �޽��� ť���� �޽��� �������� �Լ�, �� ť�� ����־ �������� �� ����(���ŷ���) 
	�� �� ������ ����Ÿ������ �̾���

	PeekMessage : �޽��� ť���� �޽��� �������� �Լ�, �� ť�� ��������� false ������ ��������
	*/
	while (m_Loop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg); //�޾ƿ� �޽����� �Է�Ű �Ǵ�(WM_KEYDOWN, WM_CHAR..) 
			//�� ���� Ű�� WM_KEYDOWN -> WM_CHAR �� �̺�Ʈ�� �̾���
			
			DispatchMessage(&msg); //ť�� ������ �޽����� WndProc�� ������
		}
		else //ť�� ���� ��(��� ���� ��) 
		{
			Logic(); //���� �۵�
		}
	}
	return (int)msg.wParam;
}

void CGameManager::Logic() //�ΰ��� �����κ�
{
	//Ÿ�̸� ����
	m_Timer->Update();
	float DeltaTime = m_Timer->GetDeltaTime() * m_TimeScale;

	m_DeltaTime = DeltaTime;

	//��� ������ 1.�Է�->2.����->3.�浹->4.��� ���� �̾���. 
	Input(DeltaTime); // �̺�Ʈ�� �Է¹���
	
	if (Update(DeltaTime)) //���� ��ü�Ǹ� ó������ �ٽ� ����
		return;
	//Update(DeltaTime); //ȭ�鿡 ����

	if (PostUpdate(DeltaTime))
		return;

	Collision(DeltaTime); //��ų�� ���� ��Ҵ��� ���� ����
	Render(DeltaTime); //�ٲ� �̺�Ʈ�� ó��
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

void CGameManager::Render(float DeltaTime) //ȭ�� ��� ����
{
	//Rectangle(m_hBackDC, -1, -1, m_RS.Width + 1, m_RS.Height + 1);
	//CGameManager::Render(hDC, DeltaTime);

	CSceneManager::GetInst()->Render(m_hBackDC, DeltaTime);

	CInput::GetInst()->Render(m_hBackDC, DeltaTime);

	BitBlt(m_hDC, 0, 0, m_RS.Width, m_RS.Height, m_hBackDC, 0, 0, SRCCOPY);
	//�÷��̾�
	//m_Player->Render(m_hDC, DeltaTime);

	////��ŸŸ�� ���
	//char FPSText[64] = {};
	////�����ڵ�� �Ǽ����ڿ� ó���� �� �ȵǼ� ��Ƽ����Ʈ�� ó��
	//sprintf_s(FPSText, "DeltatTime : %.5f", DeltaTime); //FPSText�� �Ҽ��� 5�ڸ��� ǥ��������� �ٲ㼭 �������
	//TextOutA(m_hDC, 1000, 50, FPSText, strlen(FPSText));


	////�׳� Ÿ�̸� ���
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

	////��ŸŸ���� �̿��� ��ü �̵�
	//static float Top = 100.f;
	//static float Bottom = 200.f;
	//Top += 1.f * DeltaTime;
	//Bottom += 1.f * DeltaTime;
	//Rectangle(m_hDC, 800, Top, 900, Bottom);
}

void CGameManager::Register()
{
	WNDCLASSEXW wcex; //�������Ϳ� ����� ������ Ŭ���� ����ü��
	//�� �ؿ��� �����찡 � ���·� ������ ��������.

	wcex.cbSize = sizeof(WNDCLASSEX); //�� ������ �� �� ������ �ϴ� ����ߴ�
	wcex.style = CS_HREDRAW | CS_VREDRAW; //H: ���� V: ���� //Ŭ���̾�Ʈ ũ�� �ٲ� �� �ٽñ׸���
	wcex.lpfnWndProc = WndProc; //�Լ������ͷ� ������ ���ν��� ����
	//�޽��� ť�� �޽����� ������ ȣ���� �Լ��� ������ ���ν������ٰ� ��������
	//WndProc �Լ��� ���� �޴� ���� ������ ����, ��ġ ���� ���� ���ϵ��� ����ϱ� ���� �Լ������ͷ� ���� ��.

	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hInstance = m_hInst; //������ �ν��Ͻ� �������� �츮�� ���ӸŴ��� ����� m_hInst�� �̱������� ������ �̰ɷ� ����.
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON3)); //������ ����
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //���콺 Ŀ�� ���(�⺻)
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //Ŭ���̾�Ʈ ȭ�� �⺻ ����(ȭ��Ʈ)
	wcex.lpszMenuName = nullptr; //�޴� ��� ����, ���Ÿ� MAKEINTRESOURCEW(IDC_MY220428)
	wcex.lpszClassName = TEXT("GameFramework"); //Ŭ���� �̸� szWindowClass //�̸� �̻��ϰ� �ϴϱ� �ȳ�����?
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON3)); //�̴� ������ ����

	RegisterClassExW(&wcex); //�� �Լ��� ���� ������ �͵��� ����Ѵ�.
}

bool CGameManager::Create()
{
	m_hWnd = CreateWindowW(TEXT("GameFramework"), TEXT("Slay the Spire"), WS_OVERLAPPEDWINDOW, 100, 0, 0, 0, nullptr, nullptr, m_hInst, nullptr);
	//		= CreateWindoW(1.������ Ŭ������ ����� �̸�, 2.Ÿ��Ʋ�� �̸�, 3.â ��� ��������, 4,5. â ���� ��ġ, 6,7: ����, ���� , 8.�θ������� �ڵ� ����, 9. �޴��ڵ� ����, 10.������ �ν��Ͻ�(hInstance), 11. 
	//10�����ڴ� ���������� �����Ǹ� HWND�� ��ȯ���� ���н� 0 ��ȯ
	if (!m_hWnd)
	{
		return false;
	}

	//�ػ󵵼���: ������ FHD�� �ϸ� �޴������� �߰����ٶ� FHD ���� ��� �� �ֱ� ������ �������� ���� 

	RECT rc = { 0, 0, m_RS.Width, m_RS.Height }; //�簢�� ����ü LEFT, TOP, RIGHT, BOTTOM

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); //���� ���� ������ ũ�� �ҷ���

	MoveWindow(m_hWnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, TRUE);

	ShowWindow(m_hWnd, SW_SHOW); //ȭ�� ���
	UpdateWindow(m_hWnd); //ȭ�� ����

	return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//Ű���� �Է� Ȥ�� �̺�Ʈ �߻� �� ó���ϴ� ���ν���
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