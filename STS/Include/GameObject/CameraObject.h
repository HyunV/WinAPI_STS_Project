#pragma once
#include "GameObject.h"
class CCameraObject :
    public CGameObject
{
    friend class CScene;

protected:
    CCameraObject();
    virtual ~CCameraObject();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);

private:
    void CameraMoveUp();
    void CameraMoveDown();
public:
    void CameraReset();
    void SetCameraPos(Vector2 v)
    {
        m_Pos = v;
    };
    void SetAutoCamera();
};

