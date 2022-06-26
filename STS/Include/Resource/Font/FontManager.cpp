#include "FontManager.h"
#include "Font.h"
#include "../../PathManager.h"

CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
}

bool CFontManager::Init()
{
	LoadFont(TEXT("���õ����� Bold"));
	LoadFont(TEXT("Kreon"));

	LoadFont("DefaultFont", TEXT("���õ����� Bold"), 0, 0);
	LoadFont("NameFont", TEXT("���õ����� Bold"), 0, 14);
	LoadFont("TypeFont", TEXT("���õ����� Bold"), 0, -10);
	LoadFont("CostFont", TEXT("���õ����� Bold"), 0, 26);
	LoadFont("ExplainFont", TEXT("���õ����� Bold"), 0, 14);

	LoadFont("PlayerNameFont", TEXT("���õ����� Bold"), 0, 15);
	LoadFont("UI", TEXT("���õ����� Bold"), 0, 20);


	return true;
}

bool CFontManager::LoadFont(const std::string& Name, const TCHAR* FontName, int Width, int Height)
{
	CFont* Font = FindFont(Name);

	if (Font)
		return true;

	Font = new CFont;

	Font->SetName(Name);

	if (!Font->LoadFont(FontName, Width, Height))
	{
		SAFE_DELETE(Font);
		return false;
	}

	m_mapFont.insert(std::make_pair(Name, Font));

	return true;
}

bool CFontManager::LoadFont(const TCHAR* FontFileName, const std::string& PathName)
{
	TCHAR	FullPath[MAX_PATH] = {};

	const PathInfo* Info = CPathManager::GetInst()->FindPath(FONT_PATH);

	if (Info)
		lstrcpy(FullPath, Info->Path);

	lstrcat(FullPath, FontFileName);

	AddFontResource(FullPath);

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

CFont* CFontManager::FindFont(const std::string& Name)
{
	auto	iter = m_mapFont.find(Name);

	if (iter == m_mapFont.end())
		return nullptr;

	return iter->second;
}

void CFontManager::ReleaseFont(const std::string& Name)
{
	auto	iter = m_mapFont.find(Name);

	if (iter == m_mapFont.end())
		return;

	if (iter->second->GetRefCount() == 1)
		m_mapFont.erase(iter);
}
