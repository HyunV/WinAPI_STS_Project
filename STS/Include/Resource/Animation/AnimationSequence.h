#pragma once
//�ִϸ��̼� ��� �ϳ��ϳ��� �����͸� ������ �ִ� Ŭ����
//������������ �����ؼ� ���ű� ������ Ref�� ����Ѵ�.
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
    CSharedPtr<CTexture>  m_Texture; //����� �ؽ�ó�� ��� �־�� �Ѵ� �� �����̹���.(�ȼ������� �����ϰ� �ִ�.)
    std::vector<AnimationFrameData> m_vecFrame; //�ִϸ��̼� ������ ������: ���� ã�ư����� Start~End�� ������ ��������Ʈ�� ������ ���Ϳ� ����
    //(117x87) 3ĳ�� ��õ� �̹����� ���÷�
    //��ġ�� [0]:(0,0,59,87) [1](59,0,118,87) [2](118, 0, 177, 87)
    //�� �ؽ�ó�� �����ϴ� ������ �ִϸ��̼� �Ŵ������� ����
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

