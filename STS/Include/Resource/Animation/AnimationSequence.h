#pragma once
//애니메이션 모션 하나하나의 데이터를 가지고 있는 클래스
//여러군데에서 공유해서 쓸거기 때문에 Ref를 상속한다.
#include "../../Ref.h"
#include "../Texture/Texture.h"

class CAnimationSequence :
    public CRef
{
    friend class CAnimationManager;
    friend class CAnimationInfo;

private:
    CAnimationSequence();
    ~CAnimationSequence();

private:
    CSharedPtr<CTexture>  m_Texture; //사용할 텍스처를 들고 있어야 한다 즉 원본이미지.(픽셀단위로 저장하고 있다.)
    std::vector<AnimationFrameData> m_vecFrame; //애니메이션 프레임 데이터: 원본 찾아가보면 Start~End로 나누어 스프라이트의 갯수를 벡터에 저장
    //(117x87) 3캐릭 루시드 이미지를 예시로
    //위치가 [0]:(0,0,59,87) [1](59,0,118,87) [2](118, 0, 177, 87)
    //이 텍스처를 정제하는 과정은 애니메이션 매니저에서 진행
public:
    CTexture* GetTexture()    const
    {
        return m_Texture;
    }

    ETexture_Type GetTextureType()  const
    {
        return m_Texture->GetTextureType();
    }

    const AnimationFrameData& GetFrame(int Index)   const
    {
        return m_vecFrame[Index];
    }

    int GetFrameCount() const
    {
        return (int)m_vecFrame.size();
    }

public:
    void AddFrame(const Vector2& Start, const Vector2& End);
    void AddFrame(float PosX, float PosY, float SizeX, float SizeY);
};

