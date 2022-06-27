#pragma once
#include "Scene.h"
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

private:
    void CreateAnimationSequence();
};

