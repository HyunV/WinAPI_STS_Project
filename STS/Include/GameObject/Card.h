#pragma once
#include "GameObject.h"
#include "../GameInfo.h"
#include "../CardFlag.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
//카드의 옵션을 다루는 클래스
//추상클래스
class CCard :
    public CGameObject
{
    friend class CScene;


protected:
    CCard();
    virtual ~CCard();

    
    //모든 카드가 가지고 있는 공통의 기능 -? 
    //> 카드를 그린다
    
    //모든 카드가 가지고 있는 공통의 정보
protected:
    std::string m_cardName;
    int m_cost; // 카드 코스트
    Card_Type m_cardType;
    Card_Value m_cardValue;
    bool m_colorless;
    bool m_curse;

    bool m_cardMove; //카드 이동 세팅

    //카드에 입힐 텍스트 설명을 담을 위젯
    CSharedPtr<class CWidgetComponent> m_MycardName;
    CSharedPtr<class CWidgetComponent> m_MycardType;
    CSharedPtr<class CWidgetComponent> m_MycardExplain;
    CSharedPtr<class CWidgetComponent> m_MycardCost;

    vector<wstring> cardPanelFiles; //카드 패널 배열

    vector<wstring> cardEdgeFiles; //카드 테두리
    Vector2 m_cardEdgeSize;
    Vector2 m_cardEdgeOffset;

    vector<wstring> cardNameTagFiles; //카드 네임택
    Vector2 m_cardNameTagSize;
    Vector2 m_cardNameTagOffset;

    Vector2 m_costImageSize;
    Vector2 m_costImageOffset;

    Vector2 m_cardImageSize;
    Vector2 m_cardImageOffset;

    int m_cardInfo[3];

    bool m_mouseHovered;
    bool m_mouseClicked;
    Vector2 m_cardOriginPos;
    Vector2 m_clickedPos;
    bool m_collisionInteraction;

    Vector2 m_HoveredOffset;
    //class CardAbility* m_Ability;

protected:

    virtual bool Init();
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Update(float DeltaTime);
    

//카드 이미지 매니저,(일러스트, 카드, 테두리 원, 네임택, 코스트)
//카드 틀, 이미지, 테두리, 네임택, 코스트
public:
    //카드 구현(카드 아이디, 카드 이름, 카드 이미지, 비용, 카드 타입, 컬러(안씀), 레어도,
    //void CreateCard(std::string m_cardName, int m_Cost, (int)Card_Type cardType); //카드 이름, 코스트 
    //void MakeCardImage(); //인자:카드 타입(공수파), 카드 종류, 레어도, 코스트 유무, 
    
    void SetCardName(std::string cardName)
    {
         m_cardName = cardName;
    }
    void SetCardCost(int cost) 
    {
        m_cost = cost;
    }

    void SetCardInfo(Card_Type Type, Card_Value Value, bool colorless, bool curse = false);
    void SetCardAttribute(const TCHAR* cardName, const TCHAR* cardType, const TCHAR* cardExplain, const TCHAR* cardCost);

    void SetCardType(Card_Type cardType) 
    {
        m_cardType = cardType;

    }
    void SetCardValue(Card_Value cardValue) 
    {
        m_cardValue = cardValue;
    }
   
    bool SetColorless(bool colorless) {
        return colorless;
    }
    bool SetCurse(bool curse) {
        return curse;
    } 
    
    virtual void useCard();

    //void SetAbility(class CardAbility* Ability)
    //{
    //    m_Ability = Ability;
    //}
private:
    void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
    void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
    void CollisionBegin(CCollider* Src, CCollider* Dest);
    void CollisionEnd(CCollider* Src, CCollider* Dest);
};

