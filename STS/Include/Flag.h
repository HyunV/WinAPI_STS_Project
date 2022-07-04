#pragma once

enum class ETexture_Type //�ؽ�ó ���� 
{
	Sprite, 
	Frame
};

enum class ERender_Layer //��� ���̾� ���� m_ObjList �� �� �Ӽ��� �ο��ؼ� ������ �����
{
	Back, //����
	Deco,
	Default,
	Effect,
	Black,
	Hand,	
	Max
};

enum class ECollision_Channel //�浹 ä�� Ű? �Ǿƽĺ��� ����ü 
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
	//�浹 ��ȣ�ۿ� ���� (����, �浹)
{
	Ignore,
	Collision
};

enum class ECollider_Type
	//��Ʈ�ڽ� ���(�簢��, ��)
{
	Box,
	Circle
};

enum class EBrush_Type
{ 
	Red, //�浹�ҋ�
	Green, //���� �ʤ�����
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

enum class ETile_Option //�Ϲ� ����, ���̽� ���� �̷��͵�
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