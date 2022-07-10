#pragma once
#include "../GameInfo.h"
//씬이 1번 씬 2번 씬 이렇게 있는데 1->2로 넘어가기 위해선 1번에 있는 리소스(텍스처)를 모두 제거하고 넘어가야 한다.
//근데 텍스처 매니저는 1번 2번 씬의 텍스처를 한꺼번에 받아서 관리하고 있다.
//이럴 때 씬 넘어갈 때 어떤 텍스처를 제거해야 하는지 알 수 없으니 씬 리소스라는 클래스를 통해 텍스처, 애니메이션을 관리한다.
//# 1-> 2 씬 넘어가도 계속 쓰는 리소스들은 제거하지 않게도 관리한다.


class CSceneResource
{
	friend class CScene;

private:
	CSceneResource();
	~CSceneResource();

private:
	std::unordered_map<std::string, CSharedPtr<class CTexture>> m_mapTexture;
	std::unordered_map<std::string, CSharedPtr<class CAnimationSequence>> m_mapAnimationSequence;
	std::unordered_map<std::string, CSharedPtr<class CSound>> m_mapSound;
	std::unordered_map<std::string, CSharedPtr<class CFont>> m_mapFont;

public: ///////////////텍스쳐///////////////
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);


#ifdef UNICODE
	bool LoadTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);
#else

	bool LoadTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif

	bool SetColorKey(const std::string& Name, unsigned char r, unsigned char g, unsigned char b,
		int Index = 0);
	bool SetColorKeyAll(const std::string& Name, unsigned char r, unsigned char g, unsigned char b);

	class CTexture* FindTexture(const std::string& Name);

public:	// ==================== Animation Sequence ====================
	bool CreateAnimationSequence(const std::string& Name, class CTexture* Texture);
	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName);
	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const TCHAR* FileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const TCHAR* FullPath);

#ifdef UNICODE

	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const std::vector<std::wstring>& vecFileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const std::vector<std::wstring>& vecFullPath);

#else

	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const std::vector<std::string>& vecFileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const std::vector<std::string>& vecFullPath);

#endif // UNICODE


	bool AddAnimationFrame(const std::string& Name, const Vector2& Start,
		const Vector2& End);
	bool AddAnimationFrame(const std::string& Name,
		float PosX, float PosY, float SizeX, float SizeY);

	class CAnimationSequence* FindAnimation(const std::string& Name);

public:	// ============================ Sound ================================
	bool CreateSoundChannel(const std::string& Name);
	bool LoadSound(const std::string& GroupName, const std::string& Name,
		bool Loop, const char* FileName, const std::string& PathName = SOUND_PATH);
	bool SetVolume(int Volume);
	bool SetVolume(const std::string& GroupName, int Volume);
	bool SoundPlay(const std::string& Name);
	bool SoundStop(const std::string& Name);
	bool SoundPause(const std::string& Name);
	bool SoundResume(const std::string& Name);


	FMOD::ChannelGroup* FindChannelGroup(const std::string& Name);
	class CSound* FindSound(const std::string& Name);


public:	// =========================== Font ==============================
	bool LoadFontInfo(const std::string& Name, const std::tstring& FontName,
		int Width, int Height);
	bool LoadFontResource(
		const std::tstring& FontFileName,
		const std::string& PathName = FONT_PATH);
	void SetFont(const std::string& Name, HDC hDC);
	void ResetFont(const std::string& Name, HDC hDC);
	class CFont* FindFont(const std::string& Name);
};

