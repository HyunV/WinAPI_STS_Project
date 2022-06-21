#pragma once
#include "Widget.h"
class CImageWidget :
    public CWidget
{
    friend class CWidgetWindow;

protected:
    CImageWidget();
    CImageWidget(const CImageWidget& widget);
    virtual ~CImageWidget();

protected:
    CSharedPtr<class CTexture> m_Texture;
    AnimationFrameData m_CheckStateData[(int)ECheckBox_State::Max];
    ECheckBox_State         m_CheckState;
    std::function<void()>   m_Callback[(int)ECheckBox_State::Max]; //버튼을 눌렀을때 동작할 함수
    
    bool m_Clicked;
    HWND m_hWnd;
    Vector2 m_MouseMove;
    Vector2 m_MousePos;

public:
    void SetTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE

    void SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

    void SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif
    void SetImageStateData(ECheckBox_State State, const Vector2& Start, const Vector2& End);

    void EnableCheck(bool Enable)
    {
        m_CheckState = Enable ? ECheckBox_State::Disable : ECheckBox_State::Enable;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime);

public:
    virtual void CollisionMouseHoveredCallback(const Vector2& Pos);
    virtual void CollisionMouseReleaseCallback();

public:
    bool SetColorKey(unsigned char r, unsigned char g, unsigned char b);
    bool SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b);

public:
    template <typename T>
    void SetCallback(ECheckBox_State State, T* Obj, void(T::* Func)())
    {
        m_Callback[(int)m_CheckState] = std::bind(Func, Obj);
    }
};


