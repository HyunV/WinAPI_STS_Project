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
	
	CSharedPtr<class CWidgetComponent> m_ShieldImage;
	CSharedPtr<class CWidgetComponent> m_ShieldText;

	/// <summary>
	/// ////////////////////////////////////////////////
	/// </summary>

	CSharedPtr<class CWidgetComponent> m_AtkBuff;
	CSharedPtr<class CWidgetComponent> m_DexBuff;
	CSharedPtr<class CWidgetComponent> m_DemonForm;
	CSharedPtr<class CWidgetComponent> m_Barricade;

	CSharedPtr<class CWidgetComponent> m_RageBuff;
	CSharedPtr<class CWidgetComponent> m_RitualBuff;
	
	CSharedPtr<class CWidgetComponent> m_VulDeBuff;
	CSharedPtr<class CWidgetComponent> m_WeakDeBuff;
	/// <summary>
	/// //텍스트
	/// </summary>
	CSharedPtr<class CWidgetComponent> m_AtkBuffText;
	CSharedPtr<class CWidgetComponent> m_DexBuffText;
	CSharedPtr<class CWidgetComponent> m_DemonFormText;
	CSharedPtr<class CWidgetComponent> m_BarricadeText;

	CSharedPtr<class CWidgetComponent> m_RageBuffText;
	CSharedPtr<class CWidgetComponent> m_RitualBuffText;

	CSharedPtr<class CWidgetComponent> m_VulDeBuffText;
	CSharedPtr<class CWidgetComponent> m_WeakDeBuffText;
	//공격 민첩 악마의형상 바리케이드
	//격노, 의식
	//취약 약화
	vector<CSharedPtr<class CWidgetComponent>> m_StatusList; 
	//현재 값이 존재하는 스테이터스를 넣는다.
	vector<CSharedPtr<class CWidgetComponent>> m_ValueList;

	Vector2 m_BuffFirstPos;
	Vector2 m_TextOffSet;
	int* ArrTemp;
	virtual void UpdateStatus();
	void ConvertText(int Value, CSharedPtr<class CWidgetComponent> TextWiz);
	

	vector<CSharedPtr<class CWidgetComponent>> m_TestButton;
	void TestCallback();

};

