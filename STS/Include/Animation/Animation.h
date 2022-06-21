#pragma once

#include "AnimationInfo.h"

class CAnimation
{
	friend class CGameObject; //이 클래스는 게임오브젝트가 갖다 쓸 수 있다.

private:
	CAnimation();
	~CAnimation();

private:
	class CGameObject* m_Owner; //이 애니메이션을 가지고있는 오브젝트
	class CScene* m_Scene; // 어떤 씬에 속해있는지
	std::unordered_map<std::string, class CAnimationInfo*>	m_mapAnimation; //만들때 동적할당으로 생성
	//그러므로 소멸자에서 제거를 해주어야 됨
	//애니메이션 모션 여러개를 여기에 등록해놓고 교체해서 쓴다
	//(idle, walk..)
	 CAnimationInfo* m_CurrentAnimation; //현재 동작되고 있는 애니메이션의 주소를 가진다.
	 std::function<void()> m_CurrentAnimationEndFunc;

public:
	//원하는 시퀀스를 추가하는 함수
	void AddAnimation(const std::string& SequenceName, bool Loop = true,
		float PlayTime = 1.f, float PlayScale = 1.f,
		bool Reverse = false);
	void SetPlayTime(const std::string& Name, float PlayTime); //
	void SetPlayScale(const std::string& Name, float PlayScale);
	void SetPlayLoop(const std::string& Name, bool Loop);
	void SetPlayReverse(const std::string& Name, bool Reverse);
	void SetCurrentAnimation(std::string& Name); //현재 동작하는 애니메이션 지정
	void ChangeAnimation(const std::string& Name); //바꿀 애니메이션
	bool CheckCurrentAnimation(const std::string& Name); //현재 동작되고 있는 애니메이션이 어떤거인지 확인
	void Update(float DeltaTime);

private:
	CAnimationInfo* FindInfo(const std::string& Name);

public:
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void(T::* Func)()) 
		//애니메이션 끝나면 작동하는 함수
	{
		CAnimationInfo* Info = FindInfo(Name);

		if (!Info)
			return;

		Info->SetEndFunction<T>(Obj, Func);
	}

	template <typename T>
	void AddNotify(const std::string& Name, int Frame, T* Obj, void(T::* Func)())
		//특정 프레임 모션에 함수 추가 
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

