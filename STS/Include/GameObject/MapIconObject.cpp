#include "MapIconObject.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/ImageWidget2.h"
#include "Effect.h"
#include "../Input.h"
#include "CardManager.h"

#include "TurnEffect.h"
#include "Effects/BattleStartImage.h"
#include "MyMonster.h"
#include "Monster/Slime.h"
#include "Monster/Red.h"
#include "Monster/Jaw.h"
#include "Monster/BossSlime.h"
#include "Effects/RestObject.h"


CMapIconObject::CMapIconObject()
{
	SetTypeID<CMapIconObject>();
	m_RenderLayer = ERender_Layer::MapIcon;
	m_Type = EMapIcon_Type::none;
	m_Time = 0.f;
	m_rand = 0;
	m_MouseHovered = false;
	m_isStageLevel = 0;
	m_check = false;
}

CMapIconObject::~CMapIconObject()
{

}

bool CMapIconObject::Init()
{
	CGameObject::Init();
	m_Time = 0.f;
	SetPos(640, 2300);
	SetPivot(0.5f, 0.5f);

	SetTexture("MapIcon", TEXT("Map/monster.bmp"));
	SetColorKey(255, 0, 255);
	SetSize(64.f,64.f);

	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(64.f, 64.f);
	Box->SetCollisionProfile("MapIcon");

	Box->SetMouseCollisionBeginFunction<CMapIconObject>(this, &CMapIconObject::CollisionMouseBegin);
	Box->SetMouseCollisionEndFunction<CMapIconObject>(this, &CMapIconObject::CollisionMouseEnd);


	return true;
}

void CMapIconObject::Update(float DeltaTime)
{
	//CGameObject::Update(DeltaTime);
	m_rand = rand() % 3;

	if (m_MouseHovered && m_Time == 0.f && !m_Scene->GetIsBattle())
	{
		int stage = CCardManager::GetInst()->GetStageLevel();
		// 카드매니저의 스테이지보다 1 크
		if (m_isStageLevel == stage + 1) {
			if (CInput::GetInst()->GetMouseLDown()) //마우스 클릭 시
			{
				CEffect* Effect = m_Scene->CreateObject<CEffect>("circle");

				Effect->SetRenderLayer(ERender_Layer::MapIcon);
				Effect->SetPos(m_OwnerPos);
				Effect->AddAnimation("circle", false, 0.3f);
				m_Time += 0.1f;						
			}
		}
	}
	if (m_Time>0)
	{
		m_Time += DeltaTime;
		if (m_Time >= 0.4f) {
			CWidgetComponent* circled = CreateWidgetComponent<CImageWidget2>("circled");
			circled->GetWidget<CImageWidget2>()->SetTexture("circled", TEXT("Map/cleared.bmp"));
			circled->GetWidget<CImageWidget2>()->SetSize(96, 96);
			circled->SetPos(-5, 0);
			circled->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
			
			m_Time = 0.f;
			StartEvent();
			CCardManager::GetInst()->AddStageLevel();
			//			
			//
		}		
	}
}

void CMapIconObject::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CMapIconObject::CollisionMouseBegin(CCollider* Src, const Vector2& MousePos)
{
	m_OwnerPos = Src->GetOwner()->GetPos();
	m_MouseHovered = true;

}

void CMapIconObject::CollisionMouseEnd(CCollider* Src, const Vector2& MousePos)
{
	m_MouseHovered = false;
}

void CMapIconObject::StartEvent()
{ 
	//여기서 상황에 따라 세팅됨
	switch (m_Type)
	{
	case EMapIcon_Type::monster:
		m_Scene->SetIsBattle(true);
		CreateMonsters();
		//CreateBoss();
		break;
	case EMapIcon_Type::rest:
		m_Scene->SetRestSwitch(true);
		CreateRest();		
		break;
	case EMapIcon_Type::shop:

		break;
	case EMapIcon_Type::chest:

		break;
	case EMapIcon_Type::elite:
		m_Scene->SetIsBattle(true);
		CreateElite();
		break;
	case EMapIcon_Type::boss:
		m_Scene->SetIsBattle(true);
		CreateBoss();
		break;
	}
	
	m_Scene->SetMapSwitch(false);
	m_Scene->SetStageIcon(false);
	m_Scene->GetCameraObj()->CameraReset();


	//m_Scene->GetCameraObj()->
	//MessageBox(nullptr, TEXT("확인2."), TEXT("^모^"), MB_OK);
}

void CMapIconObject::CreateMonsters()
{
	//난수로 마리수 정함
	if (rand() % 100 < 40) { //40%확률로 2마리
		
		RandMonsters(rand()%3);
		RandMonsters(rand()%3);

		int length = (int)m_Scene->GetMonsters().size();
		for (int i = 0; i < length; i++)
		{
			m_Scene->GetMonsters()[i]->SetPos(800.f+(i*(200.f)), 450.f);
		}
	}
	else {
		//RandMonsters(rand()%3);
		RandMonsters(rand()%3);
	}
	CBattleStartImage* image = m_Scene->CreateObject<CBattleStartImage>("BattleStart");
	CTurnEffect* test = m_Scene->CreateObject<CTurnEffect>("TurnBanner");
}

void CMapIconObject::CreateRest()
{
	CRestObject* RestBack = m_Scene->CreateObject<CRestObject>("RestBack");
	RestBack->SetTexture("RestBack", TEXT("Scene/rest.bmp"));
	RestBack->SetSize(1280.f, 758.f);
	RestBack->SetPos(0, 0);

	CRestObject* RestObj = m_Scene->CreateObject<CRestObject>("RestObj");
	RestObj->SetTexture("RestObj", TEXT("Scene/A.bmp"));
	RestObj->SetSize(1280.f, 329.f);
	RestObj->SetColorKey(255, 0, 255);
	RestObj->SetPos(0, 370.f);

	CRestObject* RestChar = m_Scene->CreateObject<CRestObject>("RestChar");
	RestChar->SetTexture("RestChar", TEXT("Player/shoulder2.bmp"));
	RestChar->SetSize(960.f, 568.f);
	RestChar->SetColorKey(255, 0, 255);
	RestChar->SetPos(0, 150.f);
}

void CMapIconObject::CreateShop()
{
}

void CMapIconObject::CreateChest()
{
}

void CMapIconObject::CreateElite()
{
	CRed* red = m_Scene->CreateObject<CRed>("EliteRed");
	m_Scene->AddMonsters(red);
	CBattleStartImage* image = m_Scene->CreateObject<CBattleStartImage>("BattleStart");
	CTurnEffect* test = m_Scene->CreateObject<CTurnEffect>("TurnBanner");
}

void CMapIconObject::CreateBoss()
{
	CBossSlime* King = m_Scene->CreateObject<CBossSlime>("Slime");
	//King->SetPos(800, 400);
	m_Scene->AddMonsters(King);
	CBattleStartImage* image = m_Scene->CreateObject<CBattleStartImage>("BattleStart");
	CTurnEffect* test = m_Scene->CreateObject<CTurnEffect>("TurnBanner");
}

void CMapIconObject::RandMonsters(int value)
{
	if (value == 0) //광신자
	{
		CMyMonster* Cultist = m_Scene->CreateObject<CMyMonster>("Cultist");
		m_Scene->AddMonsters(Cultist);
	}
	if (value == 1) //턱벌레
	{
		CJaw* Jaw = m_Scene->CreateObject<CJaw>("jaw");
		m_Scene->AddMonsters(Jaw);		
	}
	if (value == 2) //슬라임
	{
		CSlime* Slime = m_Scene->CreateObject<CSlime>("Slime");
		m_Scene->AddMonsters(Slime);
	}
}




