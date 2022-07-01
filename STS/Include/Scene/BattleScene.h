#pragma once
#include "Scene.h"
#include "../GameObject/Card.h"
class CBattleScene :
    public CScene
{
    friend class CSceneManager;

protected:
    CBattleScene();
    virtual ~CBattleScene();

private:
    //CSharedPtr<class CMyMonster> m_Monster;

public:
    bool Init();
    void Update(float DeltaTime);
    vector<CCard*> m_MyHand;
private:
    void CreateAnimationSequence();
};

