#pragma once
#include "GameObject.h"
#include "../GameInfo.h"
#include "../CardFlag.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
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
    std::string m_cardName; //ī�� �̸�
    int m_cost; // ī�� �ڽ�Ʈ
    Card_Type m_cardType; //ī�� Ÿ��
    Card_Value m_cardValue; //ī�� ��͵�

    int m_CardPower;

    bool m_colorless; //���� ����
    bool m_curse;  //���� ���� 
    bool m_Enhanced; // ��ȭ����
    char m_CardExplain[256];
    bool m_EnableCollider; //ī�� �浹 Ȱ��ȭ
    bool m_cardMove; //ī�� �̵� ����

    

    //ī�忡 ���� �ؽ�Ʈ ������ ���� ����
    CSharedPtr<class CWidgetComponent> m_MycardName;
    CSharedPtr<class CWidgetComponent> m_MycardType;
    CSharedPtr<class CWidgetComponent> m_MycardExplain;
    vector<CSharedPtr<class CWidgetComponent>> m_Explains;
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


    list<CSharedPtr<class CCardAbility>> m_Abilitys;

    //class CardAbility* m_Ability;

protected:

    virtual bool Init();
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Update(float DeltaTime);

public:
    void SetCardInfo(string CardName, Card_Type Type, Card_Value Value, bool colorless, bool curse); //ī���� Ÿ�԰� ��ġ�� ����
    //void SetCardAttribute(const TCHAR* cardName, const TCHAR* cardType, const TCHAR* cardExplain, const TCHAR* cardCost); //�̸�, Ÿ��, ����, �ڽ�Ʈ
    void SetCardAttribute(const TCHAR* cardName, Card_Type cardType, int cost);
    //void Ch
    virtual void SetAbility();//ī�� �ɷ� �ο�

public:
    void AddAbility(class CCardAbility* Ability);
    

//ī�� �̹��� �Ŵ���,(�Ϸ���Ʈ, ī��, �׵θ� ��, ������, �ڽ�Ʈ)
//ī�� Ʋ, �̹���, �׵θ�, ������, �ڽ�Ʈ
public:
    //ī�� ����(ī�� ���̵�, ī�� �̸�, ī�� �̹���, ���, ī�� Ÿ��, �÷�(�Ⱦ�), ���,
    
    void SetCardName(std::string cardName)
    {
         m_cardName = cardName;
    }
    void SetCardCost(int cost) 
    {
        m_cost = cost;
    }

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

    virtual void useCard(CGameObject* Target);

    

private:
    void CollisionMouseBegin(CCollider* Src, const Vector2& MousePos);
    void CollisionMouseEnd(CCollider* Src, const Vector2& MousePos);
    void CollisionBegin(CCollider* Src, CCollider* Dest);
    void CollisionEnd(CCollider* Src, CCollider* Dest);




   std::string m_CardImage;

};

