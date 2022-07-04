#pragma once

enum class ETexture_Type //텍스처 구분 
{
	Sprite, 
	Frame
};

enum class ERender_Layer //출력 레이어 순서 m_ObjList 에 이 속성을 부여해서 순서를 만든다
{
	Back, //배경용
	Deco,
	Default,
	Effect,
	Black,
	Hand,	
	Max
};

enum class ECollision_Channel //충돌 채널 키? 피아식별용 열거체 
{
	Default,
	Player,
	Monster,
	PlayerAttack,
	MonsterAttack,
	Card,
	MyPlayer,
	Mouse,
	Max
};

enum class ECollision_Interaction 
	//충돌 상호작용 여부 (무시, 충돌)
{
	Ignore,
	Collision
};

enum class ECollider_Type
	//히트박스 모양(사각형, 원)
{
	Box,
	Circle
};

enum class EBrush_Type
{ 
	Red, //충돌할떄
	Green, //닿지 않ㅇ르때
	Black,
	Blue,
	Yellow,
	Max
};

enum class EEffect_Type
{
	Once,
	Duration,
	Loop
};

enum class EButton_State
{
	Normal,
	MouseHovered,
	Click,
	Disable,
	Max
};

enum class EButton_Sound_State
{
	MouseHovered,
	Click,
	Max
};

enum class ECheckBox_State
{
	Disable,
	Enable,
	Max
};

enum class ETile_Option //일반 발판, 아이스 발판 이런것들
{
	Normal,
	ImpossibleToMove
};

enum class EMessageBox_Type
{
	Default,
	Shop
};

enum class EWhos_Turn
{
	None,
	Player,
	Monster
};