#pragma once
/*
�ִϸ��̼� �������� �ϳ� ������ �����鼭
��© �����, �������� ���� �����ϴ� ��ü
//���⼭ run info, idle info, attack info ���� �����ٵ� �װ� �ִϸ��̼� Ŭ�������� �����̳ʿ� ��� �����Ѵ�.
*/
//�ִϽ�����+�ִ����� -> �ִϸ��̼� Ŭ���� 
#include "../GameInfo.h"

//Notify: ��Ÿ ������ : Ȱ��� ��ų�� �� �� Ȱ ������ ���� �����°�ó��
//���� ���ϴ� �����ӿ� �Լ��� ����ϴ� �ý��� : Notify
struct AnimationNotify
{
	int		Frame; //�� ��° �����ӿ� �������
	bool	Call;  //���� ����� ���۵� �� �Լ��� �� �Ǵ��� ����
	//���� ������ ���� ����:
	/*
		4���������� 4���� ����� �ִ�.
		| | | |
		2��° �������� Notify�� 2�� �� �ִ�.
		4�� �������� 1�� ���� �� �ð��� 1�ʶ�� n���� n+1 �� ���� �ð��� 0.25���̴�.
		�� 0.25�ʷ� ���� 2��° ������ -> 3��° ���������� ���µ� Notify �Լ��� ���� 1���� �ƴ�
		������ ���� ȣ�� �� �� �ִ�. �̸� �ݺ����� ����� �Լ��� �ѹ� ����Ǹ� ���̻� ������� �ʰ� �������ش�.
	*/
	std::function<void()>	Function; //������ �Լ�

	AnimationNotify() :
		Frame(0),
		Call(false)
	{
	}
};


class CAnimationInfo
{
	friend class CAnimation;
	friend class CGameObject;

private:
	CAnimationInfo();
	~CAnimationInfo();

private:
	CSharedPtr<class CAnimationSequence>	m_Sequence; //������ �޾ƿ���
	int				m_Frame;	// ���� �ִϸ��̼��� ���۵Ǵ� ������.
	float			m_Time;		// �ִϸ��̼� �������� ���������ֱ� ���� �ð���.
								// 3������ �ѹ��� �����µ� 1�ʰ� �ɸ��� 1�����Ӵ� �ɸ��� �ð��� 0.33��, �� 0.33�ʰ� �������� �Ǵ��ϴ� ��

	float			m_FrameTime;	// �� �������� �����ϱ� ���� �ð�. (0.33�ʰ� ������ ����)
	float			m_PlayTime;		// ��� �ѹ��� ���۵Ǳ� ���� �ð�. (��� �ѹ��� ���� �ð�) 
									// 1�� �������ָ� 1�ʿ� ��©�� ���� (���� �ʴ� ���� �����ϸ� ����)

	float			m_PlayScale;	// ����ӵ� ����.
	bool			m_Loop;			// �ݺ��ؼ� ����ؾ� �ϴ��� ����.
	bool			m_Reverse;		// ����� ����.
	std::function<void()>		m_EndFunction;	// �ִϸ��̼��� ���������� ȣ��� �Լ� ���.
	
	std::vector<AnimationNotify*>	m_vecNotify; //������ �̺�Ʈ�� ������ ����� �� �ְ� �迭��

public:
	template <typename T>
	void SetEndFunction(T* Obj, void(T::* Func)())
	{
		m_EndFunction = std::bind(Func, Obj);
	}

	template <typename T>
	void AddNotify(int Frame, T* Obj, void(T::* Func)()) //���° ������, � ������Ʈ����, �߻��� �̺�Ʈ �Լ�)
	{
		AnimationNotify* Notify = new AnimationNotify;

		Notify->Frame = Frame;
		Notify->Function = std::bind(Func, Obj);

		m_vecNotify.push_back(Notify);
	}
};

