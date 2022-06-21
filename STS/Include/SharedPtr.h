#pragma once
//�ζ��� Ŭ���� ����Ʈ ������
//���ø��̶� �ζ������� �������.
template <typename T>
class CSharedPtr
{
public:
	CSharedPtr() :
		m_Ptr(nullptr) //�ʱ�ȭ
	{
	}

	CSharedPtr(const CSharedPtr<T>& ptr) //���������
	{
		m_Ptr = ptr.m_Ptr;

		if (m_Ptr) //�������� �ƴ� ��
			m_Ptr->AddRef(); //���۷��� ī���� �߰�

	}
	CSharedPtr(T* ptr) //���ø����� ���� ��
	{
		m_Ptr = ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}
	~CSharedPtr()
	{
		if (m_Ptr)
			m_Ptr->Release(); //����
	}

private:
	T* m_Ptr;

//����Ʈ������ ���۷�����
public:
	void operator = (const CSharedPtr<T>& ptr)
	{
		//������ �����ϰ� �ִ� ��ü�� ���� ��� ī��Ʈ 1����
		if (m_Ptr)
			m_Ptr->Release();
		 
		m_Ptr = ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	void operator = (T* ptr)
	{
		// ������ �����ϰ� �ִ� ��ü�� ���� ��� ī��Ʈ�� 1 �����Ѵ�.
		if (m_Ptr)
			m_Ptr->Release();

		m_Ptr = ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	bool operator == (const CSharedPtr<T>& ptr) const //�޸� �ּ� ������ ��
	{
		//���� Ŭ������ ptr�̶�, �Ű������� �޾ƿ��� ptr�� ��
		return m_Ptr == ptr.m_Ptr;

	}

	bool operator == (T* ptr) const //�޸� �ּ� ������ ��
	{
		return m_Ptr == ptr;
	}
	bool operator != (const CSharedPtr<T>& ptr)	const //�ٸ��� ��
	{
		return m_Ptr != ptr.m_Ptr;
	}

	bool operator != (T* ptr)	const //�ٸ��� ��
	{
		return m_Ptr != ptr;
	}
	
	//������: �޾ƿ��°� ��ü�� T*Ÿ������ �ν��ϰ� ������ش�.
	operator T* ()	const
	{
		return m_Ptr;
	}
	
	T* operator -> ()	const
	{
		return m_Ptr;
	}

	T* operator * ()	const
	{
		return m_Ptr;
	}

	T* Get()	const
	{
		return m_Ptr;
	}
};

