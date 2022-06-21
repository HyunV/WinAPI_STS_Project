#include "BattleScene.h"
#include "../GameObject/MyPlayer.h"
#include "../GameObject/MyMonster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/TopPanel.h"
#include "../GameObject/Cards/Strike.h"

#include "../Widget/CharacterHUD.h"

CBattleScene::CBattleScene()
{
	CreateAnimationSequence();
}

CBattleScene::~CBattleScene()
{
}

bool CBattleScene::Init()
{
	GetCamera()->SetResolution(1920.f, 1200.f);
	GetCamera()->SetWorldResolution(1920.f, 1200.f);
	GetCamera()->SetTargetPivot(0.f, 0.f);

	CreateObject<CBackObj>("BackObj");
	CMyPlayer* Player = CreateObject<CMyPlayer>("Player");

	CMyMonster* Monster = CreateObject<CMyMonster>("Monster");

	CStrike* Strike = CreateObject<CStrike>("CStrike");
	CCard* Card = CreateObject<CCard>("card");
	Card->SetPos(200, 300);


	//CCard* StrikeCard = CreateObject<CCard>("StrikeCard");
	//StrikeCard->SetPos(122, 100);
	//StrikeCard->SetImage(3);

	//CCard* Strik2eCard = CreateObject<CCard>("Strike2Card");
	//Strik2eCard->SetPos(100, 100);
	//Strik2eCard->SetImage(4);


	SetPlayer(Player);

	//
	CreateWidgetWindow<CTopPanel>("TopPanel");
	return true;
}

void CBattleScene::CreateAnimationSequence()
{
}
