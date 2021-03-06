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
	int m_Atk;

	Vector2 Dir;
	Vector2 OriginPos;
	int cnt;
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

