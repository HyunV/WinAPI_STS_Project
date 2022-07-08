#pragma once
#include "GameObject.h"
class CTileMap :
    public CGameObject
{
    friend class CScene;

protected:
    CTileMap();
    virtual ~CTileMap();

private:
    std::vector<class CTile*> m_vecTile; //생성된 타일들
    CSharedPtr<class CTexture> m_TileTexture;
    
    //타일을 어느 밀도로 나눌 지 계산
    int m_CountX; // 가로로 x 개
    int m_CountY; // 세로로 y개

    Vector2 m_TileSize; //타일 하나의 크기
    int m_StartX;
    int m_StartY;
    int m_EndX;
    int m_EndY;

public:
    int GetCountX()	const
    {
        return m_CountX;
    }

    int GetCountY()	const
    {
        return m_CountY;
    }

public:
    void ChangeTileOption(const Vector2& Pos, ETile_Option Option);
    void SetTileFrame(const Vector2& Pos, const Vector2& Start,
        const Vector2& End);
    class CTile* GetTile(const Vector2& Pos); //위치를 넣었을 때
    class CTile* GetTile(int Index); //인덱스를 넣었을 때
    class CTile* GetTile(int IndexX, int IndexY); //인덱스 가로, 세로를 넣었을때
    int GetTileIndexX(float x); //x 인덱스
    int GetTileIndexY(float y); //y인덱스 구하기
    int GetTileIndex(const Vector2& Pos); //위치를 넣어서 x y를 구해주는 함수

public:
    bool CreateTile(int CountX, int CountY, const Vector2& TileSize); 
    void SetTileTexture(const std::string& Name);
    void SetTileTexture(class CTexture* Texture);
    void SetTileTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTileTextureFullPath(const std::string& Name, const TCHAR* FullPath);


#ifdef UNICODE

    void SetTileTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTileTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

    void SetTileTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTileTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif // UNICODE

    bool SetTileColorKey(unsigned char r, unsigned char g, unsigned char b,
        int Index = 0);
    bool SetTileColorKeyAll(unsigned char r, unsigned char g, unsigned char b);


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
};

