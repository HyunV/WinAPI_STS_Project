#pragma once
#include "../GameInfo.h"
#include "../GameObject/Card.h"
//ī���� �����⸦ ������ְ� ����Ʈ�� ������ִ� Ŭ����
class CCardManager
{
public:
	CCardManager();
	~CCardManager();

	//ī�� ����
	//ī�� �����

private:
	std::list<CCard*> m_myDeck;
	std::list<CCard*> m_deck;
	std::list<CCard*> m_hand;
	//std::list<CCard*> m_discarddeck;
	// 
	// 
	//std ���� �ֵ��� �����̳�
public:
	template<typename T>
	T* CreateCard(const std::string& cardName, int cost, Card_Type cardType, Card_Value cardValue) 
	{
		//ī�带 �����Ѵ�
		T* card = new T();
		
		//ī�忡 ���� �߰����ش�.

		card->m_cardName = cardName;
		card->m_cost = cost;
		card->m_cardType = cardType;
		card->m_cardValue = cardValue;

		//������ ī�带 ����Ʈ�� �ִ´�
		m_myDeck.push_back(card);
	}
	void AddCardToMyDeck() {
		//ī�带 ����Ʈ�� �߰��Ѵ�
	}
};

