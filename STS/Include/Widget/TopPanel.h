#pragma once
#include "WidgetWindow.h"
#include "../GameInfo.h"
class CTopPanel :
    public CWidgetWindow 
{
    friend class CScene;

protected:
    CTopPanel();
    virtual ~CTopPanel();

private:
    CSharedPtr<class CText> m_PlayerName; //�̸�
    CSharedPtr<class CText> m_Job; //����
    
    
    CSharedPtr<class CText> m_LifeUI; //ü��

    CSharedPtr<class CText> m_GoldUI; //���
    CSharedPtr<class CText> m_FloorUI; //���� �� ��
    //std::vector<CSharedPtr<class CButton>> m_Potion; //����

    CSharedPtr<class CText> m_DeckCount;

    CSharedPtr<class CText> m_Energy;

    CSharedPtr<class CText> LCardCount;
    CSharedPtr<class CText> RCardCount;

    bool TurnOff;

    //������, ���� ī�� ����(����), ����ī�� ����(����) �� ����(��ư) ,�ȹ�ư(��ư) ���̱� ����
    
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

};

