#pragma once
#include "GameObject.h"
class CSatellite :
    public CGameObject
{
	friend class CScene;

protected:
    CSatellite();
    CSatellite(const CSatellite& Obj);
    virtual ~CSatellite();

private:

public:

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};
