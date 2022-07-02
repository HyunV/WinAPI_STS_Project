#pragma once
#include "../GameInfo.h"
#include "../GameObject/Card.h"
#include "../Singletone.h"
//ī���� �����⸦ ������ְ� ����Ʈ�� ������ִ� Ŭ����
class CCardManager
{
	friend class CScene;
	friend class CSceneManager;	
	//ī�� ����
	//ī�� �����
	
public:
	class CScene* m_Scene;

	//vector<CCard*> m_allCard; //������ ��� ī�带 ��´�

	vector<CCard*> m_mainDeck;  //�ٽ� ��
	//int m_mainDeckCount;

	vector<CCard*> m_bringCardDummy; //���� ī�� ����
	//int m_bringCardCount;

	vector<CCard*> m_disCardDummy; //���� ī�� ����
	//int m_disCardCount;

	vector<CCard*> m_Hand; //����

	bool m_UsedCard;
	bool m_MouseClicked;
	class CGameObject* m_CardCheck;
	//����� ī�� ����
	
public:
	//void AddCardToMyDeck(); //ī�带 ����Ʈ�� �߰��Ѵ�
		
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
	void InitMyDeck(); //Ÿ�� 5��, ���� 4��

	void SetBringDeck(); //����� ī���� ���� §��
	
	void DrawCard(int value); //�긵������ n���� ī�带 �����´�. //ť�� ��������

	void AddDiscard(CGameObject* Discard); //����� ī�� Ȥ�� ������ �� �ڵ��� ��� ī�带 ������.

	void BattleStart(); //���� ���۵� �� ����

	//ī�� ���� ����
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

