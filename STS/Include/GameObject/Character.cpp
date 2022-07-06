#include "Character.h"

#include "../GameManager.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"
#include "../Widget/ImageWidget2.h"
#include "../Widget/Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CCharacter::CCharacter()
{
	SetTypeID<CCharacter>();
	//m_BuffFirstPos = (-60.f, 120.f); //플레이어 오프셋
	//m_TextOffSet = (15.f, 13.f);
	ArrTemp = nullptr;
}

CCharacter::CCharacter(const CCharacter& Obj) :
	CGameObject(Obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	//m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
	//	"61.mp3");
	
	m_HPBarFrame = CreateWidgetComponent<CProgressBar>("HPBarFrame");
	m_HPBarFrame->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Back,
		"HPFrame", TEXT("HPBar/BarPanel.bmp"));
	m_HPBarFrame->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Default, Vector2(0, 0), Vector2(130, 12));
	m_HPBarFrame->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Shield, Vector2(130, 0), Vector2(260, 12));
	m_HPBarFrame->GetWidget<CProgressBar>()->SetColorKey(EProgressBar_Texture_Type::Back, 255, 0, 255);
	m_HPBarFrame->GetWidget<CProgressBar>()->SetSize(130.f, 12.f);

	m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");
	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar,
		"HPBar", TEXT("HPBar/BarHP.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Default, Vector2(0, 0), Vector2(126, 12));
	m_HPBar->GetWidget<CProgressBar>()->SetBarStateData(EProgressBar_Color::Shield, Vector2(126, 0), Vector2(252, 12));
	m_HPBar->GetWidget<CProgressBar>()->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);
	m_HPBar->GetWidget<CProgressBar>()->SetSize(126.f, 12.f);


	m_HPText = CreateWidgetComponent<CText>("HPText");
	m_HPText->GetWidget<CText>()->SetText(TEXT("죽음"));
	m_HPText->GetWidget<CText>()->EnableShadow(true);
	m_HPText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_HPText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_HPText->GetWidget<CText>()->SetFont("UI");
	m_HPText->GetWidget<CText>()->SetSize(100, 100);

	m_HPBarFrame->SetPos(0.f, 100.f);
	m_HPBar->SetPos(0.f, 100.f);
	Vector2 v = m_HPBar->GetPos();
	m_HPText->SetPos(50.f, 137.f);

	m_ShieldImage = CreateWidgetComponent<CImageWidget2>("ShieldImage");
	m_ShieldImage->GetWidget<CImageWidget2>()->SetTexture("AddShield", TEXT("Effects/block.bmp"));
	m_ShieldImage->GetWidget<CImageWidget2>()->SetSize(32, 32);
	m_ShieldImage->SetPos(-60, 98);
	m_ShieldImage->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_ShieldImage->GetWidget<CImageWidget2>()->SetEnable(false);

	m_ShieldText = CreateWidgetComponent<CText>("ShieldText");
	m_ShieldText->GetWidget<CText>()->SetText(TEXT("5"));
	m_ShieldText->GetWidget<CText>()->EnableShadow(true);
	m_ShieldText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_ShieldText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_ShieldText->GetWidget<CText>()->SetFont("Shield");
	m_ShieldText->GetWidget<CText>()->SetSize(32, 32);
	m_ShieldText->SetPos(-46, 100);
	m_ShieldText->GetWidget<CText>()->SetEnable(false);

	//버프, 디버프 관련 텍스트

	m_AtkBuff = CreateWidgetComponent<CImageWidget2>("AtkBuff");
	m_AtkBuff->GetWidget<CImageWidget2>()->SetTexture("AtkBuff", TEXT("Buff/atk.bmp"));
	m_AtkBuff->GetWidget<CImageWidget2>()->SetSize(20, 20);
	m_AtkBuff->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_AtkBuff->GetWidget<CImageWidget2>()->SetEnable(true);

	m_AtkBuffText = CreateWidgetComponent<CText>("AtkBuffText");
	m_AtkBuffText->GetWidget<CText>()->SetFont("TypeFont");
	m_AtkBuffText->GetWidget<CText>()->SetText(TEXT("1"));
	m_AtkBuffText->GetWidget<CText>()->EnableShadow(true);
	m_AtkBuffText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_AtkBuffText->GetWidget<CText>()->SetTextColor(255, 255, 0);
	m_AtkBuffText->GetWidget<CText>()->SetSize(20, 20);
	//m_AtkBuffText->SetPos(-25.f+15.f ,115.f+13.f);
	m_AtkBuffText->GetWidget<CText>()->SetEnable(true);

	m_DexBuff = CreateWidgetComponent<CImageWidget2>("DexBuff");
	m_DexBuff->GetWidget<CImageWidget2>()->SetTexture("DexBuff", TEXT("Buff/def.bmp"));
	m_DexBuff->GetWidget<CImageWidget2>()->SetSize(20, 20);
	//m_DexBuff->SetPos(-25+20, 120);
	m_DexBuff->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_DexBuff->GetWidget<CImageWidget2>()->SetEnable(true);

	m_DexBuffText = CreateWidgetComponent<CText>("DexBuffText");
	m_DexBuffText->GetWidget<CText>()->SetFont("TypeFont");
	m_DexBuffText->GetWidget<CText>()->SetText(TEXT("2"));
	m_DexBuffText->GetWidget<CText>()->EnableShadow(true);
	m_DexBuffText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_DexBuffText->GetWidget<CText>()->SetTextColor(255, 255, 0);
	m_DexBuffText->GetWidget<CText>()->SetSize(19, 18);
	//m_DexBuffText->SetPos(-25.f + 15.f+20.f, 115.f + 13.f);
	m_DexBuffText->GetWidget<CText>()->SetEnable(true);

	m_DemonForm = CreateWidgetComponent<CImageWidget2>("DemonForm");
	m_DemonForm->GetWidget<CImageWidget2>()->SetTexture("DemonForm", TEXT("Buff/dem.bmp"));
	m_DemonForm->GetWidget<CImageWidget2>()->SetSize(20, 20);
	//m_DemonForm->SetPos(-25 + 20+20, 120);
	m_DemonForm->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_DemonForm->GetWidget<CImageWidget2>()->SetEnable(true);

	m_DemonFormText = CreateWidgetComponent<CText>("DemonFormText");
	m_DemonFormText->GetWidget<CText>()->SetFont("TypeFont");
	m_DemonFormText->GetWidget<CText>()->SetText(TEXT("3"));
	m_DemonFormText->GetWidget<CText>()->EnableShadow(true);
	m_DemonFormText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_DemonFormText->GetWidget<CText>()->SetTextColor(255, 255, 0);
	m_DemonFormText->GetWidget<CText>()->SetSize(20, 20);
	//m_DemonFormText->SetPos(-25.f + 15.f + 20.f + 20.f, 115.f + 13.f);
	m_DemonFormText->GetWidget<CText>()->SetEnable(true);

	m_Barricade = CreateWidgetComponent<CImageWidget2>("Barricade");
	m_Barricade->GetWidget<CImageWidget2>()->SetTexture("Barricade", TEXT("Buff/bar.bmp"));
	m_Barricade->GetWidget<CImageWidget2>()->SetSize(20, 20);
	//m_Barricade->SetPos(100, 120);
	m_Barricade->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_Barricade->GetWidget<CImageWidget2>()->SetEnable(true);

	m_BarricadeText = CreateWidgetComponent<CText>("BarricadeText");
	m_BarricadeText->GetWidget<CText>()->SetFont("TypeFont");
	m_BarricadeText->GetWidget<CText>()->SetText(TEXT("4"));
	m_BarricadeText->GetWidget<CText>()->EnableShadow(true);
	m_BarricadeText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_BarricadeText->GetWidget<CText>()->SetTextColor(255, 255, 0);
	m_BarricadeText->GetWidget<CText>()->SetSize(20, 20);
	//m_BarricadeText->SetPos(200, 115.f + 13.f);
	m_BarricadeText->GetWidget<CText>()->SetEnable(true);

	m_RageBuff = CreateWidgetComponent<CImageWidget2>("RageBuff");
	m_RageBuff->GetWidget<CImageWidget2>()->SetTexture("RageBuff", TEXT("Buff/rage.bmp"));
	m_RageBuff->GetWidget<CImageWidget2>()->SetSize(20, 20);
	//m_RageBuff->SetPos(300, 120);
	m_RageBuff->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_RageBuff->GetWidget<CImageWidget2>()->SetEnable(true);

	m_RageBuffText = CreateWidgetComponent<CText>("RageBuffText");
	m_RageBuffText->GetWidget<CText>()->SetFont("TypeFont");
	m_RageBuffText->GetWidget<CText>()->SetText(TEXT("5"));
	m_RageBuffText->GetWidget<CText>()->EnableShadow(true);
	m_RageBuffText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_RageBuffText->GetWidget<CText>()->SetTextColor(255, 255, 0);
	m_RageBuffText->GetWidget<CText>()->SetSize(20, 20);
	//m_RageBuffText->SetPos(-25.f + 15.f + 20.f + 20.f, 115.f + 13.f);
	m_RageBuffText->GetWidget<CText>()->SetEnable(true);

	m_RitualBuff = CreateWidgetComponent<CImageWidget2>("RitualBuff");
	m_RitualBuff->GetWidget<CImageWidget2>()->SetTexture("RitualBuff", TEXT("Buff/rit.bmp"));
	m_RitualBuff->GetWidget<CImageWidget2>()->SetSize(20, 20);
	//m_RitualBuff->SetPos(350, 120);
	m_RitualBuff->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_RitualBuff->GetWidget<CImageWidget2>()->SetEnable(true);

	m_RitualBuffText = CreateWidgetComponent<CText>("RitualBuffText");
	m_RitualBuffText->GetWidget<CText>()->SetFont("TypeFont");
	m_RitualBuffText->GetWidget<CText>()->SetText(TEXT("6"));
	m_RitualBuffText->GetWidget<CText>()->EnableShadow(true);
	m_RitualBuffText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_RitualBuffText->GetWidget<CText>()->SetTextColor(255, 255, 0);
	m_RitualBuffText->GetWidget<CText>()->SetSize(20, 20);
	//m_RitualBuffText->SetPos(-25.f + 15.f + 20.f + 20.f, 115.f + 13.f);
	m_RitualBuffText->GetWidget<CText>()->SetEnable(true);

	m_VulDeBuff = CreateWidgetComponent<CImageWidget2>("VulDeBuff");
	m_VulDeBuff->GetWidget<CImageWidget2>()->SetTexture("VulDeBuff", TEXT("Buff/vul.bmp"));
	m_VulDeBuff->GetWidget<CImageWidget2>()->SetSize(20, 20);
	//m_VulDeBuff->SetPos(400, 120);
	m_VulDeBuff->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_VulDeBuff->GetWidget<CImageWidget2>()->SetEnable(true);

	m_VulDeBuffText = CreateWidgetComponent<CText>("m_VulDeBuffText");
	m_VulDeBuffText->GetWidget<CText>()->SetFont("TypeFont");
	m_VulDeBuffText->GetWidget<CText>()->SetText(TEXT("7"));
	m_VulDeBuffText->GetWidget<CText>()->EnableShadow(true);
	m_VulDeBuffText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_VulDeBuffText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_VulDeBuffText->GetWidget<CText>()->SetSize(20, 20);
	//m_VulDeBuffText->SetPos(-25.f + 15.f + 20.f + 20.f, 115.f + 13.f);
	m_VulDeBuffText->GetWidget<CText>()->SetEnable(true);

	m_WeakDeBuff = CreateWidgetComponent<CImageWidget2>("WeakDeBuff");
	m_WeakDeBuff->GetWidget<CImageWidget2>()->SetTexture("WeakDeBuff", TEXT("Buff/weak.bmp"));
	m_WeakDeBuff->GetWidget<CImageWidget2>()->SetSize(20, 20);
	//m_WeakDeBuff->SetPos(450, 120);
	m_WeakDeBuff->GetWidget<CImageWidget2>()->SetColorKey(255, 0, 255);
	m_WeakDeBuff->GetWidget<CImageWidget2>()->SetEnable(true);
	

	m_WeakDeBuffText = CreateWidgetComponent<CText>("WeakDeBuffText");
	m_WeakDeBuffText->GetWidget<CText>()->SetFont("TypeFont");
	m_WeakDeBuffText->GetWidget<CText>()->SetText(TEXT("8"));
	m_WeakDeBuffText->GetWidget<CText>()->EnableShadow(true);
	m_WeakDeBuffText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_WeakDeBuffText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_WeakDeBuffText->GetWidget<CText>()->SetSize(20, 20);
	//m_WeakDeBuffText->SetPos(-25.f + 15.f + 20.f + 20.f, 115.f + 13.f);
	m_WeakDeBuffText->GetWidget<CText>()->SetEnable(true);

	m_StatusList.push_back(m_AtkBuff);
	m_StatusList.push_back(m_DexBuff);
	m_StatusList.push_back(m_DemonForm);
	m_StatusList.push_back(m_Barricade);
	m_StatusList.push_back(m_RageBuff);
	m_StatusList.push_back(m_RitualBuff);
	m_StatusList.push_back(m_VulDeBuff);
	m_StatusList.push_back(m_WeakDeBuff);
	//현재 값이 존재하는 스테이터스를 넣는다.

	m_ValueList.push_back(m_AtkBuffText);
	m_ValueList.push_back(m_DexBuffText);
	m_ValueList.push_back(m_DemonFormText);
	m_ValueList.push_back(m_BarricadeText);
	m_ValueList.push_back(m_RageBuffText);
	m_ValueList.push_back(m_RitualBuffText);
	m_ValueList.push_back(m_VulDeBuffText);
	m_ValueList.push_back(m_WeakDeBuffText);
	
	//######################여기 버튼##########################33
	//CWidgetComponent* TestButton = CreateWidgetComponent<CButton>("TestButtonss");
	//TestButton->GetWidget<CButton>()->SetTexture("TestButtonss", TEXT("TopPanel/endTurnButton.bmp"));
	//TestButton->GetWidget<CButton>()->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(154.f, 154.f));
	//TestButton->GetWidget<CButton>()->SetButtonStateData(EButton_State::MouseHovered, Vector2(154.f, 0.f), Vector2(308.f, 154.f));
	//TestButton->GetWidget<CButton>()->SetButtonStateData(EButton_State::Click, Vector2(154.f, 0.f), Vector2(308.f, 154.f));
	//TestButton->SetPos(200.f, 100.f);
	//TestButton->GetWidget<CButton>()->SetColorKey(255, 0, 255);
	//TestButton->GetWidget<CButton>()->SetZOrder(1);
	//TestButton->GetWidget<CButton>()->SetCallback<CCharacter>(EButton_Sound_State::Click,
	//	this, &CCharacter::TestCallback);
	//############################################################
	
	return true;
}

void CCharacter::Update(float DeltaTime)
{
	//UpdateStatus();
	CGameObject::Update(DeltaTime);

	if (m_Shield > 0) {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Shield);
		m_ShieldImage->GetWidget<CImageWidget2>()->SetEnable(true);
		m_ShieldText->GetWidget<CImageWidget2>()->SetEnable(true);

		ConvertText(m_Shield, m_ShieldText);

	}
	else {
		m_HPBarFrame->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
		m_HPBar->GetWidget<CProgressBar>()->SetBarType(EProgressBar_Color::Default);
		m_ShieldImage->GetWidget<CImageWidget2>()->SetEnable(false);
		m_ShieldText->GetWidget<CImageWidget2>()->SetEnable(false);
	}

	char Text[256] = {};
	sprintf_s(Text, "%d/%d", m_HP, m_MaxHP);

	TCHAR Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);
	m_HPText->GetWidget<CText>()->SetText(Unicode);

	UpdateStatus();

	//상태이상 배치
	int count = 0;


	//for (int i = 0; i < m_StatusList.size(); i++)
	//{
	//	if (m_StatusList[i]->GetWidget()->GetEnable())
	//	{
	//		count++;
	//	}
	//}

	auto iter = m_StatusList.begin();
	auto end = m_StatusList.end();


	for (; iter != end;) 
	{
		if (!(*iter)->GetWidget()->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->SetPos(m_BuffFirstPos.x+(count*20), 120.f);
		iter++;
		count++;
	}

	count = 0;

	//for (int i = 0; i < m_ValueList.size(); i++)
	//{
	//	if (m_ValueList[i]->GetWidget()->GetEnable())
	//	{
	//		count++;
	//	}
	//}

	auto iter2 = m_ValueList.begin();
	auto end2 = m_ValueList.end();

	for (; iter2 != end2;)
	{
		if (!(*iter2)->GetWidget()->GetEnable())
		{
			++iter2;
			continue;
		}
		(*iter2)->SetPos(m_BuffFirstPos.x+m_TextOffSet.x+(count*20), 130.f);
		iter2++;
		count++;
	}
	count = 0;

	for (int i = 0; i < m_ValueList.size(); i++)
	{
		ConvertText(ArrTemp[i], m_ValueList[i]);
	}
}

void CCharacter::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CCharacter::UpdateStatus()
{
	ArrTemp = GetBuffArr();
	for (int i = 0; i < (int)Buff::Max; i++)
	{
		if (ArrTemp[i] <= 0) { //
			m_StatusList[i]->GetWidget()->SetEnable(false);
			m_ValueList[i]->GetWidget()->SetEnable(false);
		}
		else {
			m_StatusList[i]->GetWidget()->SetEnable(true);
			m_ValueList[i]->GetWidget()->SetEnable(true);
		}
	}
}

void CCharacter::ConvertText(int Value, CSharedPtr<class CWidgetComponent> TextWiz)
{
	char Text[256] = {};
	sprintf_s(Text, "%d", Value);

	TCHAR Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);
	TextWiz->GetWidget<CText>()->SetText(Unicode);
}

void CCharacter::TestCallback()
{
	MessageBox(nullptr, TEXT("2"), TEXT("a"), MB_OK);
}
