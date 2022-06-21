#pragma once
//인라인 클래스 스마트 포인터
//템플릿이라 인라인으로 만들었다.
template <typename T>
class CSharedPtr
{
public:
	CSharedPtr() :
		m_Ptr(nullptr) //초기화
	{
	}

	CSharedPtr(const CSharedPtr<T>& ptr) //복사생성자
	{
		m_Ptr = ptr.m_Ptr;

		if (m_Ptr) //널포인터 아닐 시
			m_Ptr->AddRef(); //레퍼런스 카운터 추가

	}
	CSharedPtr(T* ptr) //템플릿으로 받을 때
	{
		m_Ptr = ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}
	~CSharedPtr()
	{
		if (m_Ptr)
			m_Ptr->Release(); //감소
	}

private:
	T* m_Ptr;

//스마트포인터 오퍼레이터
public:
	void operator = (const CSharedPtr<T>& ptr)
	{
		//기존에 참조하고 있는 객체가 있을 경우 카운트 1감소
		if (m_Ptr)
			m_Ptr->Release();
		 
		m_Ptr = ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	void operator = (T* ptr)
	{
		// 기존에 참조하고 있던 객체가 있을 경우 카운트를 1 감소한다.
		if (m_Ptr)
			m_Ptr->Release();

		m_Ptr = ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	bool operator == (const CSharedPtr<T>& ptr) const //메모리 주소 같은지 비교
	{
		//여기 클래스의 ptr이랑, 매개변수로 받아오는 ptr의 비교
		return m_Ptr == ptr.m_Ptr;

	}

	bool operator == (T* ptr) const //메모리 주소 같은지 비교
	{
		return m_Ptr == ptr;
	}
	bool operator != (const CSharedPtr<T>& ptr)	const //다른지 비교
	{
		return m_Ptr != ptr.m_Ptr;
	}

	bool operator != (T* ptr)	const //다른지 비교
	{
		return m_Ptr != ptr;
	}
	
	//컨버전: 받아오는거 자체를 T*타입으로 인식하게 만들어준다.
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

