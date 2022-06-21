#pragma once
//레퍼런스 카운트 확인 클래스
//텍스처같이 클래스를 공유하는 일이 잦으면 이 클래스를 상속시켜 관리해주면 편하다.
#include "GameInfo.h"

class CRef
{
public:
	CRef();
	CRef(const CRef& ref);
	virtual ~CRef(); //상속용이라 버추얼 키워드

protected:
	int		m_RefCount;
	std::string	m_Name; // 지정한 이름
	std::string	m_TypeName;// 타입 이름
	size_t	m_TypeID; // id 값?
	bool	m_Enable;	// 활성, 비활성
	bool	m_Active;	// 살아 있는지 죽었는지 이걸 이용해서 안전하게 객체를 뺄 예정

public:
	void AddRef(); //++
	int Release(); //--, 소멸


public:
	int GetRefCount()	const
	{
		return m_RefCount;
	}

	bool GetEnable()	const
	{
		return m_Enable;
	}

	bool GetActive()	const
	{
		return m_Active;
	}

	size_t GetTypeID()	const
	{
		return m_TypeID;
	}

	const std::string& GetTypeName()	const
	{
		return m_TypeName;
	}

	const std::string& GetName()	const
	{
		return m_Name;
	}

	void SetEnable(bool Enable)
	{
		m_Enable = Enable;
	}

	void SetActive(bool Active)
	{
		m_Active = Active;
	}

	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}

	template <typename T>
	bool CheckTypeID()	const
	{
		return m_TypeID == typeid(T).hash_code(); //타입인포 관련 헤더, 무슨 타입인지 알아온다.
	}

public:
	template <typename T>
	void SetTypeID()
	{
		// 타입 이름을 문자열로 얻어온다.
		m_TypeName = typeid(T).name();

		// 타입의 고유한 번호를 얻어온다.
		m_TypeID = typeid(T).hash_code();
	}
};

