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

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

	float m_AttackDir;
	float m_AttackSpeed;
};

