#include "BattleScene.h"
#include "../GameObject/MyPlayer.h"
#include "../GameObject/MyMonster.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/Deco.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"


#include "../Widget/WidgetComponent.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/TopPanel.h"
#include "../Widget/ImageWidget2.h"
#include "../Widget/CharacterHUD.h"

#include "../Collision/ColliderBox.h"


#include "../GameObject/Cards/GiveAttribute.h"

#include "../Widget/StartWindow.h"

#include "../GameObject/Cards/Strike.h"
#include "../GameObject/Cards/Defend.h"




CBattleScene::CBattleScene()
{
	CreateAnimationSequence();
}

CBattleScene::~CBattleScene()
{
}

bool CBattleScene::Init()
{
	
	//CreateWidgetWindow<CStartWindow>("StartWindow");

	GetCamera()->SetResolution(1280.f, 1200.f);
	GetCamera()->SetWorldResolution(1280.f, 1200.f);
	GetCamera()->SetTargetPivot(0.f, 0.f);

	CreateObject<CBackObj>("BackObj");
	
	CDeco* BackImageA = CreateObject<CDeco>("BackImageA");
	BackImageA->SetPos(0, 0);
	BackImageA->SetTexture("BackImageA", TEXT("Scene/B.bmp"));
	BackImageA->SetSize(1280, 512);
	BackImageA->SetColorKey(255, 0, 255);

	CDeco* BackImageB = CreateObject<CDeco>("BackImageB");
	BackImageB->SetPos(0, 550);
	BackImageB->SetTexture("BackImageB", TEXT("Scene/C.bmp"));
	BackImageB->SetSize(1280, 185);
	BackImageB->SetColorKey(255, 0, 255);


	CMyPlayer* Player = CreateObject<CMyPlayer>("Player");

	CMyMonster* Monster = CreateObject<CMyMonster>("Monster");

	GetSceneResource()->LoadTexture("strike", TEXT("Cards/CardImage/strike.bmp"));

	GetSceneResource()->LoadTexture("shield", TEXT("Cards/CardImage/defend.bmp"));
	//카드 키워드 생성 //////////////////////////

	CGiveAttribute* Damage = CreateObject<CGiveAttribute>("Damage");
	Damage->SetType(Card_Attribute::Damage, 10);
	CGiveAttribute* Shield = CreateObject<CGiveAttribute>("Shield");
	Shield->SetType(Card_Attribute::Shield, 10);
	CGiveAttribute* DrawCard = CreateObject<CGiveAttribute>("DrawCard");
	DrawCard->SetType(Card_Attribute::DrawCard, 0);


	///////////////////카드 생성//////////////////////////
	CCard* Card = CreateObject<CCard>("card");
	Card->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Card->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Card->SetPos(300, 570); 
	Card->AddAbility(Damage);
	//Card->AddAbility(sh);
	//Card->AddAbility(DrawCard);

	CCard* Card2 = CreateObject<CCard>("card2");
	Card2->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Card2->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Card2->SetPos(470, 570);
	Card2->AddAbility(Shield);


	CCard* Card3 = CreateObject<CCard>("card3");
	Card3->SetCardInfo("??", Card_Type::Power, Card_Value::Rare, true, false);
	Card3->SetCardAttribute(TEXT("카드"), Card_Type::Power, 3);
	Card3->SetPos(640, 570);
	Card3->AddAbility(DrawCard);


	SetPlayer(Player);
	
	CreateWidgetWindow<CTopPanel>("TopPanel");
	//
	

	return true;
}

void CBattleScene::CreateAnimationSequence()
{
}
