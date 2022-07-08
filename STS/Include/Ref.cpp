#include "Ref.h"

CRef::CRef() :
	m_RefCount(0),
	m_Enable(true),
	m_Active(true),
	m_TypeID(0)
{

}

CRef::CRef(const CRef& ref) : //복사생성자 Ref를 0부터 시작하게 만듬
	m_RefCount(0),
	m_TypeName(ref.m_TypeName),
	m_TypeID(ref.m_TypeID),
	m_Enable(ref.m_Enable),
	m_Active(ref.m_Active)
{

}

CRef::~CRef()
{
}

void CRef::AddRef()
{
	++m_RefCount;
}

int CRef::Release()
//a객체에 release 멤버함수를 호출하고 a객체를 지울 수 있는가? -> 가능
{//널ptr로 함수 호출했던거 생각 ->멤버함수를 쓰지만 않는다면 가능했었다
	--m_RefCount;

	if (m_RefCount <= 0)
	{
		delete this; //0이될때 원본 객체를 지워버린다
		//위의 질문주석을 응용하여 this로 지우고 멤버변수 로 갖다 쓰게 된다면 문제가 된다.
		return 0;
	}

	return m_RefCount;
}
