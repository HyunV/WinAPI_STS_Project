#include "FontManager.h"
#include "Font.h"
#include "../../PathManager.h"

#include "../../GameManager.h"
CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
	size_t size = m_LoadedFontFullpath.size();

	for (size_t i = 0; i < size; ++i)
	{
		RemoveFontResource(m_LoadedFontFullpath[i].c_str());
	}
}

bool CFontManager::Init()
{
	LoadFontResource(TEXT("GyeonggiCheonnyeonBatangBold.ttf"));
	LoadFontResource(TEXT("Kreon-Bold.ttf"));
	LoadFontResource(TEXT("04b03.ttf"));

	LoadFontInfo("DefaultFont", TEXT("경기천년바탕 Bold"), 0, 0);
	LoadFontInfo("NameFont", TEXT("경기천년바탕 Bold"), 0, 15);
	LoadFontInfo("TypeFont", TEXT("경기천년바탕 Bold"), 0, -10);
	LoadFontInfo("CostFont", TEXT("Kreon"), 0, 23);
	LoadFontInfo("ExplainFont", TEXT("04b03"), 0, 14);
	LoadFontInfo("PlayerExplainFont", TEXT("경기천년바탕 Bold"), 0, 26);

	LoadFontInfo("PlayerNameFont", TEXT("경기천년바탕 Bold"), 0, 15);
	LoadFontInfo("UI", TEXT("경기천년바탕 Bold"), 0, 20);
	LoadFontInfo("Shield", TEXT("경기천년바탕 Bold"), 0, 18);
	LoadFontInfo("DamageFont", TEXT("경기천년바탕 Bold"), 0, 40);
	LoadFontInfo("TurnMessageFont", TEXT("경기천년바탕 Bold"), 0, 60);
	LoadFontInfo("EnergyFont", TEXT("경기천년바탕 Bold"), 0, 32);
	LoadFontInfo("BuffFont", TEXT("04b03"), 0, -10);




	return true;
}

CFont* CFontManager::FindFont(const std::string& Name)
{
	auto	iter = m_mapFont.find(Name);

	if (iter == m_mapFont.end())
		return nullptr;

	return iter->second;
}

bool CFontManager::LoadFontInfo(const std::string& Name, const std::tstring& FontName, int Width, int Height)
{
	CFont* Font = FindFont(Name);

	if (Font)
		return true;

	Font = new CFont;


	Font->SetName(Name);


	if (!Font->LoadFontInfo(Name, FontName, Width, Height))
	{
		SAFE_DELETE(Font);
		return false;
	}

	m_mapFont.insert(std::make_pair(Name, Font));

	return true;
}

bool CFontManager::LoadFontResource(const std::tstring& FontFileName, const std::string& PathName)
{
	TCHAR	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(FONT_PATH);

	if (Info)
		lstrcpy(FullPath, Info->Path);

	lstrcat(FullPath, FontFileName.c_str());

	if (AddFontResource(FullPath) == 0)
		return false;

	m_LoadedFontFullpath.push_back(FullPath);

	return true;
}

void CFontManager::SetFont(const std::string& Name, HDC hDC)
{
	CFont* Font = FindFont(Name);

	if (!Font)
		return;

	Font->SetFont(hDC);
}

void CFontManager::ResetFont(const std::string& Name, HDC hDC)
{
	CFont* Font = FindFont(Name);

	if (!Font)
		return;

	Font->ResetFont(hDC);
}

void CFontManager::ReleaseFont(const std::string& Name)
{
	auto	iter = m_mapFont.find(Name);

	if (iter == m_mapFont.end())
		return;

	if (iter->second->GetRefCount() == 1)
		m_mapFont.erase(iter);
}



//bool CFontManager::LoadFont(const std::string& Name, const TCHAR* FontName, int Width, int Height)
//{
//	CFont* Font = FindFont(Name);
//
//	if (Font)
//		return true;
//
//	Font = new CFont;
//
//	Font->SetName(Name);
//
//	if (!Font->LoadFont(FontName, Width, Height))
//	{
//		SAFE_DELETE(Font);
//		return false;
//	}
//
//	m_mapFont.insert(std::make_pair(Name, Font));
//
//	return true;
//}
//
//bool CFontManager::LoadFont(const TCHAR* FontFileName, const std::string& PathName)
//{
//	TCHAR	FullPath[MAX_PATH] = {};
//
//	const PathInfo* Info = CPathManager::GetInst()->FindPath(FONT_PATH);
//
//	if (Info)
//		lstrcpy(FullPath, Info->Path);
//
//	lstrcat(FullPath, FontFileName);
//
//	AddFontResource(FullPath);
//
//	return true;
//}
//
//void CFontManager::SetFont(const std::string& Name, HDC hDC)
//{
//	CFont* Font = FindFont(Name);
//
//	if (!Font)
//		return;
//
//	Font->SetFont(hDC);
//}
//
//void CFontManager::ResetFont(const std::string& Name, HDC hDC)
//{
//	CFont* Font = FindFont(Name);
//
//	if (!Font)
//		return;
//
//	Font->ResetFont(hDC);
//}
//
//CFont* CFontManager::FindFont(const std::string& Name)
//{
//	auto	iter = m_mapFont.find(Name);
//
//	if (iter == m_mapFont.end())
//		return nullptr;
//
//	return iter->second;
//}
//
//bool CFontManager::LoadFontInfo(const std::string& Name, const std::tstring& FontName, int Width, int Height)
//{
//	return false;
//}
//
//bool CFontManager::LoadFontResource(const std::tstring& FontFileName, const std::string& PathName)
//{
//	return false;
//}
//
//void CFontManager::ReleaseFont(const std::string& Name)
//{
//	auto	iter = m_mapFont.find(Name);
//
//	if (iter == m_mapFont.end())
//		return;
//
//	if (iter->second->GetRefCount() == 1)
//		m_mapFont.erase(iter);
//}
