#pragma once
//���۷��� ī��Ʈ Ȯ�� Ŭ����
//�ؽ�ó���� Ŭ������ �����ϴ� ���� ������ �� Ŭ������ ��ӽ��� �������ָ� ���ϴ�.
#include "GameInfo.h"

class CRef
{
public:
	CRef();
	CRef(const CRef& ref);
	virtual ~CRef(); //��ӿ��̶� ���߾� Ű����

protected:
	int		m_RefCount;
	std::string	m_Name; // ������ �̸�
	std::string	m_TypeName;// Ÿ�� �̸�
	size_t	m_TypeID; // id ��?
	bool	m_Enable;	// Ȱ��, ��Ȱ��
	bool	m_Active;	// ��� �ִ��� �׾����� �̰� �̿��ؼ� �����ϰ� ��ü�� �� ����

public:
	void AddRef(); //++
	int Release(); //--, �Ҹ�


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
		return m_TypeID == typeid(T).hash_code(); //Ÿ������ ���� ���, ���� Ÿ������ �˾ƿ´�.
	}

public:
	template <typename T>
	void SetTypeID()
	{
		// Ÿ�� �̸��� ���ڿ��� ���´�.
		m_TypeName = typeid(T).name();

		// Ÿ���� ������ ��ȣ�� ���´�.
		m_TypeID = typeid(T).hash_code();
	}
};

