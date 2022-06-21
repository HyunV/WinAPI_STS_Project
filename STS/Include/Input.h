#pragma once
//�Է��� �޾����� (�⺻ �Է�, �� ������ ��, Ŀ�ǵ� �Է��� ��, Ű���� �� ��, ���콺 Ŭ�� ��)
#include "GameInfo.h"
#include "Singletone.h"
//vk Ŀ�ǵ� �ø���� 255�� ���� unsigned char�� ���
// 
// GetAsyncKeyState : Ű�� ���¸� üũ�� �� �ִ�.
// 0 : �ȴ�������.
// 0x8000 : Ű ���� ����.
// 0x1 : Ű�� ���� �����ӿ� ���� ����.

enum class Input_Type //�Ÿ������ ���ȴ��� �׸�
{
	Down, //������ ����
	Push,//������ ��
	Up, //�� ��
	End 
};

struct KeyState
{
	unsigned char key;
	bool Down; //������ ����
	bool Push; //������ ��
	bool Up; //�� ��

	KeyState() : //�̴ϼȶ�����?
		key(0),
		Down(false),
		Push(false),
		Up(false)
	{
	}
};

//���ϴ� �Լ��� �̰�
struct BindFunction
{
	void* Obj; //void ������ Ÿ�� Obj
	//��� ���� Ÿ���� �����͸� �����ϱ� ���� �̷��� ����
	std::function<void()> func; //function ���

	BindFunction() :
		Obj(nullptr)
	{
	}
};

//���ε� Ű : Ŀ�ǵ�
struct BindKey //����Ű Ŀ�ǵ�
{
	//���ε� Ű�� �ʿ��� ������
	std::string Name; //���� ����Ű���� �̸������ִ� �뵵 ����
	KeyState* key; //� Ű�� ����ϴ��� (Down, Up, push)
	bool Ctrl;
	bool Alt;
	bool Shift;

	//Ű�� ������ �� ������ �� �ִ� �Լ����� ���� ����
	
	//����Լ� ����Ҷ��� ��ü���� �ݵ�� ���������� vector<Ÿ��>�̸�
	std::vector<BindFunction*> vecFunction[(int)Input_Type::End]; //���� ũ�� 3�� ������ٴ� ��? [0] : Down, [1] Push, [2] Up 
	//BindFunction Ÿ�� ����
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

	Vector2 m_MousePos;		//������ �� ���콺 ��ġ
	Vector2 m_MouseWorldPos; // ������� ���콺 ��ġ
	Vector2 m_MouseMove; // ���콺 �̵�
	bool	m_MouseLDown; //���콺 ���� ����
	bool	m_MouseLPush; //���콺 ������ ���϶�
	bool	m_MouseLUp; //���콺 �� ��
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
	
	KeyState* FindKeyState(unsigned char Key); //����Ʈ�� Ž�� ���
	BindKey* FindBindKey(const std::string& Name); //����Ʈ�� Ž�� ���

public:
	bool AddBindKey(const std::string& Name, unsigned char Key); //� Ű�� �� ������ �߰�
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
		// ����Լ��� ����Ҷ� �Լ��ּ�, ��ü�ּҸ� ����ؾ� �Ѵ�.
		Function->func = std::bind(Func, Object);

		Key->vecFunction[(int)Type].push_back(Function);
	}

	DECLARE_SINGLE(CInput)
};

