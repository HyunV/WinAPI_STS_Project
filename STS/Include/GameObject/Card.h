#pragma once
#include "GameObject.h"
#include "../GameInfo.h"
#include "../CardFlag.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
//ī���� �ɼ��� �ٷ�� Ŭ����
//�߻�Ŭ����
class CCard :
    public CGameObject
{
    friend class CScene;


protected:
    CCard();
    virtual ~CCard();

    
    //��� ī�尡 ������ �ִ� ������ ��� -? 
    //> ī�带 �׸���
    
    //��� ī�尡 ������ �ִ� ������ ����
protected:
    std::string m_cardName;
    int m_cost; // ī�� �ڽ�Ʈ
    Card_Type m_cardType;
    Card_Value m_cardValue;
    bool m_colorless;
    bool m_curse;

    bool m_cardMove; //ī�� �̵� ����

    //ī�忡 ���� �ؽ�Ʈ ������ ���� ����
    CSharedPtr<class CWidgetComponent> m_MycardName;
    CSharedPtr<class CWidgetComponent> m_MycardType;
    CSharedPtr<class CWidgetComponent> m_MycardExplain;
    CSharedPtr<class CWidgetComponent> m_MycardCost;

    vector<wstring> cardPanelFiles; //ī�� �г� �迭

    vector<wstring> cardEdgeFiles; //ī�� �׵θ�
    Vector2 m_cardEdgeSize;
    Vector2 m_cardEdgeOffset;

    vector<wstring> cardNameTagFiles; //ī�� ������
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
    

//ī�� �̹��� �Ŵ���,(�Ϸ���Ʈ, ī��, �׵θ� ��, ������, �ڽ�Ʈ)
//ī�� Ʋ, �̹���, �׵θ�, ������, �ڽ�Ʈ
public:
    //ī�� ����(ī�� ���̵�, ī�� �̸�, ī�� �̹���, ���, ī�� Ÿ��, �÷�(�Ⱦ�), ���,
    //void CreateCard(std::string m_cardName, int m_Cost, (int)Card_Type cardType); //ī�� �̸�, �ڽ�Ʈ 
    //void MakeCardImage(); //����:ī�� Ÿ��(������), ī�� ����, ���, �ڽ�Ʈ ����, 
    
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

