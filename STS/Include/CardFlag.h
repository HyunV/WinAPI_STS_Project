#pragma once

enum class Card_Type
{
	Attack,
	Skill,
	Power,
	Curse
};

enum class Card_Value //노말 특별 희귀
{
	Common,
	Special,
	Rare
};

enum class Card_Attribute
{
	None,
	Damage, //데미지
	Shield, //방어도 증가
	DrawCard, //카드 드로
	Exhaust, //소멸
	Vulnerable,//취약
	Weak,		//약화
	Inflame, //발화(공버프)
	FootWork,//발놀림(민첩버프)
	Barricade,//바리케이드
	LimitBreak,//한계돌파
	DemonForm, //악마의 형상
	BodySlam, //몸통 박치기
	Entrench, //참호
	Text1, //내 턴 시작 시
};

enum class Card_Preview
{
	Preview,
	Hand
};

enum class Buff
{
	Atk,
	Dex,
	DemonForm,
	Barrigate,
	Rage,
	Ritual,
	Vulnerable,
	Weak,
	Max
};