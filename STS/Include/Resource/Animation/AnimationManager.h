#pragma once
//구조는 대체로 텍스처매니저와 비슷
#include "../../GameInfo.h"

class CAnimationManager
{
	friend class CResourceManager;

private:
	CAnimationManager();
	~CAnimationManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CAnimationSequence>>	m_mapSequence;
	//애니메이션 모션 하나하나 담는 변수?

public:
	bool Init();

public:
	bool CreateAnimationSequence(const std::string& Name, class CTexture* Texture); //이름과 텍스처 받아와서 시퀀스 생성
	bool AddAnimationFrame(const std::string& Name, const Vector2& Start,
		const Vector2& End);
	bool AddAnimationFrame(const std::string& Name,
		float PosX, float PosY, float SizeX, float SizeY);

	class CAnimationSequence* FindAnimation(const std::string& Name);
	void ReleaseAnimation(const std::string& Name);
};

