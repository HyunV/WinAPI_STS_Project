#pragma once

#include "../GameInfo.h"
class CTile
{
	friend class CTileMap;

private:
	CTile();
	~CTile();

private:
	class CScene* m_Scene;
	class CTileMap* m_Owner;
	CSharedPtr<class CTexture>	m_Texture;
	ETile_Option	m_Option;
	Vector2		m_Pos; // ��ġ
	Vector2		m_Size; // ũ��
	int			m_IndexX; //���� �ε���
	int			m_IndexY; // ���� �ε���
	int			m_Index; //�� �ε���
	int			m_TileFrame;
	Vector2		m_StartFrame;
	Vector2		m_EndFrame;

public:
	ETile_Option GetOption()	const
	{
		return m_Option;
	}

	const Vector2& GetPos()	const
	{
		return m_Pos;
	}

	const Vector2& GetSize()	const
	{
		return m_Size;
	}

public:
	void SetTileInfo(const Vector2& Pos, const Vector2& Size,
		int IndexX, int IndexY, int Index, class CTexture* Texture);
	void SetFrame(const Vector2& Start, const Vector2& End)
	{
		m_StartFrame = Start;
		m_EndFrame = End;
	}

	void SetTileOption(ETile_Option Option)
	{
		m_Option = Option;
	}

public:
	void Render(HDC hDC);
};

