#include "GameOver.h"

CGameOver::CGameOver()
{
    m_RenderLayer = ERender_Layer::Default;
    m_Time = 0.f;
}

CGameOver::~CGameOver()
{
}

bool CGameOver::Init()
{
    return true;
}

void CGameOver::Update(float DeltaTime)
{

}
