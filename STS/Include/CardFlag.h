#pragma once

enum class Card_Type
{
	Attack,
	Skill,
	Power,
	Curse
};

enum class Card_Value //�븻 Ư�� ���
{
	Common,
	Special,
	Rare
};

enum class Card_Attribute
{
	None,
	Damage, //������
	Shield, //�� ����
	DrawCard, //ī�� ���
	Exhaust, //�Ҹ�
	Vulnerable,//���
	Weak,		//��ȭ
	Inflame, //��ȭ(������)
	FootWork,//�߳(��ø����)
	Barricade,//�ٸ����̵�
	LimitBreak,//�Ѱ赹��
	DemonForm, //�Ǹ��� ����
	BodySlam, //���� ��ġ��
	Entrench, //��ȣ
	Text1, //�� �� ���� ��
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