#pragma once
#include "../GameInfo.h"
#include "../GameObject/Card.h"
#include "../Singletone.h"
//카드의 껍데기를 만들어주고 리스트로 만들어주는 클래스
class CCardManager
{
	friend class CScene;
	friend class CSceneManager;	
	//카드 띄우기
	//카드 만들기
	
public:
	class CScene* m_Scene;

	//vector<CCard*> m_allCard; //구현한 모든 카드를 담는다

	vector<CCard*> m_mainDeck;  //핵심 덱
	//int m_mainDeckCount;

	vector<CCard*> m_bringCardDummy; //뽑을 카드 더미
	//int m_bringCardCount;

	vector<CCard*> m_disCardDummy; //버린 카드 더미
	//int m_disCardCount;

	vector<CCard*> m_Hand; //손패

	bool m_UsedCard;
	bool m_MouseClicked;
	class CGameObject* m_CardCheck;
	//사용한 카드 더미
	
public:
	//void AddCardToMyDeck(); //카드를 리스트에 추가한다
		
	//void SetAllCard(vector<CCard*> AllCardDeck) {
	//	m_allCard = AllCardDeck;
	//}
	//vector<CCard*> GetAllCard()
	//{
	//	return m_allCard;
	//}

	vector<CCard*> GetMainDeck() {
		return m_mainDeck;
	}
	vector<CCard*> GetHand() {
		return m_Hand;
	}
	void SetHand(vector<CCard*> hand)
	{
		m_Hand = hand;
	}
	void SetMainDeck(vector<CCard*> usingDeck)
	{
		m_mainDeck = usingDeck;
	}
	int getMaindeckCount() {
		return m_mainDeck.size();
	}
	int getBringCardCount() {
		return m_bringCardDummy.size();
	}
	int getDiscardCount() {
		return m_disCardDummy.size();
	}
	void InitMyDeck(); //타격 5장, 수비 4장

	void SetBringDeck(); //사용할 카드의 덱을 짠다
	
	void DrawCard(int value); //브링덱에서 n개의 카드를 가져온다. //큐로 가져오자

	void AddDiscard(CGameObject* Discard); //사용한 카드 혹은 턴종료 시 핸드의 모든 카드를 버린다.

	void BattleStart(); //전투 시작될 때 세팅

	//카드 조작 관련
	CGameObject* CardCheck();

	void SetCardCheck(CGameObject* card) 
	{
		m_CardCheck = card;
	}

	bool GetMouseClicked()
	{
		return m_MouseClicked;
	}
	void SetMouseClicked(bool Check)
	{
		m_MouseClicked = Check;
	}

	void HandSort();
	void UseCard();
	bool Init();

	DECLARE_SINGLE(CCardManager)
};

