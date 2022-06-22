#include "Card.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Camera.h"
#include "../Resource/Texture/Texture.h"
#include "../Widget/WidgetWindow.h"
#include "../Collision/ColliderBox.h"
#include "../Input.h"

CCard::CCard()
{
	SetTypeID<CCard>();
	m_mouseHovered = false;
	m_mouseClicked = false;

}

CCard::~CCard()
{
}

bool CCard::Init()
{
	//1. 카드를 띄운다
	//-> 텍스처가 필요하다
	// -> 이미지가 여러개 필요하다
	//   ->이미지를 그리기 위해 필요한게 뭔가?
	//		->Texture의 안에있는 ImageInfo에 있는 HDC  ( hMemDC)
	//			m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_cardOriginPos = (0.f, 0.f);

	//카드 패널
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_C1.bmp"));	 //0
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_C2.bmp"));	 //1
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_C3.bmp"));	 //2
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_R1.bmp"));	 //3
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_R2.bmp"));	 //4
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_R3.bmp"));	 //5
	cardPanelFiles.push_back(TEXT("Cards/cardPanel_Curse.bmp")); //6

	m_Scene->GetSceneResource()->LoadTexture("cardPanel", cardPanelFiles);
	SetSize(295, 415);

	//카드 테두리
	//카드타입에따라 edge텍스처와 nameTag와 이미지
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_C1.bmp")); //	 0  //공격
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_C2.bmp")); //  1  //스킬  
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_C3.bmp")); //	 2  //파워
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_S1.bmp")); //	 3 
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_S2.bmp")); //	 4 
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_S3.bmp")); //	 5
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_R1.bmp")); //	 6 
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_R2.bmp")); //	 7 
	cardEdgeFiles.push_back(TEXT("Cards/cardEdge_R3.bmp")); //	 8

	//카드파츠들의 이미지를 불러와서 그릴 준비m_cardEdgeSize
	m_cardEdgeSize = Vector2(265, 235);
	m_cardEdgeOffset = Vector2(14, 5);
	m_Scene->GetSceneResource()->LoadTexture("CardEdge", cardEdgeFiles);

	//카드 네임택
	cardNameTagFiles.push_back(TEXT("Cards/cardNameTag_C.bmp")); //0 COMMON
	cardNameTagFiles.push_back(TEXT("Cards/cardNameTag_S.bmp")); //2 SPECIAL
	cardNameTagFiles.push_back(TEXT("Cards/cardNameTag_R.bmp")); //1 RARE

	m_cardNameTagSize = Vector2(322.f, 70.f);
	m_cardNameTagOffset = Vector2(-14, 25);
	m_Scene->GetSceneResource()->LoadTexture("CardNameTags", cardNameTagFiles);

	//코스트 이미지
	m_Scene->GetSceneResource()->LoadTexture("CostImage", TEXT("Cards/cardCost.bmp"));
	m_costImageSize = Vector2(67, 67);
	m_costImageOffset = Vector2(-20, -20);

	//카드 이미지
	m_Scene->GetSceneResource()->LoadTexture("CardImage", TEXT("Cards/CardImage/Strike.bmp"));
	m_cardImageSize = Vector2(246, 185);
	m_cardImageOffset = Vector2(22, 44);


	//카드세팅하는 함수
	SetCardInfo(Card_Type::Attack, Card_Value::Common, false);
	SetCardAttribute(TEXT("타아아아아아아아아앙아아아아격"), TEXT("공격"), TEXT("피해를 6 줍니다."), TEXT("3"));

	//충돌체
	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(295, 415);
	Box->SetCollisionProfile("Card");
	Box->SetOffset(m_Size*0.5f);

	Box->SetMouseCollisionBeginFunction<CCard>(this, &CCard::CollisionMouseBegin);
	Box->SetMouseCollisionEndFunction<CCard>(this, &CCard::CollisionMouseEnd);
	Box->SetCollisionBeginFunction<CCard>(this, &CCard::CollisionBegin);
	Box->SetCollisionEndFunction<CCard>(this, &CCard::CollisionEnd);

	
	return true;
}

void CCard::Render(HDC hDC, float DeltaTime)
{
	//카드 파츠들을 모아서 그려야함
	//패널 -> 엣지 -> 네임택 -> 코스트
	CTexture* CardPanelTexture = CResourceManager::GetInst()->FindTexture("cardPanel");

	CTexture* CardEdgeTexture = CResourceManager::GetInst()->FindTexture("CardEdge");

	CTexture* CardNameTagTexture= CResourceManager::GetInst()->FindTexture("CardNameTags");

	CTexture* CardCostTexture = CResourceManager::GetInst()->FindTexture("CostImage");

	CTexture* CardImageTexture = CResourceManager::GetInst()->FindTexture("CardImage");



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
			Pos = m_Pos - m_Scene->GetCamera()->GetPos() ;
		}

		RenderLT = Pos;

		//패널 그리기
		::TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
			(int)m_Size.x, (int)m_Size.y, CardPanelTexture->GetDC(m_cardInfo[0]),
			0, 0, (int)m_Size.x, (int)m_Size.y, CardPanelTexture->GetColorKey(0));

		//카드일러
		if (CardImageTexture) {
			RenderLT = Pos;

			RenderLT += m_cardImageOffset;

			::TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
				(int)m_cardImageSize.x, (int)m_cardImageSize.y, CardImageTexture->GetDC(0),
				0, 0, (int)m_cardImageSize.x, (int)m_cardImageSize.y, CardImageTexture->GetColorKey(0));
		}

		//카드 테두리
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
	//마우스 드래그

	//if (!m_mouseHovered) {
	//	m_Pos = m_cardOriginPos;
	//}
	if (m_mouseHovered) {
		
		if (CInput::GetInst()->GetMouseLDown())
		{
			if (m_cardOriginPos.x == 0.f && m_cardOriginPos.y == 0.f) {
				m_cardOriginPos = GetPos();
			}
			m_clickedPos = CInput::GetInst()->GetMousePos();
		}
		
		if (CInput::GetInst()->GetMouseLPush())
		{

			
			SetPos(CInput::GetInst()->GetMousePos() - m_Size * 0.5f);
		}

		if (CInput::GetInst()->GetMouseLUp()) //뗐을 때
		{
				SetPos(m_cardOriginPos);
			
		}
		
	}
}

void CCard::SetCardInfo(Card_Type Type, Card_Value Value, bool colorless, bool curse)
{
	//cardInfo[0] = 카드 패널
	//cardInfo[1] = 카드 테두리
	//cardInfo[2] = 카드 네임택
	SetCardType(Type);
	SetCardValue(Value);
	m_colorless = colorless;
	m_curse = curse;

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

void CCard::SetCardAttribute(const TCHAR* cardName, const TCHAR* cardType, const TCHAR* cardExplain, const TCHAR* cardCost)
{
	//CSharedPtr<class CText> m_MycardName;
	//CSharedPtr<class CText> m_MycardType;
	//CSharedPtr<class CText> m_MycardExplain;

	m_MycardName = CreateWidgetComponent<CText>("cardName");
	m_MycardName->GetWidget<CText>()->SetText(cardName);
	m_MycardName->SetPos(120, 27);
	//m_MycardName->GetWidget<CText>()->SetTextSize(10);
	m_MycardName->GetWidget<CText>()->EnableShadow(true);
	m_MycardName->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_MycardName->GetWidget<CText>()->SetTextColor(255, 255, 237);
	m_MycardName->GetWidget<CText>()->SetFont("ExplainFont");
	

	m_MycardType = CreateWidgetComponent<CText>("cardType");
	m_MycardType->GetWidget<CText>()->SetText(cardType);
	m_MycardType->SetPos(120, 214);
	m_MycardType->GetWidget<CText>()->SetTextColor(94, 94, 94);

	m_MycardExplain = CreateWidgetComponent<CText>("cardExplain");
	m_MycardExplain->GetWidget<CText>()->SetText(cardExplain);
	m_MycardExplain->SetPos(50, 300);
	m_MycardExplain->GetWidget<CText>()->EnableShadow(true);
	m_MycardExplain->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_MycardExplain->GetWidget<CText>()->SetTextColor(255, 249, 229);

	m_MycardCost = CreateWidgetComponent<CText>("cardCost");
	m_MycardCost->GetWidget<CText>()->SetText(cardCost);
	m_MycardCost->SetPos(5, 0);
	//m_MycardCost->GetWidget<CText>()->SetSize(200.f, 200.f);
	m_MycardCost->GetWidget<CText>()->EnableShadow(true);
	m_MycardCost->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
	m_MycardCost->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_MycardCost->GetWidget<CText>()->SetFont("CostFont");

}

void CCard::useCard()
{
	//Card능력을 발동하면된다
	//if(m_Ability)
	//	m_Ability->Activate();

}

void CCard::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
	m_mouseHovered = true;
	m_HoveredOffset = Vector2(0, -50);

	SetPos(GetPos() + m_HoveredOffset);
}

void CCard::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	m_mouseHovered = false;


	SetPos(GetPos() - m_HoveredOffset);


}

void CCard::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	m_collisionInteraction = true;
	//MessageBox(nullptr, TEXT("확인dddddd."), TEXT("^모^"), MB_OK);
}

void CCard::CollisionEnd(CCollider* Src, CCollider* Dest)
{

	if (m_collisionInteraction) 
	{
		if (CInput::GetInst()->GetMouseLUp()) //뗐을 때
		{
			Dest->GetOwner()->InflictDamage(30.f);
			m_collisionInteraction = false;
		}

	}
}
