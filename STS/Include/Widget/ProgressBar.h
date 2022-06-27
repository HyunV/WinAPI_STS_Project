#pragma once
#include "Widget.h"

enum class EProgressBar_Texture_Type
{
    Back, //배경
    ShieldBarBack,
    Bar, //바 이미지
    ShieldBar,
    End
};

enum class EProgressBar_Dir
{
    LeftToRight,
    RightToLeft,
    BottomToTop,
    TopToBottom,
    End
};

enum class EProgressBar_Color
{
    Default,
    Shield,
    End
};

class CProgressBar :
    public CWidget
{
    friend class CWidgetComponent;
    friend class CWidgetWindow;
    

protected:
    CProgressBar();
    CProgressBar(const CProgressBar& widget);
    virtual ~CProgressBar();

protected:
    CSharedPtr<class CTexture> m_Texture[(int)EProgressBar_Texture_Type::End];
    EProgressBar_Dir    m_Dir;
    float               m_Value;
    Vector2             m_BarSize;
    Vector2             m_BarPos;
    
    EProgressBar_Color  m_BarType;
    AnimationFrameData m_StateData[(int)EProgressBar_Color::End];

public:
    void SetBarStateData(EProgressBar_Color State, const Vector2& Start, const Vector2& End);
    void SetBarDir(EProgressBar_Dir Dir)
    {
        m_Dir = Dir;
    }

    void SetValue(float Value)
    {
        m_Value = Value;

        if (m_Value > 1.f)
            m_Value = 1.f;

        else if (m_Value < 0.f)
            m_Value = 0.f;
    }

    void AddValue(float Value)
    {
        m_Value += Value;

        if (m_Value > 1.f)
            m_Value = 1.f;

        else if (m_Value < 0.f)
            m_Value = 0.f;
    }
    void SetBarType(EProgressBar_Color Type)
    {
        m_BarType = Type;
    }

public:
    void SetTexture(EProgressBar_Texture_Type Type, const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type Type, const std::string& Name, const TCHAR* FullPath);
    
    void SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName);
#ifdef UNICODE

    void SetTexture(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::wstring>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

    void SetTexture(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::string>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif

    void SetColorKey(EProgressBar_Texture_Type Type, unsigned char r, unsigned char g, unsigned char b);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime);

public:


};

