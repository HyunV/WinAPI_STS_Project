#pragma once
#include "../GameInfo.h"
#include "../GameObject/Card.h"
#include "../Singletone.h"
//ī���� �����⸦ ������ְ� ����Ʈ�� ������ִ� Ŭ����
class CCardManager
{
	friend class CScene;
	friend class CSceneManager;
public:
	
	//ī�� ����
	//ī�� �����
	
private:
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

	bool m_MouseHovered;

	class CGameObject* m_CardCheck;
	//����� ī�� ����
	
	//���� �ý��� ����
	bool m_PlayerTurn;
	bool m_MonstersTurn;
	int m_TurnCount;
	int m_DrawCard;

	class CTurnEffect* m_Temp; //�����Ǿ��ִ��� ����
	//
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
		return (int)m_mainDeck.size();
	}
	int getBringCardCount() {
		return (int)m_bringCardDummy.size();
	}
	int getDiscardCount() {
		return (int)m_disCardDummy.size();
	}
	void SetBringCardDeck(vector<CCard*> deck) {
		m_bringCardDummy = deck;
	}
	vector<CCard*> GetBringDeck() {
		return m_bringCardDummy;
	}
	void SetDiscardDeck(vector<CCard*> deck) {
		m_disCardDummy = deck;
	}
	vector<CCard*> GetDiscardDeck() {
		return m_disCardDummy;
	}
	void SetPlayerTurn(bool Enable );

	bool GetPlayerTurn()
	{
		return m_PlayerTurn;
	}
	void SetMonstersTurn(bool Enable)
	{
		m_MonstersTurn = Enable;
	}
	bool GetMonstersTurn()
	{
		return m_MonstersTurn;
	}
	void SetTurnCount(int value)
	{
		m_TurnCount = value;
	}
	int GetTurnCount()
	{
		return m_TurnCount;
	}
	void SetTurnEffect(CTurnEffect* Temp)
	{
		m_Temp = Temp;
	}
	class CTurnEffect* GetTurnEffect() const
	{
		return m_Temp;
	}
	int GetDrawCard()
	{
		return m_DrawCard;
	}
	void SetDrawCard(int value)
	{
		m_DrawCard = value;
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

	bool GetMouseHovered()
	{
		return m_MouseHovered;
	}
	void SetMouseHovered(bool Check)
	{
		m_MouseHovered = Check;
	}
	bool GetMouseClicked()
	{
		return m_MouseClicked;
	}
	void SetMouseClicked(bool Check)
	{
		m_MouseClicked = Check;
	}

	void EnableHand(bool Enable);
	void HandSort();
	void CardView(vector<CCard*> deck);
	void ClearCard(vector<CCard*> deck);
	void HandToDiscard(); //�� ���� �� ���� �ڵ带 ��� ������
	int Rand(int n);
	bool Init();

	DECLARE_SINGLE(CCardManager)
};

