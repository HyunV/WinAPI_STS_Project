#pragma once
#include "GameObject.h"
class CCharacter :
    public CGameObject
{
	friend class CScene;

protected:
	CCharacter();
	CCharacter(const CCharacter& Obj);
	virtual ~CCharacter();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

protected:
	CSharedPtr<class CWidgetComponent> m_HPBarFrame;
	CSharedPtr<class CWidgetComponent> m_HPBar;
	CSharedPtr<class CWidgetComponent> m_NameBar;
	CSharedPtr<class CWidgetComponent> m_HPText;

	int m_MaxHP;
	int m_HP;

	float m_AttackDir;
	float m_AttackSpeed;

	void AttackMotion(float Dir, float Speed);

};

