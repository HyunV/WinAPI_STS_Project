#pragma once

enum class Card_Type
{
	Attack,
	Skill,
	Power,
	Curse
};

enum class Card_Value //³ë¸» Æ¯º° Èñ±Í
{
	Common,
	Special,
	Rare
};

//enum class Card_Ability

//enum class Player_Buff
//{
//	Atk,
//
//};

enum class Card_Attribute
{
	None,
	Damage,
	Shield,
	DrawCard,
	Attack,
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