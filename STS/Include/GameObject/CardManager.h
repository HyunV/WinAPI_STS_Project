#pragma once
#include "../GameInfo.h"
#include "../GameObject/Card.h"
#include "../Singletone.h"
//카드의 껍데기를 만들어주고 리스트로 만들어주는 클래스
class CCardManager
{
	friend class CScene;
	friend class CSceneManager;
public:
	
	//카드 띄우기
	//카드 만들기
	
private:
	class CScene* m_Scene;

	vector<CCard*> m_allCard; //구현한 모든 카드를 담는다

	vector<CCard*> m_mainDeck;  //핵심 덱
	//int m_mainDeckCount;

	vector<CCard*> m_bringCardDummy; //뽑을 카드 더미
	//int m_bringCardCount;

	vector<CCard*> m_disCardDummy; //버린 카드 더미
	//int m_disCardCount;

	vector<CCard*> m_delCardDummy; //버려진 카드 더미

	vector<CCard*> m_Hand; //손패

	bool m_UsedCard;

	bool m_MouseClicked;

	bool m_MouseHovered;

	class CGameObject* m_CardCheck;
	//사용한 카드 더미
	
	//게임 시스템 설계
	bool m_PlayerTurn;
	bool m_MonstersTurn;
	int m_TurnCount;
	int m_DrawCard;

	class CTurnEffect* m_Temp; //생성되어있는지 여부

	int m_StageLevel;


	//몬스터 공격 순서
	int m_AtkCount;
	//
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
	int GetStageLevel()
	{
		return m_StageLevel;
	}
	void SetStageLevel(int value)
	{
		m_StageLevel = value;
	}
	void AddStageLevel()
	{
		m_StageLevel += 1;
	}
	void SetMonsterAttackCount(int value) 
	{
		m_AtkCount = value;
	}
	int GetMonsterAttackCount()
	{
		return m_AtkCount;
	}
	void AddMonstersAttackCount()
	{
		m_AtkCount += 1;
	}

	void InitMyDeck(); //타격 5장, 수비 4장

	void SetBringDeck(); //사용할 카드의 덱을 짠다
	
	void DrawCard(int value); //브링덱에서 n개의 카드를 가져온다. //큐로 가져오자

	void AddDiscard(CGameObject* Discard); //사용한 카드 혹은 턴종료 시 핸드의 모든 카드를 버린다.

	void AddExhaustcard(CGameObject* Deletecard); //파워카드, 혹은 소멸카드는 일회용


	void BattleStart(); //전투 시작될 때 세팅

	void ClearHand(); //핸드를 비운다
	void BattleReset(); //배틀 종료시 패를 초기화한다.

	//카드 조작 관련
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

	void EnableHand(bool Enable); //손패 보이게 안보이게 여부
	void HandSort(); //손 패 정렬 및 enable 해줌
	void CardView(vector<CCard*> deck); //카드 보여주는 함수
	void ClearCard(vector<CCard*> deck); //카드 보여주기 끝낼 때 위치 초기화 함수
	void HandToDiscard(); //턴 종료 시 남은 핸드를 모두 버린다
	void RemoveHand(); //카드 사용 시 핸드에서 비우는 함수
	void RemoveHandAll();
	
	void SetRandomDeck(int value = 10); //이번 게임에서 사용할 덱을 산정

	//난수
	int Rand(int End); //시작범위 넣을거면 2번째 인자에 추가
	int RangeRand(int Min, int Max);
	bool PercentRand(int Percent);

	bool Init();

	DECLARE_SINGLE(CCardManager)
};

