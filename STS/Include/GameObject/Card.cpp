#include "Card.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Camera.h"
#include "../Resource/Texture/Texture.h"
#include "../Widget/WidgetWindow.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"
#include "../GameObject/Cards/CardAbility.h"
#include "../GameObject/CardManager.h"
#include "../GameObject/BubbleMessage.h"
#include <sstream>

CCard::CCard()
{
	SetTypeID<CCard>();
	m_mouseHovered = false;
	m_mouseClicked = false;
	m_RenderLayer = ERender_Layer::Hand;
	m_Enable = false;
	m_SelectCard = false;
	m_cardName = "NoName";
	m_colorless = false;
	m_curse = false;
	m_Enhanced = false;
	m_EnableCollider = true;
	m_CardExplain[0] = {};

}

CCard::~CCard()
{
	list<CSharedPtr< CCardAbility>>::iterator iter = m_Abilitys.begin();
	list<CSharedPtr< CCardAbility>>::iterator End = m_Abilitys.end();
	//
	m_Abilitys.clear();
}

bool CCard::Init()
{
	m_cardOriginPos = (0.f, 0.f);
	//1. ī�带 ����
	//-> �ؽ�ó�� �ʿ��ϴ�
	// -> �̹����� ������ �ʿ��ϴ�
	//   ->�̹����� �׸��� ���� �ʿ��Ѱ� ����?
	//		->Texture�� �ȿ��ִ� ImageInfo�� �ִ� HDC  ( hMemDC)
	//			m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	
	////////////////////////////////////////////////////////////////////////
	// 
	// ī�� �̹��� ���

	cardPanelFiles.push_back(TEXT("Cards/cardPanel_C1.bmp"));	 //0
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_C2.bmp"));	 //1
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_C3.bmp"));	 //2
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_R1.bmp"));	 //3
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_R2.bmp"));	 //4
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_R3.bmp"));	 //5
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_Curse.bmp")); //6

	m_Scene->GetSceneResource()->LoadTexture("cardPanel", cardPanelFiles);
	SetSize(148, 209);

	//ī�� �̹���
	m_cardImageSize = Vector2(123, 93);
	m_cardImageOffset = Vector2(13, 20);

	//ī�� �׵θ�
	//ī��Ÿ�Կ����� edge�ؽ�ó�� nameTag�� �̹���
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_C1.bmp")); //	 0  //����
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_C2.bmp")); //  1  //��ų  
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_C3.bmp")); //	 2  //�Ŀ�
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_S1.bmp")); //	 3 
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_S2.bmp")); //	 4 
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_S3.bmp")); //	 5
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_R1.bmp")); //	 6 
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_R2.bmp")); //	 7 
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_R3.bmp")); //	 8

	//ī���������� �̹����� �ҷ��ͼ� �׸� �غ�m_cardEdgeSize
	m_cardEdgeSize = Vector2(135, 119);
	m_cardEdgeOffset = Vector2(7, -1);
	m_Scene->GetSceneResource()->LoadTexture("CardEdge", cardEdgeFiles);

	//ī�� ������
	cardNameTagFiles.push_back(TEXT("Cards/cardNameTag_C.bmp")); //0 COMMON
	cardNameTagFiles.push_back(TEXT("Cards/cardNameTag_S.bmp")); //2 SPECIAL
	cardNameTagFiles.push_back(TEXT("Cards/cardNameTag_R.bmp")); //1 RARE

	m_cardNameTagSize = Vector2(162, 36);
	m_cardNameTagOffset = Vector2(-7, 9);
	m_Scene->GetSceneResource()->LoadTexture("CardNameTags", cardNameTagFiles);

	//�ڽ�Ʈ �̹���
	m_Scene->GetSceneResource()->LoadTexture("CostImage", TEXT("Cards/cardCost.bmp"));
	m_costImageSize = Vector2(35, 34);
	m_costImageOffset = Vector2(-10, -10);



	////////////////////////////////////////////////////////////////////////
	//ī�弼���ϴ� �Լ�
	//SetCardInfo(Card_Type::Attack, Card_Value::Common, false);
	//SetCardAttribute(TEXT("Ÿ��"), TEXT("����"), TEXT("���ظ� 6 �ݴϴ�."), TEXT("3"));

	//�浹ü

	//if (m_EnableCollider) {
		CColliderBox* Box = AddCollider<CColliderBox>("Body");

		Box->SetExtent(148, 208);
		Box->SetCollisionProfile("Card");
		Box->SetOffset(m_Size * 0.5f);

		Box->SetMouseCollisionBeginFunction<CCard>(this, &CCard::CollisionMouseBegin);
		Box->SetMouseCollisionEndFunction<CCard>(this, &CCard::CollisionMouseEnd);
		Box->SetCollisionBeginFunction<CCard>(this, &CCard::CollisionBegin);
		Box->SetCollisionEndFunction<CCard>(this, &CCard::CollisionEnd);
	//}


		//SetCollisionEnable(false);
	return true;
}

void CCard::Render(HDC hDC, float DeltaTime)
{
	//ī�� �������� ��Ƽ� �׷�����
//�г� -> ���� -> ������ -> �ڽ�Ʈ
	CTexture* CardPanelTexture = CResourceManager::GetInst()->FindTexture("cardPanel");

	CTexture* CardEdgeTexture = CResourceManager::GetInst()->FindTexture("CardEdge");

	CTexture* CardNameTagTexture = CResourceManager::GetInst()->FindTexture("CardNameTags");

	CTexture* CardCostTexture = CResourceManager::GetInst()->FindTexture("CostImage");

	CTexture* CardImageTexture = CResourceManager::GetInst()->FindTexture(m_CardImage);


	if (CardPanelTexture)
	{
		Vector2	RenderLT;

		Vector2	CameraPos;
		Vector2	Resolution;
		Vector2 Pos;

		if (m_Scene)
		{
			CameraPos = m_Scene->GetCamera()->GetPos();
			Resolution = m_Scene->GetCamera()->GetResolution();
			Pos = m_Pos - m_Scene->GetCamera()->GetPos();
		}

		RenderLT = Pos;

		//�г� �׸���
		::TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
			(int)m_Size.x, (int)m_Size.y, CardPanelTexture->GetDC(m_cardInfo[0]),
			0, 0, (int)m_Size.x, (int)m_Size.y, CardPanelTexture->GetColorKey(0));

		/////////ī���Ϸ�
		if (CardImageTexture) {
			RenderLT = Pos;

			RenderLT += m_cardImageOffset;

			::TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
				(int)m_cardImageSize.x, (int)m_cardImageSize.y, CardImageTexture->GetDC(0),
				0, 0, (int)m_cardImageSize.x, (int)m_cardImageSize.y, CardImageTexture->GetColorKey(0));
		}

		//ī�� �׵θ�
		if (CardEdgeTexture)
		{
			RenderLT = Pos;

			RenderLT += m_cardEdgeOffset;

			::TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
				(int)m_cardEdgeSize.x, (int)m_cardEdgeSize.y, CardEdgeTexture->GetDC(m_cardInfo[1]),
				0, 0, (int)m_cardEdgeSize.x, (int)m_cardEdgeSize.y, CardEdgeTexture->GetColorKey(0));

		}
		if (CardNameTagTexture)
		{
			RenderLT = Pos;

			RenderLT += m_cardNameTagOffset;

			::TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
				(int)m_cardNameTagSize.x, (int)m_cardNameTagSize.y,
				CardNameTagTexture->GetDC(m_cardInfo[2]),
				0, 0, (int)m_cardNameTagSize.x, (int)m_cardNameTagSize.y,
				CardNameTagTexture->GetColorKey(0));
		}

		if (CardCostTexture) {

			RenderLT = Pos;

			RenderLT += m_costImageOffset;

			::TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
				(int)m_costImageSize.x, (int)m_costImageSize.y,
				CardCostTexture->GetDC(0),
				0, 0, (int)m_costImageSize.x, (int)m_costImageSize.y,
				CardCostTexture->GetColorKey(0));
		}
	}

	CGameObject::Render(hDC, DeltaTime);
}

void CCard::Update(float DeltaTime)
{
	//���콺 �巡��
	if (m_mouseHovered) {
		if (CInput::GetInst()->GetMouseLDown())
		{		
			if (m_cardOriginPos.x == 0.f && m_cardOriginPos.y == 0.f) 
			{
				m_cardOriginPos = GetPos();
			}
			m_clickedPos = CInput::GetInst()->GetMousePos();
		}
		
		if (CInput::GetInst()->GetMouseLPush())
		{	
			
			SetPos(CInput::GetInst()->GetMousePos() - m_Size * 0.5f);
		}

		if (CInput::GetInst()->GetMouseLUp()) //���� ��
		{			
				SetPos(m_cardOriginPos);
			
		}
		
	}
}

void CCard::SetCardInfo(string CardName, Card_Type Type, Card_Value Value, bool colorless, bool curse)
{
	//cardInfo[0] = ī�� �г�
	//cardInfo[1] = ī�� �׵θ�
	//cardInfo[2] = ī�� ������
	SetCardType(Type);
	SetCardValue(Value);
	m_colorless = colorless;
	m_curse = curse;
	m_CardImage = CardName;
	switch (Type)
	{
	case Card_Type::Attack:
		if (m_colorless)
			m_cardInfo[0] = 0;
		else
			m_cardInfo[0] = 3;

		switch (Value) {
			case Card_Value::Common:
				m_cardInfo[1] = 0;
				m_cardInfo[2] = 0;
				break;
			case Card_Value::Special:
				m_cardInfo[1] = 3;
				m_cardInfo[2] = 1;
				break;
			case Card_Value::Rare:
				m_cardInfo[1] = 6;
				m_cardInfo[2] = 2;
				break;
		}
		break;

	case Card_Type::Skill:
		if (m_curse) {
			m_cardInfo[0] = 6;
			m_cardInfo[1] = 1;
			m_cardInfo[2] = 0;
			break;
		}
		if (m_colorless)
			m_cardInfo[0] = 1;
		else
			m_cardInfo[0] = 4;

		switch (Value) {
		case Card_Value::Common:
			m_cardInfo[1] = 1;
			m_cardInfo[2] = 0;
			break;
		case Card_Value::Special:
			m_cardInfo[1] = 4;
			m_cardInfo[2] = 1;
			break;
		case Card_Value::Rare:
			m_cardInfo[1] = 7;
			m_cardInfo[2] = 2;
			break;
		}
		break;

	case Card_Type::Power:
		if (m_colorless)
			m_cardInfo[0] = 2;
		else
			m_cardInfo[0] = 5;

		switch (Value) {
		case Card_Value::Common:
			m_cardInfo[1] = 2;
			m_cardInfo[2] = 0;
			break;
		case Card_Value::Special:
			m_cardInfo[1] = 5;
			m_cardInfo[2] = 1;
			break;
		case Card_Value::Rare:
			m_cardInfo[1] = 8;
			m_cardInfo[2] = 2;
			break;
		}
		break;
	}

}

//void CCard::SetCardAttribute(const TCHAR* cardName, const TCHAR* cardType, const TCHAR* cardExplain, const TCHAR* cardCost)
//{
//	m_MycardName = CreateWidgetComponent<CText>("cardName");
//	m_MycardName->GetWidget<CText>()->SetText(cardName);
//	m_MycardName->SetPos(120, 27);
//	//m_MycardName->GetWidget<CText>()->SetTextSize(10);
//	m_MycardName->GetWidget<CText>()->EnableShadow(true);
//	m_MycardName->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
//	m_MycardName->GetWidget<CText>()->SetTextColor(255, 255, 237);
//	m_MycardName->GetWidget<CText>()->SetFont("ExplainFont");
//	
//
//	m_MycardType = CreateWidgetComponent<CText>("cardType");
//	m_MycardType->GetWidget<CText>()->SetText(cardType);
//	m_MycardType->SetPos(120, 214);
//	m_MycardType->GetWidget<CText>()->SetTextColor(94, 94, 94);
//
//	m_MycardExplain = CreateWidgetComponent<CText>("cardExplain");
//	m_MycardExplain->GetWidget<CText>()->SetText(cardExplain);
//	m_MycardExplain->SetPos(50, 300);
//	m_MycardExplain->GetWidget<CText>()->EnableShadow(true);
//	m_MycardExplain->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
//	m_MycardExplain->GetWidget<CText>()->SetTextColor(255, 249, 229);
//
//	m_MycardCost = CreateWidgetComponent<CText>("cardCost");
//	m_MycardCost->GetWidget<CText>()->SetText(cardCost);
//	m_MycardCost->SetPos(5, 0);
//	//m_MycardCost->GetWidget<CText>()->SetSize(200.f, 200.f);
//	m_MycardCost->GetWidget<CText>()->EnableShadow(true);
//	m_MycardCost->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
//	m_MycardCost->GetWidget<CText>()->SetTextColor(255, 255, 255);
//	m_MycardCost->GetWidget<CText>()->SetFont("CostFont");
//
//}

void CCard::SetCardAttribute(const TCHAR* cardName, Card_Type cardType, int cost)
{
	//ī�� �̸�
	m_MycardName = CreateWidgetComponent<CText>("cardName");
	m_MycardName->GetWidget<CText>()->SetText(cardName);
	m_MycardName->SetPos(72, 8);
	m_MycardName->GetWidget<CText>()->EnableShadow(true);
	m_MycardName->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_MycardName->GetWidget<CText>()->SetTextColor(255, 255, 237);
	m_MycardName->GetWidget<CText>()->SetFont("NameFont");


	//ī�� Ÿ��
	//m_MycardType = CreateWidgetComponent<CText>("cardType");
	char Type[5] = {};
	char Attack[5] = "����";
	char Skill[5] = "��ų";
	char Power[5] = "�Ŀ�";
	char Curse[5] = "����";
	switch (cardType)
	{
	case Card_Type::Attack:
		m_AttackCard = true;
		strcpy_s(Type, Attack);
		break;

	case Card_Type::Skill:		
		strcpy_s(Type, Skill);
		break;

	case Card_Type::Power:				
		strcpy_s(Type, Power);
		break;
	case Card_Type::Curse:		
		strcpy_s(Type, Curse);
		break;
	}
	TCHAR Change[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Type, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Type, -1, Change, Length);

	m_MycardType = CreateWidgetComponent<CText>("cardType");
	m_MycardType->GetWidget<CText>()->SetText(Change);
	m_MycardType->SetPos(74, 105);
	m_MycardType->GetWidget<CText>()->SetTextColor(64, 64, 64);
	m_MycardType->GetWidget<CText>()->SetFont("TypeFont");

	//ī�� �ڽ�Ʈ, ī�� ����
	m_MycardCost = CreateWidgetComponent<CText>("cardCost");

	m_Energy = cost;
	char Text[256] = {};
	sprintf_s(Text, "%d", m_Energy);

	TCHAR	Unicode[256] = {};
	int Length2 = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length2);

	m_MycardCost->GetWidget<CText>()->SetText(Unicode);
	m_MycardCost->SetPos(6, -10);
	//m_MycardCost->GetWidget<CText>()->SetSize(200.f, 200.f);
	m_MycardCost->GetWidget<CText>()->EnableShadow(true);
	m_MycardCost->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_MycardCost->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_MycardCost->GetWidget<CText>()->SetFont("CostFont");

	//ī�� ����
	//m_MycardExplain = CreateWidgetComponent<CText>("cardExplain");
	//SetAbility();
	////m_MycardExplain->GetWidget<CText>()->SetText(cardExplain);
	//m_MycardExplain->SetPos(0, 0);
	//m_MycardExplain->GetWidget<CText>()->EnableShadow(true);
	//m_MycardExplain->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	//m_MycardExplain->GetWidget<CText>()->SetTextColor(255, 249, 229);
	//m_MycardExplain->GetWidget<CText>()->SetFont("NameFont");

}

void CCard::SetAbility()
{
	TCHAR Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, m_CardExplain, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, m_CardExplain, -1, Unicode, Length);

	m_MycardExplain->GetWidget<CText>()->SetText(Unicode);
}

void CCard::AddAbility(CCardAbility* givedAbility)
{
	m_Abilitys.push_back(givedAbility);

	stringstream ss;
	
	ss << "cardExplain" << m_Abilitys.size();

	 CWidgetComponent* text = CreateWidgetComponent<CText>(ss.str());
	 text->SetPos(75.f, (float)(100 + m_Abilitys.size()*20));
	 text->GetWidget<CText>()->EnableShadow(true);
	 text->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	 text->GetWidget<CText>()->SetTextColor(255, 249, 229);

	 text->GetWidget<CText>()->SetText(givedAbility->GetExplain());
text->GetWidget<CText>()->SetFont("NameFont");

m_Explains.push_back(text);
}

void CCard::SetEnable(bool Enable)
{
	CRef::SetEnable(Enable);
	list<CSharedPtr<class CCardAbility>>::iterator iter = m_Abilitys.begin();
	list<CSharedPtr<class CCardAbility>>::iterator iterEnd = m_Abilitys.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetEnable(Enable);
	}
}


void CCard::useCard(CGameObject* owner, CGameObject* target)
{
	//
	//ī�� Ÿ�� �˾Ƴ���
	if (owner->GetAttackCard() && target->GetName() == "Player") {
		return;
	}
	int cost = owner->GetEnergy();
	int PlayerEnergy = m_Scene->GetPlayer()->GetEnergy();
	if (PlayerEnergy - cost < 0) {
		CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("Messages");
		Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("�������� ������."));
		return;
	}
	else {
		m_Scene->GetPlayer()->SetEnergy(PlayerEnergy - cost);
	}

	list<CSharedPtr< CCardAbility>>::iterator iter = m_Abilitys.begin();
	list<CSharedPtr< CCardAbility>>::iterator End = m_Abilitys.end();

	for (; iter != End; iter++)
	{
		(*iter)->ActivateAbility(owner, target);
	}

	owner->SetUsedCard(true);
	m_Scene->SetUseCard(true);
}

void CCard::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
	if(!(m_Scene->GetBlackSwitch()))
	{
	if (!CCardManager::GetInst()->CardCheck()) 
	{
		CCardManager::GetInst()->SetCardCheck(Src->GetOwner());
		if (!m_mouseHovered) {
			m_mouseHovered = true;
			Src->SetMouseCollision(true);
			Src->GetOwner()->SetSelectedCard(true);
			if (Src->GetOwner()->GetSelectedCard())
			{
				m_HoveredOffset = Vector2(0, -50);
				Src->GetOwner()->SetPos(GetPos() + m_HoveredOffset);
			}
		}
	}
	}
}

void CCard::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	if (m_mouseHovered)
	{
		m_mouseHovered =false;
		SetPos(GetPos() - m_HoveredOffset);
		Src->GetOwner()->SetSelectedCard(false);
		CCardManager::GetInst()->SetCardCheck(nullptr);
		CCardManager::GetInst()->HandSort();
	}		
}

void CCard::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (!(m_Scene->GetBlackSwitch()))
	{
		m_collisionInteraction = true;
	}
	
	
	//MessageBox(nullptr, TEXT("Ȯ��dddddd."), TEXT("^��^"), MB_OK);
}

void CCard::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	if (m_collisionInteraction) 
	{
		if (CInput::GetInst()->GetMouseLUp()) //���� ��
		{	
			useCard(Src->GetOwner(), Dest->GetOwner());
			//ī�� ������ ����
			m_collisionInteraction = false;
		}

	}
}
