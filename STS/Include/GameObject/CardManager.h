#pragma once
#include "../GameInfo.h"
#include "../GameObject/Card.h"
#include "../Singletone.h"
//카드의 껍데기를 만들어주고 리스트로 만들어주는 클래스
class CCardManager
{
public:
	CCardManager();
	~CCardManager();

	//카드 띄우기
	//카드 만들기

private:
	vector<CCard*> m_allCard; //구현한 모든 카드를 담는다
	vector<CCard*> m_mainDeck;  //핵심 덱
	vector<CCard*> m_bringCardDummy; //뽑을 카드 더미
	vector<CCard*> m_throwCardDummy; //버린 카드 더미
	//std::vector<CCard*> m_extinctCardDummy; //소멸된 카드 더미


	//std::list<CCard*> m_discarddeck;
	// 
	// 
	//std 붙은 애들은 컨테이너
public:
	template<typename T>
	T* CreateCard(const std::string& cardName, int cost, Card_Type cardType, Card_Value cardValue) 
	{
		//카드를 생성한다
		T* card = new T();
		
		//카드에 값을 추가해준다.

		card->m_cardName = cardName;
		card->m_cost = cost;
		card->m_cardType = cardType;
		card->m_cardValue = cardValue;

		//생성한 카드를 리스트에 넣는다
		//m_myDeck.push_back(card);
	}
	void AddCardToMyDeck() {
		//카드를 리스트에 추가한다
	}

	//DECLARE_SINGLE(CCardManager)
};

