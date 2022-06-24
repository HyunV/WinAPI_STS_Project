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
	
	int m_Shield;//¹æ¾îµµ


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

public:
	float AddShield(float shield);
	void Buff();
	void Debuff();
private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

