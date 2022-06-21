#pragma once

#include "AnimationInfo.h"

class CAnimation
{
	friend class CGameObject; //�� Ŭ������ ���ӿ�����Ʈ�� ���� �� �� �ִ�.

private:
	CAnimation();
	~CAnimation();

private:
	class CGameObject* m_Owner; //�� �ִϸ��̼��� �������ִ� ������Ʈ
	class CScene* m_Scene; // � ���� �����ִ���
	std::unordered_map<std::string, class CAnimationInfo*>	m_mapAnimation; //���鶧 �����Ҵ����� ����
	//�׷��Ƿ� �Ҹ��ڿ��� ���Ÿ� ���־�� ��
	//�ִϸ��̼� ��� �������� ���⿡ ����س��� ��ü�ؼ� ����
	//(idle, walk..)
	 CAnimationInfo* m_CurrentAnimation; //���� ���۵ǰ� �ִ� �ִϸ��̼��� �ּҸ� ������.
	 std::function<void()> m_CurrentAnimationEndFunc;

public:
	//���ϴ� �������� �߰��ϴ� �Լ�
	void AddAnimation(const std::string& SequenceName, bool Loop = true,
		float PlayTime = 1.f, float PlayScale = 1.f,
		bool Reverse = false);
	void SetPlayTime(const std::string& Name, float PlayTime); //
	void SetPlayScale(const std::string& Name, float PlayScale);
	void SetPlayLoop(const std::string& Name, bool Loop);
	void SetPlayReverse(const std::string& Name, bool Reverse);
	void SetCurrentAnimation(std::string& Name); //���� �����ϴ� �ִϸ��̼� ����
	void ChangeAnimation(const std::string& Name); //�ٲ� �ִϸ��̼�
	bool CheckCurrentAnimation(const std::string& Name); //���� ���۵ǰ� �ִ� �ִϸ��̼��� ������� Ȯ��
	void Update(float DeltaTime);

private:
	CAnimationInfo* FindInfo(const std::string& Name);

public:
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void(T::* Func)()) 
		//�ִϸ��̼� ������ �۵��ϴ� �Լ�
	{
		CAnimationInfo* Info = FindInfo(Name);

		if (!Info)
			return;

		Info->SetEndFunction<T>(Obj, Func);
	}

	template <typename T>
	void AddNotify(const std::string& Name, int Frame, T* Obj, void(T::* Func)())
		//Ư�� ������ ��ǿ� �Լ� �߰� 
	{
		CAnimationInfo* Info = FindInfo(Name);

		if (!Info)
			return;

		Info->AddNotify<T>(Frame, Obj, Func);
	}
	template <typename T>
	void SetCurrentAnimationEndFunction(T* Obj, void(T::* Func)())
	{
		m_CurrentAnimationEndFunc = std::bind(Func, Obj);
	}
};

