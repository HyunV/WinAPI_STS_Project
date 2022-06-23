#pragma once
#include "Character.h"
class CMyPlayer :
    public CCharacter
{
    friend class CScene;

protected:
    CMyPlayer();
    CMyPlayer(const CMyPlayer& Obj);
    virtual ~CMyPlayer();

private:
    int m_HP;
    int m_HPMax;
	int m_Atk;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

public:
	void Buff();
	void Debuff();
};

