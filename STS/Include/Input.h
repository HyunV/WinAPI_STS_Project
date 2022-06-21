#pragma once
//입력을 받았을때 (기본 입력, 꾹 눌렀을 때, 커맨드 입력할 때, 키보드 뗄 때, 마우스 클릭 등)
#include "GameInfo.h"
#include "Singletone.h"
//vk 커맨드 시리즈는 255개 이하 unsigned char로 충분
// 
// GetAsyncKeyState : 키의 상태를 체크할 수 있다.
// 0 : 안눌린상태.
// 0x8000 : 키 누른 상태.
// 0x1 : 키가 이전 프레임에 눌린 상태.

enum class Input_Type //어떤타입으로 눌렸는지 항목
{
	Down, //누르기 시작
	Push,//누르는 중
	Up, //뗄 때
	End 
};

struct KeyState
{
	unsigned char key;
	bool Down; //누르기 시작
	bool Push; //누르는 중
	bool Up; //뗄 때

	KeyState() : //이니셜라이저?
		key(0),
		Down(false),
		Push(false),
		Up(false)
	{
	}
};

//뭐하는 함수냐 이거
struct BindFunction
{
	void* Obj; //void 포인터 타입 Obj
	//모든 변수 타입의 데이터를 저장하기 위해 이렇게 선언
	std::function<void()> func; //function 헤더

	BindFunction() :
		Obj(nullptr)
	{
	}
};

//바인드 키 : 커맨드
struct BindKey //조합키 커맨드
{
	//바인드 키에 필요한 변수들
	std::string Name; //무슨 조합키인지 이름지어주는 용도 변수
	KeyState* key; //어떤 키를 사용하는지 (Down, Up, push)
	bool Ctrl;
	bool Alt;
	bool Shift;

	//키를 눌렀을 때 동작할 수 있는 함수들을 만들 예정
	
	//멤버함수 등록할때는 객체까지 반드시 등록해줘야함 vector<타입>이름
	std::vector<BindFunction*> vecFunction[(int)Input_Type::End]; //벡터 크기 3개 만들었다는 뜻? [0] : Down, [1] Push, [2] Up 
	//BindFunction 타입 벡터
	BindKey() :
		key(nullptr),
		Ctrl(false),
		Alt(false),
		Shift(false)
	{
	}
};

class CInput
{
private:
	std::unordered_map<unsigned char, KeyState*> m_mapKeyState;
	std::unordered_map<std::string, BindKey*> m_mapBindKey;
	bool m_Ctrl;
	bool m_Alt;
	bool m_Shift;
	HWND m_hWnd;

	Vector2 m_MousePos;		//윈도우 상 마우스 위치
	Vector2 m_MouseWorldPos; // 월드공간 마우스 위치
	Vector2 m_MouseMove; // 마우스 이동
	bool	m_MouseLDown; //마우스 누른 순간
	bool	m_MouseLPush; //마우스 누르는 중일때
	bool	m_MouseLUp; //마우스 뗄 때
	CollisionProfile* m_MouseProfile;
	CSharedPtr<class CGameObject> m_MouseObj;
	bool m_ShowCursor;

public:
	bool GetMouseLDown()	const
	{
		return m_MouseLDown;
	}

	bool GetMouseLPush()	const
	{
		return m_MouseLPush;
	}

	bool GetMouseLUp()	const
	{
		return m_MouseLUp;
	}
	CollisionProfile* GetMouseProfile() const
	{
		return m_MouseProfile;
	}
	const Vector2& GetMousePos()	const
	{
		return m_MousePos;
	}

	const Vector2& GetMouseWorldPos()	const
	{
		return m_MouseWorldPos;
	}

	const Vector2& GetMouseMove()	const
	{
		return m_MouseMove;
	}

public:
	void ComputeWorldMousePos(const Vector2& CameraPos);

public:
	bool Init(HWND hWnd);
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);

private:
	void UpdateMouse(float DeltaTime);
	void UpdateKeyState(float DeltaTime);
	void UpdateBindKey(float DeltaTime);

	void SetKeyCtrl(const std::string& Name, bool Ctrl = true);
	void SetKeyAlt(const std::string& Name, bool Alt = true);
	void SetKeyShift(const std::string& Name, bool Shift = true);
	
	KeyState* FindKeyState(unsigned char Key); //이진트리 탐색 방식
	BindKey* FindBindKey(const std::string& Name); //이진트리 탐색 방식

public:
	bool AddBindKey(const std::string& Name, unsigned char Key); //어떤 키를 쓸 것인지 추가
	void ClearCallback();

public:
	template <typename T>
	void AddBindFunction(const std::string& KeyName, Input_Type Type,
		T* Object, void (T::* Func)())
	{
		BindKey* Key = FindBindKey(KeyName);

		if (!Key)
			return;

		BindFunction* Function = new BindFunction;

		Function->Obj = Object;
		// 멤버함수를 등록할때 함수주소, 객체주소를 등록해야 한다.
		Function->func = std::bind(Func, Object);

		Key->vecFunction[(int)Type].push_back(Function);
	}

	DECLARE_SINGLE(CInput)
};

