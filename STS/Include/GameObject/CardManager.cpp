#include "CardManager.h"
#include "Card.h"
#include "Cards/CardAbility.h"
#include "Cards/GiveAttribute.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneResource.h"
#include "GameObject.h"
#include "BubbleMessage.h"
#include <time.h>

DEFINITION_SINGLE(CCardManager);

CCardManager::CCardManager()
{
	m_CardCheck = nullptr;
	m_MouseClicked = false;
	m_MouseHovered = false;
	m_MonstersTurn = false;
	m_PlayerTurn = false;
	m_TurnCount = 1;
	m_UsedCard = false;
	m_Scene = nullptr;
	m_DrawCard = 5;
	m_AtkCount = 0;
	m_StageLevel = 0;
	m_Temp = 0;
	//srand((unsigned int)time(0));
}

CCardManager::~CCardManager()
{
}

void CCardManager::InitMyDeck()
{

	//카드 능력치 세팅

	//공격 
	CGiveAttribute* StrikeDamage = m_Scene->CreateObject<CGiveAttribute>("StrikeDamage");
	StrikeDamage->SetType(Card_Attribute::Damage, 6);

	//강타딜
	CGiveAttribute* BashDamage = m_Scene->CreateObject<CGiveAttribute>("BashDamage");
	BashDamage->SetType(Card_Attribute::Damage, 8);

	//몽둥이질 
	CGiveAttribute* bludgeonDamage = m_Scene->CreateObject<CGiveAttribute>("bludgeonDamage");
	bludgeonDamage->SetType(Card_Attribute::Damage, 32);

	//클로스라인
	CGiveAttribute* clotheslineDamage = m_Scene->CreateObject<CGiveAttribute>("bludgeonDamage");
	clotheslineDamage->SetType(Card_Attribute::Damage, 12);

	//흡혈
	CGiveAttribute* BiteDamage = m_Scene->CreateObject<CGiveAttribute>("BiteDamage");
	BiteDamage->SetType(Card_Attribute::Damage, 7);

	//섬광
	CGiveAttribute* FlashDamage = m_Scene->CreateObject<CGiveAttribute>("FlashDamage");
	FlashDamage->SetType(Card_Attribute::Damage, 3);

	//혈류
	CGiveAttribute* BloodDamage = m_Scene->CreateObject<CGiveAttribute>("BloodDamage");
	BloodDamage->SetType(Card_Attribute::Damage, 15);

	//철의파동
	CGiveAttribute* ironDamage = m_Scene->CreateObject<CGiveAttribute>("ironDamage");
	ironDamage->SetType(Card_Attribute::Damage, 5);

	//폼멜타격
	CGiveAttribute* PommelDamage = m_Scene->CreateObject<CGiveAttribute>("PommelDamage");
	PommelDamage->SetType(Card_Attribute::Damage, 9);

	CGiveAttribute* UpperDamage = m_Scene->CreateObject<CGiveAttribute>("UpperDamage");
	UpperDamage->SetType(Card_Attribute::Damage, 13);

	CGiveAttribute* HyperDamage = m_Scene->CreateObject<CGiveAttribute>("HyperDamage");
	HyperDamage->SetType(Card_Attribute::Damage, 99999);

	//수비
	CGiveAttribute* Shield5 = m_Scene->CreateObject<CGiveAttribute>("Shield");
	Shield5->SetType(Card_Attribute::Shield, 5);

	CGiveAttribute* Shield2 = m_Scene->CreateObject<CGiveAttribute>("Shield2");
	Shield2->SetType(Card_Attribute::Shield, 2);

	CGiveAttribute* Shield8 = m_Scene->CreateObject<CGiveAttribute>("Shield8");
	Shield8->SetType(Card_Attribute::Shield, 8);

	CGiveAttribute* Shield30 = m_Scene->CreateObject<CGiveAttribute>("Shield30");
	Shield30->SetType(Card_Attribute::Shield, 30);
	
	//드로우카드
	CGiveAttribute* DrawCard1 = m_Scene->CreateObject<CGiveAttribute>("DrawCard1");
	DrawCard1->SetType(Card_Attribute::DrawCard, 1);

	CGiveAttribute* DrawCard2 = m_Scene->CreateObject<CGiveAttribute>("DrawCard2");
	DrawCard2->SetType(Card_Attribute::DrawCard, 2);

	CGiveAttribute* DrawCard4 = m_Scene->CreateObject<CGiveAttribute>("DrawCard4");
	DrawCard4->SetType(Card_Attribute::DrawCard, 4);

	CGiveAttribute* DrawCard5 = m_Scene->CreateObject<CGiveAttribute>("DrawCard5");
	DrawCard5->SetType(Card_Attribute::DrawCard, 5);

	//소멸
	CGiveAttribute* Exhaust = m_Scene->CreateObject<CGiveAttribute>("Exhaust");
	Exhaust->SetType(Card_Attribute::Exhaust, 0);

	//취약
	CGiveAttribute* Vulnerable2 = m_Scene->CreateObject<CGiveAttribute>("Vulnerable");
	Vulnerable2->SetType(Card_Attribute::Vulnerable, 2);

	//약화
	CGiveAttribute* Weak2 = m_Scene->CreateObject<CGiveAttribute>("Vulnerable");
	Weak2->SetType(Card_Attribute::Weak, 2);

	//공격력
	CGiveAttribute* Inflame2 = m_Scene->CreateObject<CGiveAttribute>("Inflame2");
	Inflame2->SetType(Card_Attribute::Inflame, 2);

	CGiveAttribute* Inflame3 = m_Scene->CreateObject<CGiveAttribute>("Inflame3");
	Inflame3->SetType(Card_Attribute::Inflame, 3);

	//민첩함
	CGiveAttribute* FootWork2 = m_Scene->CreateObject<CGiveAttribute>("FootWork2");
	FootWork2->SetType(Card_Attribute::FootWork, 2);

	CGiveAttribute* FootWork3 = m_Scene->CreateObject<CGiveAttribute>("FootWork3");
	FootWork3->SetType(Card_Attribute::FootWork, 3);

	//바리케이드
	CGiveAttribute* BarricadeAtt = m_Scene->CreateObject<CGiveAttribute>("BarricadeAtt");
	BarricadeAtt->SetType(Card_Attribute::Barricade, 1);

	//한계돌파
	CGiveAttribute* LimitBreakAtt = m_Scene->CreateObject<CGiveAttribute>("LimitBreakAtt");
	LimitBreakAtt->SetType(Card_Attribute::LimitBreak, 0);

	//악마의형상
	CGiveAttribute* DemonAtt = m_Scene->CreateObject<CGiveAttribute>("DemonAtt");
	DemonAtt->SetType(Card_Attribute::DemonForm, 3);
	CGiveAttribute* DemonAtt2 = m_Scene->CreateObject<CGiveAttribute>("DemonAtt");
	DemonAtt2->SetType(Card_Attribute::DemonForm, 2);

	//몸통박치기
	CGiveAttribute* BodySlamAtt = m_Scene->CreateObject<CGiveAttribute>("BodySlamAtt");
	BodySlamAtt->SetType(Card_Attribute::BodySlam, 0);

	//참호
	CGiveAttribute* EntrenchAtt = m_Scene->CreateObject<CGiveAttribute>("EntrenchAtt");
	EntrenchAtt->SetType(Card_Attribute::Entrench, 0);

	//내 턴 시작 시
	CGiveAttribute* Text1 = m_Scene->CreateObject<CGiveAttribute>("Text1");
	Text1->SetType(Card_Attribute::Text1, 0);

	//체력 
	CGiveAttribute* HPPlus4 = m_Scene->CreateObject<CGiveAttribute>("HPPlus4");
	HPPlus4->SetType(Card_Attribute::PlusHP, 4);

	CGiveAttribute* HPPlus2 = m_Scene->CreateObject<CGiveAttribute>("HPPlus2");
	HPPlus2->SetType(Card_Attribute::PlusHP, 2);

	CGiveAttribute* HPLose2 = m_Scene->CreateObject<CGiveAttribute>("HPLose2");
	HPLose2->SetType(Card_Attribute::LoseHP, 2);

	CGiveAttribute* HPLose6 = m_Scene->CreateObject<CGiveAttribute>("HPLose6");
	HPLose6->SetType(Card_Attribute::LoseHP, 6);

	CGiveAttribute* AddEnergy2 = m_Scene->CreateObject<CGiveAttribute>("AddEnergy2");
	AddEnergy2->SetType(Card_Attribute::GetEnergy, 2);

	//##############################################메인덱 카드 세팅###################################################################################
	CCard* Strike1 = m_Scene->CreateObject<CCard>("Strike1");
	Strike1->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike1->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike1->AddAbility(StrikeDamage);

	CCard* Strike2 = m_Scene->CreateObject<CCard>("Strike2");
	Strike2->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike2->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike2->AddAbility(StrikeDamage);

	CCard* Strike3 = m_Scene->CreateObject<CCard>("Strike3");
	Strike3->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike3->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike3->AddAbility(StrikeDamage);

	CCard* Strike4 = m_Scene->CreateObject<CCard>("Strike4");
	Strike4->SetCardInfo("strike", Card_Type::Attack, Card_Value::Common, false, false);
	Strike4->SetCardAttribute(TEXT("타격"), Card_Type::Attack, 1);
	Strike4->AddAbility(StrikeDamage);

	CCard* Strike5 = m_Scene->CreateObject<CCard>("Strike5");
	Strike5->SetCardInfo("strike", Card_Type::Attack, Card_Value::Rare, true, true);
	Strike5->SetCardAttribute(TEXT("전설의 타격"), Card_Type::Attack, 0);
	Strike5->AddAbility(HyperDamage);


	//수비
	CCard* Defend1 = m_Scene->CreateObject<CCard>("Defend1");
	Defend1->SetCardInfo("shield", Card_Type::Power, Card_Value::Common, false, false);
	Defend1->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend1->AddAbility(Shield5);

	CCard* Defend2 = m_Scene->CreateObject<CCard>("Defend2");
	Defend2->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend2->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend2->AddAbility(Shield5);

	CCard* Defend3 = m_Scene->CreateObject<CCard>("Defend3");
	Defend3->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend3->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend3->AddAbility(Shield5);

	CCard* Defend4 = m_Scene->CreateObject<CCard>("Defend4");
	Defend4->SetCardInfo("shield", Card_Type::Skill, Card_Value::Common, false, false);
	Defend4->SetCardAttribute(TEXT("수비"), Card_Type::Skill, 1);
	Defend4->AddAbility(Shield5);

	//강타
	CCard* Bash = m_Scene->CreateObject<CCard>("Bash");
	Bash->SetCardInfo("Bash", Card_Type::Attack, Card_Value::Common, false, false);
	Bash->SetCardAttribute(TEXT("강타"), Card_Type::Attack, 2);
	Bash->AddAbility(BashDamage);
	Bash->AddAbility(Vulnerable2);
	//기본카드 끝
	// ###############################################################################
	// 
	//발화
	CCard* Inflame = m_Scene->CreateObject<CCard>("Inflame1");
	Inflame->SetCardInfo("Inflame", Card_Type::Power, Card_Value::Special, false, false);
	Inflame->SetCardAttribute(TEXT("발화"), Card_Type::Power, 1);
	Inflame->AddAbility(Inflame2);
	Inflame->SetIsExtinctCard(true);

	CCard* InflameCard2 = m_Scene->CreateObject<CCard>("InflameCard2");
	InflameCard2->SetCardInfo("Inflame", Card_Type::Power, Card_Value::Special, false, false);
	InflameCard2->SetCardAttribute(TEXT("발화+"), Card_Type::Power, 1);
	InflameCard2->AddAbility(Inflame3);
	InflameCard2->SetIsExtinctCard(true);

	//바리케이드
	CCard* Barricade = m_Scene->CreateObject<CCard>("Barricade1");
	Barricade->SetCardInfo("Barricades", Card_Type::Power, Card_Value::Rare, false, false);
	Barricade->SetCardAttribute(TEXT("바리케이드"), Card_Type::Power, 3);
	Barricade->AddAbility(Text1);
	Barricade->AddAbility(BarricadeAtt);
	Barricade->SetIsExtinctCard(true);

	//한계돌파
	CCard* LimitBreak = m_Scene->CreateObject<CCard>("LimitBreak1");
	LimitBreak->SetCardInfo("LimitBreak", Card_Type::Skill, Card_Value::Rare, false, false);
	LimitBreak->SetCardAttribute(TEXT("한계돌파"), Card_Type::Skill, 1);
	LimitBreak->AddAbility(LimitBreakAtt);
	LimitBreak->AddAbility(Exhaust);
	LimitBreak->SetIsExtinctCard(true);

	CCard* LimitBreak2 = m_Scene->CreateObject<CCard>("LimitBreak2");
	LimitBreak2->SetCardInfo("LimitBreak", Card_Type::Skill, Card_Value::Rare, false, false);
	LimitBreak2->SetCardAttribute(TEXT("한계돌파+"), Card_Type::Skill, 1);
	LimitBreak2->AddAbility(LimitBreakAtt);
	LimitBreak2->SetIsExtinctCard(true);

	//악마의형상
	CCard* DemonForm2 = m_Scene->CreateObject<CCard>("DemonForm2");
	DemonForm2->SetCardInfo("DemonForms", Card_Type::Power, Card_Value::Rare, false, false);
	DemonForm2->SetCardAttribute(TEXT("악마의 형상+"), Card_Type::Power, 3);
	DemonForm2->AddAbility(Text1);
	DemonForm2->AddAbility(DemonAtt);
	DemonForm2->SetIsExtinctCard(true);

	CCard* DemonForm = m_Scene->CreateObject<CCard>("DemonForm1");
	DemonForm->SetCardInfo("DemonForms", Card_Type::Power, Card_Value::Rare, false, false);
	DemonForm->SetCardAttribute(TEXT("악마의 형상"), Card_Type::Power, 3);
	DemonForm->AddAbility(Text1);
	DemonForm->AddAbility(DemonAtt2);
	DemonForm->SetIsExtinctCard(true);

	//몸통박치기
	CCard* BodySlam = m_Scene->CreateObject<CCard>("BodySlam1");
	BodySlam->SetCardInfo("BodySlam", Card_Type::Attack, Card_Value::Common, false, false);
	BodySlam->SetCardAttribute(TEXT("몸통박치기"), Card_Type::Attack, 0);
	BodySlam->AddAbility(BodySlamAtt);
	
	//참호
	CCard* Entrench = m_Scene->CreateObject<CCard>("Entrench1");
	Entrench->SetCardInfo("Entrench", Card_Type::Skill, Card_Value::Special, false, false);
	Entrench->SetCardAttribute(TEXT("참호"), Card_Type::Skill, 1);
	Entrench->AddAbility(EntrenchAtt);
	
	//발놀림
	CCard* FootWork = m_Scene->CreateObject<CCard>("FootWork1");
	FootWork->SetCardInfo("FootWorks", Card_Type::Power, Card_Value::Special, true, false);
	FootWork->SetCardAttribute(TEXT("발놀림"), Card_Type::Power, 1);
	FootWork->AddAbility(FootWork2);
	FootWork->SetIsExtinctCard(true);

	CCard* FootWorkPlus = m_Scene->CreateObject<CCard>("FootWorkPlus");
	FootWorkPlus->SetCardInfo("FootWorks", Card_Type::Power, Card_Value::Special, true, false);
	FootWorkPlus->SetCardAttribute(TEXT("발놀림+"), Card_Type::Power, 1);
	FootWorkPlus->AddAbility(FootWork3);
	FootWorkPlus->SetIsExtinctCard(true);

	CCard* bandageup = m_Scene->CreateObject<CCard>("bandageup");
	bandageup->SetCardInfo("bandageup", Card_Type::Skill, Card_Value::Special, true, false);
	bandageup->SetCardAttribute(TEXT("붕대감기"), Card_Type::Skill, 0);
	bandageup->AddAbility(HPPlus4);
	bandageup->AddAbility(Exhaust);
	bandageup->SetIsExtinctCard(true);

	

	CCard* bite = m_Scene->CreateObject<CCard>("bite");
	bite->SetCardInfo("bite", Card_Type::Attack, Card_Value::Common, true, false);
	bite->SetCardAttribute(TEXT("흡혈"), Card_Type::Attack, 1);
	bite->AddAbility(BiteDamage);
	bite->AddAbility(HPPlus2);

	

	CCard* bloodletting = m_Scene->CreateObject<CCard>("bloodletting");
	bloodletting->SetCardInfo("bloodletting", Card_Type::Skill, Card_Value::Special, false, false);
	bloodletting->SetCardAttribute(TEXT("사혈"), Card_Type::Skill, 0);
	bloodletting->AddAbility(HPLose2);
	bloodletting->AddAbility(AddEnergy2);
	
	

	//몽둥이질 
	CCard* bludgeon = m_Scene->CreateObject<CCard>("bludgeon");
	bludgeon->SetCardInfo("bludgeon", Card_Type::Attack, Card_Value::Rare, false, false);
	bludgeon->SetCardAttribute(TEXT("몽둥이질"), Card_Type::Attack, 3);
	bludgeon->AddAbility(bludgeonDamage);

	

	
	CCard* clothesline = m_Scene->CreateObject<CCard>("clothesline");
	clothesline->SetCardInfo("clothesline", Card_Type::Attack, Card_Value::Common, false, false);
	clothesline->SetCardAttribute(TEXT("클로스라인"), Card_Type::Attack, 2);
	clothesline->AddAbility(clotheslineDamage);
	clothesline->AddAbility(Weak2);

	

	CCard* finesse = m_Scene->CreateObject<CCard>("finesse");
	finesse->SetCardInfo("finesse", Card_Type::Skill, Card_Value::Special, true, false);
	finesse->SetCardAttribute(TEXT("능숙"), Card_Type::Skill, 0);
	finesse->AddAbility(Shield2);
	finesse->AddAbility(DrawCard2);

	

	CCard* flashOfSteel = m_Scene->CreateObject<CCard>("flashOfSteel");
	flashOfSteel->SetCardInfo("flashOfSteel", Card_Type::Attack, Card_Value::Special, true, false);
	flashOfSteel->SetCardAttribute(TEXT("강철의 섬광"), Card_Type::Attack, 0);
	flashOfSteel->AddAbility(FlashDamage);
	flashOfSteel->AddAbility(DrawCard1);

	

	//직감
	CCard* good_instincts = m_Scene->CreateObject<CCard>("good_instincts");
	good_instincts->SetCardInfo("good_instincts", Card_Type::Skill, Card_Value::Special, true, false);
	good_instincts->SetCardAttribute(TEXT("직감"), Card_Type::Skill, 0);
	good_instincts->AddAbility(Shield5);

	

	//혈류
	CCard* hemokinesis = m_Scene->CreateObject<CCard>("hemokinesis");
	hemokinesis->SetCardInfo("hemokinesis", Card_Type::Attack, Card_Value::Special, false, false);
	hemokinesis->SetCardAttribute(TEXT("혈류"), Card_Type::Attack, 1);
	hemokinesis->AddAbility(HPLose2);
	hemokinesis->AddAbility(BloodDamage);

	

	//무적
	CCard* impervious = m_Scene->CreateObject<CCard>("impervious");
	impervious->SetCardInfo("impervious", Card_Type::Skill, Card_Value::Rare, false, false);
	impervious->SetCardAttribute(TEXT("무적"), Card_Type::Skill, 2);
	impervious->AddAbility(Shield30);
	impervious->AddAbility(Exhaust);
	impervious->SetIsExtinctCard(true);

	

	CCard* iron_wave = m_Scene->CreateObject<CCard>("iron_wave");
	iron_wave->SetCardInfo("iron_wave", Card_Type::Attack, Card_Value::Common, false, false);
	iron_wave->SetCardAttribute(TEXT("철의파동"), Card_Type::Attack, 1);
	iron_wave->AddAbility(ironDamage);
	iron_wave->AddAbility(Shield5);
	
	


	CCard* JAX = m_Scene->CreateObject<CCard>("JAX");
	JAX->SetCardInfo("JAX", Card_Type::Skill, Card_Value::Common, true, false);
	JAX->SetCardAttribute(TEXT("J.A,X"), Card_Type::Skill, 0);
	JAX->AddAbility(HPLose2);
	JAX->AddAbility(Inflame3);

	

	//전략의 천재
	CCard* master_of_strategy = m_Scene->CreateObject<CCard>("master_of_strategy");
	master_of_strategy->SetCardInfo("master_of_strategy", Card_Type::Skill, Card_Value::Rare, true, false);
	master_of_strategy->SetCardAttribute(TEXT("전략의 천재"), Card_Type::Skill, 0);
	master_of_strategy->AddAbility(DrawCard4);
	master_of_strategy->AddAbility(Exhaust);
	master_of_strategy->SetIsExtinctCard(true);

	

	//제물
	CCard* offering = m_Scene->CreateObject<CCard>("offering");
	offering->SetCardInfo("offering", Card_Type::Skill, Card_Value::Rare, false, false);
	offering->SetCardAttribute(TEXT("제물"), Card_Type::Skill, 0);
	offering->AddAbility(HPLose6);
	offering->AddAbility(DrawCard5);
	offering->AddAbility(AddEnergy2);
	offering->AddAbility(Exhaust);
	offering->SetIsExtinctCard(true);

	

	CCard* pommel_strike = m_Scene->CreateObject<CCard>("pommel_strike");
	pommel_strike->SetCardInfo("pommel_strike", Card_Type::Attack, Card_Value::Common, false, false);
	pommel_strike->SetCardAttribute(TEXT("폼멜 타격"), Card_Type::Attack, 1);
	pommel_strike->AddAbility(PommelDamage);
	pommel_strike->AddAbility(DrawCard2);

	

	CCard* seeing_red = m_Scene->CreateObject<CCard>("seeing_red");
	seeing_red->SetCardInfo("seeing_red", Card_Type::Skill, Card_Value::Special, false, false);
	seeing_red->SetCardAttribute(TEXT("혈안"), Card_Type::Skill, 0);
	seeing_red->AddAbility(AddEnergy2);
	seeing_red->AddAbility(Exhaust);
	seeing_red->SetIsExtinctCard(true);

	

	CCard* shrug_it_off = m_Scene->CreateObject<CCard>("shrug_it_off");
	shrug_it_off->SetCardInfo("shrug_it_off", Card_Type::Skill, Card_Value::Common, false, false);
	shrug_it_off->SetCardAttribute(TEXT("흘려보내기"), Card_Type::Skill, 1);
	shrug_it_off->AddAbility(Shield8);
	shrug_it_off->AddAbility(DrawCard1);

	

	CCard* swift_strike = m_Scene->CreateObject<CCard>("swift_strike");
	swift_strike->SetCardInfo("swift_strike", Card_Type::Attack, Card_Value::Special, true, false);
	swift_strike->SetCardAttribute(TEXT("날렵한 타격"), Card_Type::Attack, 0);
	swift_strike->AddAbility(StrikeDamage);
	
	

	CCard* uppercut = m_Scene->CreateObject<CCard>("uppercut");
	uppercut->SetCardInfo("uppercut", Card_Type::Attack, Card_Value::Special, false, false);
	uppercut->SetCardAttribute(TEXT("어퍼컷"), Card_Type::Attack, 2);
	uppercut->AddAbility(UpperDamage);
	uppercut->AddAbility(Weak2);
	uppercut->AddAbility(Vulnerable2);

	


	//만든 카드 삽입
	//m_mainDeck.push_back(Strike1);
	//m_mainDeck.push_back(Strike2);
	//m_mainDeck.push_back(Strike3);
	//m_mainDeck.push_back(Strike4);
	//m_mainDeck.push_back(Strike5);

	//m_mainDeck.push_back(Defend1);
	//m_mainDeck.push_back(Defend2);
	//m_mainDeck.push_back(Defend3);
	//m_mainDeck.push_back(Defend4);
	//m_mainDeck.push_back(Bash);
	//테스트 추가


	m_allCard.push_back(Strike1);
	m_allCard.push_back(Strike2);
	m_allCard.push_back(Strike3);
	m_allCard.push_back(Strike4);
	//m_allCard.push_back(Strike5); //사기
	m_allCard.push_back(Defend1);
	m_allCard.push_back(Defend2);
	m_allCard.push_back(Defend3);
	m_allCard.push_back(Defend4);
	m_allCard.push_back(Bash);
	 
	m_allCard.push_back(InflameCard2);
	m_allCard.push_back(Inflame);
	m_allCard.push_back(Barricade);
	m_allCard.push_back(LimitBreak);
	m_allCard.push_back(LimitBreak2);
	m_allCard.push_back(DemonForm);
	m_allCard.push_back(DemonForm2);
	m_allCard.push_back(BodySlam);
	m_allCard.push_back(Entrench);
	m_allCard.push_back(FootWork);
	m_allCard.push_back(FootWorkPlus);
	m_allCard.push_back(bandageup);
	m_allCard.push_back(bite);
	m_allCard.push_back(bloodletting);
	m_allCard.push_back(bludgeon);
	m_allCard.push_back(clothesline);
	m_allCard.push_back(finesse);
	m_allCard.push_back(flashOfSteel);
	m_allCard.push_back(good_instincts);
	m_allCard.push_back(hemokinesis);
	m_allCard.push_back(impervious);
	m_allCard.push_back(iron_wave);
	m_allCard.push_back(JAX);
	m_allCard.push_back(master_of_strategy);
	m_allCard.push_back(offering);
	m_allCard.push_back(pommel_strike);
	m_allCard.push_back(seeing_red);
	m_allCard.push_back(shrug_it_off);
	m_allCard.push_back(swift_strike);
	m_allCard.push_back(uppercut);
}

bool CCardManager::Init()
{
	m_PlayerTurn = false;
	m_MonstersTurn = false;
	m_TurnCount = 1;
	return true;
}

void CCardManager::EnableHand(bool Enable)
{
	for (int i = 0; i < m_Hand.size(); i++)
	{
		m_Hand[i]->SetEnable(Enable);
	}
}
void CCardManager::HandSort()
{
	vector<CCard*> SortHand;
	for (int i = 0; i < m_Hand.size(); i++) 
		//핸드창에 nullptr이 아닌애들만 임시 핸드에 담아준다.
	{
		if (m_Hand[i] != nullptr) {
			SortHand.push_back(m_Hand[i]);
		}
	}
	m_Hand = SortHand;

	//(처음위치 + (거리 * i), 600);
	for (int i = 0; i < m_Hand.size(); i++) //임시로 담은 애들을 재정렬한다.
	{
		m_Hand[i]->SetEnable(true);
		//m_Hand[i]->SetCardControl(true);
		m_Hand[i]->SetPos((float)(550-(40*(m_Hand.size()))) + (80* i), 600);
	}

	//케이스문으로 장수를 따져서 정렬하게 하자
}
void CCardManager::CardView(vector<CCard*> deck)
{
	if (!m_Hand.size() == 0) {
		EnableHand(false);
	}	
	int x = -1;
	int y = 0;
	for (int i = 0; i < deck.size(); i++)
	{
		if (i % 5 == 0) {
			x++;
			y = 0;
		}	
		deck[i]->SetEnable(true);
		deck[i]->SetPos((float)180+(y*200), (float)100+(300*x));
		y++;
	}	
}
void CCardManager::ClearCard(vector<CCard*> deck)
{
	for (int i = 0; i < deck.size(); i++)
	{	
		deck[i]->SetEnable(true);
		deck[i]->SetPos(-1000.f, 0.f);		
	}
	HandSort();
}
void CCardManager::HandToDiscard()
{
	if (!m_Hand.size() == 0) {
		EnableHand(false);
	}
	//역순으로 버리게 
	for (int i = 0; i < m_Hand.size(); i++)
	{
		if (m_Hand[i] == nullptr) {
			continue;
		}
		m_Hand[i]->SetPos(0, 0);
		m_Hand[i]->SetUsedCard(false);
		m_Hand[i]->SetEnable(false);
		m_disCardDummy.push_back(m_Hand[i]);
		m_Hand[i] = nullptr;
	}
	m_Hand.clear();
	int a = (int)m_Hand.size();
}
void CCardManager::RemoveHand()
{
	for (int i = 0; i < m_Hand.size(); i++)
	{
		if (m_Hand[i]->GetUsedCard()) 
		{
			m_Hand[i]->SetUsedCard(false);
			m_Hand[i]->SetEnable(false);
			m_Hand[i]->SetPos(0, 0);
			m_Hand[i] = nullptr;
		}
	}
	HandSort();
}
void CCardManager::RemoveHandAll()
{

	for (int i = 0; i < m_Hand.size(); i++) 
	{
		m_Hand[i]->SetUsedCard(false);
		m_Hand[i]->SetEnable(false);
		m_Hand[i]->SetPos(0, 0);
		m_Hand[i] = nullptr;	
	}
	vector<CCard*> v;
	m_Hand  = v;
	HandSort();

	for (int i = 0; i < m_mainDeck.size(); i++)
	{
		m_mainDeck[i]->SetUsedCard(false);	
		m_mainDeck[i]->SetPos(0, 0);
		m_mainDeck[i]->SetEnable(false);
	}
}
void CCardManager::SetRandomDeck(int value)
{
	int n = (int)m_allCard.size();
	vector<CCard*> Temp = m_allCard;
	std::random_shuffle(Temp.begin(), Temp.end());

	for (int i = 0; i < value; i++) 
	{
		m_mainDeck.push_back(Temp.back());
		Temp.pop_back();
	}
}
int CCardManager::Rand(int End)
{
	//Start 부터 End까지의 범위 rand() % End + Start
	//0부터 End까지 범위
	//rand
	//srand(((unsigned int)time(0)));
	return rand()%End;
}

int CCardManager::RangeRand(int Min, int Max)
{
	//srand(((unsigned int)time(0)));
	return rand()%(Max-Min+1)+Min;
}

bool CCardManager::PercentRand(int Percent)
{
	if (rand() % 100 < Percent) //난수 값이 n퍼센트보다 작게 나오면 확률 적용
		return true;
	else
	return false;
}

void CCardManager::SetPlayerTurn(bool Enable)
{
		m_PlayerTurn = Enable;
}


void CCardManager::SetBringDeck()
{
	m_bringCardDummy = GetMainDeck();
}

void CCardManager::DrawCard(int value)
{
	HandSort();
	for (int i = 0; i < value; i++) {
		
		//핸드가 10장 이상일 때
		if (m_Hand.size() >= 10) {
			CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("Messages");
			Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("손이 가득 찼다."));
			return;
		}
	
		//뽑을카드가 없을 때
		if (m_bringCardDummy.size() == 0) { 
			if (m_disCardDummy.size() == 0) {
				CBubbleMessage* Message = m_Scene->CreateObject<CBubbleMessage>("Messages");
				Message->GetMessages()->GetWidget<CText>()->SetText(TEXT("가져올 카드가 없다."));
				HandSort();
				return;
			}
			m_bringCardDummy = m_disCardDummy;
			m_disCardDummy.clear();
		}
		
		//섞어주는 코드(수정)
		vector<CCard*> Temp = m_bringCardDummy;
		std::random_shuffle(Temp.begin(), Temp.end());

		if (!m_Hand.size() == 0) {
			Vector2(m_Hand.back()->GetPos());
		}
		m_Hand.push_back(Temp.back());
		for (int i = 0; i < m_bringCardDummy.size(); i++)
		{
			if (m_bringCardDummy[i] == Temp.back())
			{
				m_bringCardDummy.erase(m_bringCardDummy.begin()+i);
			}
		}
		//m_Hand.back()->SetIsAnimated(true);
		//m_bringCardDummy.pop_back();
	}
	HandSort();
}

void CCardManager::AddDiscard(CGameObject* Discard)
{
	m_disCardDummy.push_back((CCard*)Discard);
}

void CCardManager::AddExhaustcard(CGameObject* Deletecard)
{
	m_delCardDummy.push_back((CCard*)Deletecard);
}

void CCardManager::BattleStart()
{
	m_bringCardDummy = m_mainDeck; //메인 덱 가져올 카드로 가져온다
	//가져올 덱 을 섞는다.
	//카드를 n장 뽑는다
	//핸드에 n장을 가져온다.
}

void CCardManager::ClearHand()
{

}

void CCardManager::BattleReset()
{	
	vector<CCard*> a;
	m_disCardDummy = a;
	m_bringCardDummy = a;
	m_delCardDummy = a;
	RemoveHandAll(); //손에 핸드 비움
	CCardManager::GetInst()->SetTurnCount(1);
}

CGameObject* CCardManager::CardCheck()
{
	return m_CardCheck;
}


