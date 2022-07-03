//��ƿ��Ƽ ���������� ���� �� ��
#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map> 
#include <queue>
/*
�ؽ����̺� Ž�� �ڷᱸ�� O(1)�� �ӵ�
	* �׳� map�� ����Ž��Ʈ���� O(log(N)), �ߺ� �����͸� ��������ʰ� 
	* map���� �����Ͱ� ���� �� ����
	* ���ͷ����ͷ� �����ؾߵ�.
*/
#include <crtdbg.h> //�޸𸮴��� ã���ִ� ���̺귯��, ���ӸŴ��� �����ڿ� �����������

#include<typeinfo> //���� �ٸ� �� Ÿ�Ե��� ���� �� �ְ� Ÿ���� ���ڿ��� �ٲ��ش�?(id�������� ���)
#include<string>
#include<functional> //�����Լ�, ����Լ� ������� �Լ������� ����ϰ� �����ִ� ����� ����
#include <algorithm> //sort ��� ����
#include <stack>

using namespace std;

#include "Vector2.h"
#include "SharedPtr.h"
#include "Flag.h"
#include "fmod.hpp" //���� ���� �ܺ� ���̺귯��'

#define GRAVITY 9.8f

//���ҽ� ���� ���
#pragma comment(lib, "msimg32.lib") //�̹��� �ֱ� ���� ���̺귯��
#pragma comment(lib, "../Bin/fmod64_vc.lib") //���� ���̺귯��

//��������� ���� ������
#define ROOT_PATH "RootPath" //������
#define TEXTURE_PATH "TexturePath" //�ؽ�ó �̹��� ���
#define SOUND_PATH	"SoundPath"
#define FONT_PATH	"FontPath"
// GameFrameWokk/Bin/Texture

//������ ���� ��ũ��(�Ϲ� ����, �迭 ����, RC ����)
#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr;}
#define SAFE_RELEASE(p) if(p) {p->Release(); p = nullptr; }

float RadianToDegree(float Radian); //���� -> ��
float DegreeToRadian(float Degree); // �� -> ����

#define DELTA_TIME CGameManager::GetInst()->GetDeltaTime() //��ŸŸ�Ӱ� �������� ��ũ��

struct Resolution //�ػ�
{
	int Width;
	int Height;
};

struct AnimationFrameData
{
	Vector2 Start; //�ִϸ��̼��� ����
	Vector2 End; //�ִϸ��̼��� ��
};

struct CollisionProfile //�浹 ���� ����
{
	std::string							Name; //�̸�
	ECollision_Channel					Channel; //
	bool								Enable;
	std::vector<ECollision_Interaction> vecCollisionInteraction; //��ȣ�ۿ�
	/*
	Default,
		Player,
		Monster,
		PlayerAttack,
		MonsterAttack,
		Max
	�̰͵��� ���������ؼ� �浹ó���ϳ� �����ϳ� �����Ѵ�.
	*/
	CollisionProfile() :
		Enable(true), //�ʱⰪ true�� ���� ���
		Name("Noname"),
		Channel(ECollision_Channel::Default)
	{

	}
};

struct BoxInfo
{
	Vector2 LT;
	Vector2 RB; //Size
};

struct CircleInfo
{
	Vector2 Center;
	float Radius;
};
