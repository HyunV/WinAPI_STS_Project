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
    std::vector<class CTile*> m_vecTile; //������ Ÿ�ϵ�
    CSharedPtr<class CTexture> m_TileTexture;
    
    //Ÿ���� ��� �е��� ���� �� ���
    int m_CountX; // ���η� x ��
    int m_CountY; // ���η� y��

    Vector2 m_TileSize; //Ÿ�� �ϳ��� ũ��
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
    class CTile* GetTile(const Vector2& Pos); //��ġ�� �־��� ��
    class CTile* GetTile(int Index); //�ε����� �־��� ��
    class CTile* GetTile(int IndexX, int IndexY); //�ε��� ����, ���θ� �־�����
    int GetTileIndexX(float x); //x �ε���
    int GetTileIndexY(float y); //y�ε��� ���ϱ�
    int GetTileIndex(const Vector2& Pos); //��ġ�� �־ x y�� �����ִ� �Լ�

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

