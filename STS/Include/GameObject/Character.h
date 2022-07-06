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
	/// //�ؽ�Ʈ
	/// </summary>
	CSharedPtr<class CWidgetComponent> m_AtkBuffText;
	CSharedPtr<class CWidgetComponent> m_DexBuffText;
	CSharedPtr<class CWidgetComponent> m_DemonFormText;
	CSharedPtr<class CWidgetComponent> m_BarricadeText;

	CSharedPtr<class CWidgetComponent> m_RageBuffText;
	CSharedPtr<class CWidgetComponent> m_RitualBuffText;

	CSharedPtr<class CWidgetComponent> m_VulDeBuffText;
	CSharedPtr<class CWidgetComponent> m_WeakDeBuffText;
	//���� ��ø �Ǹ������� �ٸ����̵�
	//�ݳ�, �ǽ�
	//��� ��ȭ
	vector<CSharedPtr<class CWidgetComponent>> m_StatusList; 
	//���� ���� �����ϴ� �������ͽ��� �ִ´�.
	vector<CSharedPtr<class CWidgetComponent>> m_ValueList;

	Vector2 m_BuffFirstPos;
	Vector2 m_TextOffSet;
	int* ArrTemp;
	virtual void UpdateStatus();
	void ConvertText(int Value, CSharedPtr<class CWidgetComponent> TextWiz);
	

	vector<CSharedPtr<class CWidgetComponent>> m_TestButton;
	void TestCallback();

};

