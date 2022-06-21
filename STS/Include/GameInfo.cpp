#include "GameInfo.h"


float RadianToDegree(float Radian) { //라디안 -> 도
	return Radian / PI * 180.f;
}
float DegreeToRadian(float Degree) { //도-> 라디안
	return Degree / 180.f * PI;
}
