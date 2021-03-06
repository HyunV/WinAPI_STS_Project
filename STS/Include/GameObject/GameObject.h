#pragma once
#include "../Ref.h"
#include "../Animation/Animation.h"
#include "../Widget/WidgetComponent.h"

class CGameObject :
	public CRef //스마트 포인터 상속받기
{
	friend class CScene; //오로지 씬만 접근 가능하다.
	friend class CInput;

protected:
	CGameObject();
	CGameObject(const CGameObject& Obj);
	virtual ~CGameObject();

protected:
	class CScene* m_Scene;


protected:
	ERender_Layer m_RenderLayer;
	Vector2 m_PrevPos;
	Vector2 m_Move;
	Vector2	m_Pos;
	Vector2 m_Size;
	Vector2 m_Pivot;
	CSharedPtr<class CTexture> m_Texture;
	CAnimation* m_Animation;
	float m_TimeScale;
	float m_MoveSpeed;
	std::list<CSharedPtr<class CCollider>> m_ColliderList;
	std::list<CSharedPtr<CWidgetComponent>>	m_WidgetComponentList;

	//플레이어, 적 이동관련 애니메이션
	bool m_MoveObject;
	float m_MovingObject;
	float m_DirValue;

	//에너지
	int m_Energy;
	int m_MaxEnergy;
	bool m_UsedCard;

	//공격여부
	bool m_EnableAttack;
	bool m_AttackCard;
	int m_Shield; //방어도

	//중력 관련
	bool		m_PhysicsSimulate; //물리시뮬레이션 작동 시킬것인지 여부
	bool		m_Ground;	// 땅을 밟고 있는 상태인지 아닌지
	float		m_GravityAccel; 
	float		m_FallTime; //물체가 떨어지는 시간(몇 초동안 떨어지냐)
	float		m_FallStartY; //어느 지점에서 y축으 로 떨어지고 있냐
	bool		m_Jump;
	float		m_JumpVelocity; //점프 속도

public:
	class CCollider* FindCollider(const std::string& Name);

	ERender_Layer GetRenderLayer() const
	{
		return m_RenderLayer;
	}

	float GetTimeScale() const
	{
		return m_TimeScale;
	}
	const Vector2& GetPos() const
	{
		return m_Pos;
	}

	const Vector2& GetSize() const
	{
		return m_Size;
	}
	const Vector2& GetPivot() const
	{
		return m_Pivot;
	}
public: /////////////////애니메이션 관련////////////////////////////
	void SetMoveObject(bool Move)
	{
		m_MoveObject = Move;
	}
	void SetEnableAttack(bool Attack)
	{
		m_EnableAttack = Attack;
	}
	void AddShield(int Shield)
	{
		m_Shield += Shield;
	}
	void SetEnergy(int value) {
		m_Energy = value;
	}
	void SetMaxEnergy(int value) {
		m_MaxEnergy = value;
	}
	int GetEnergy() {
		return m_Energy;
	}
	int GetMaxEnergy() {
		return m_MaxEnergy;
	}
	void SetUsedCard(bool usedCard) {
		m_UsedCard = usedCard;
	}
	bool GetUsedCard() {
		return m_UsedCard;
	}
	void SetAttackCard(bool AttackCard)
	{
		m_AttackCard = AttackCard;
	}
	bool GetAttackCard() {
		return m_AttackCard;
	}
	//중력관련
public:
	void SetPhysicsSimulate(bool Physics)
	{
		m_PhysicsSimulate = Physics;
	}

	void SetGravityAccel(float Accel)
	{
		m_GravityAccel = Accel;
	}

	void SetJumpVelocity(float JumpVelocity)
	{
		m_JumpVelocity = JumpVelocity;
	}

	void Jump()
	{
		if (!m_Jump)
		{
			m_Jump = true;
			m_Ground = false;

			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y; //위치 y값 미리 저장해둠
		}
	}


public:
	void SetTimeScale(float Scale)
	{
		m_TimeScale = Scale;
	}

	void SetPos(float x, float y)
	{
		m_Pos.x = x;
		m_Pos.y = y;
	}
	void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}
	void SetSize(float x, float y)
	{
		m_Size.x = x;
		m_Size.y = y;
	}
	void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}
	void SetPivot(float x, float y)
	{
		m_Pivot.x = x;
		m_Pivot.y = y;
	}

	void SetPivot(const Vector2& Pivot)
	{
		m_Pivot = Pivot;
	}
public:
	void SetTexture(const std::string& Name);
	void SetTexture(class CTexture* Texture);
	void SetTexture(const std::string& Name, const TCHAR* FileName, 
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE
	void SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);
#else
	void SetTexture(const std::string& Name, 
		const std::vector<std::string>& vecFileName, const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);
#endif
	bool SetColorKey(unsigned char r, unsigned char g, unsigned char b,
		int Index = 0);
	bool SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b);

public:
	void CreateAnimation();
	void AddAnimation(const std::string& SequenceName, bool Loop = true,
		float PlayTime = 1.f, float PlayScale = 1.f,
		bool Reverse = false);
	void SetPlayTime(const std::string& Name, float PlayTime);
	void SetPlayScale(const std::string& Name, float PlayScale);
	void SetPlayLoop(const std::string& Name, bool Loop);
	void SetPlayReverse(const std::string& Name, bool Reverse);
	void SetCurrentAnimation(std::string& Name);
	void ChangeAnimation(const std::string& Name);
	bool CheckCurrentAnimation(const std::string& Name);

public:
	void MoveDir(const Vector2& Dir); //특정 방향 이동
	void Move(const Vector2& MoveValue); //어느 방향으로 (x, y) 로 이동해라
	void Move(float Angle); //특정 각도로 이동해라

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);



public:
	void SetCollisionEnable(bool Enable);



public:
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void(T::* Func)())
	{
		if (m_Animation) //애니메이션이 있을때만 처리
			m_Animation->SetEndFunction<T>(Name, Obj, Func);
	}

	template <typename T>
	void SetCurrentAnimationEndFunction(T* Obj, void(T::* Func)())
	{
		if (m_Animation)
			m_Animation->SetCurrentAnimationEndFunction<T>(Obj, Func);
	}

	template <typename T>
	void AddNotify(const std::string& Name, int Frame, T* Obj, void(T::* Func)())
	{
		if (m_Animation)
			m_Animation->AddNotify<T>(Name, Frame, Obj, Func);
	}

	template <typename T>
	T* AddCollider(const std::string& Name) //충돌체 이름 지어주면서 추가하기
	{
		T* Collider = new T;

		Collider->SetName(Name);
		Collider->m_Owner = this;
		Collider->m_Scene = m_Scene;

		if (!Collider->Init())
		{
			SAFE_DELETE(Collider);
			return nullptr;
		}

		m_ColliderList.push_back(Collider);

		return Collider;
	}

	CWidgetComponent* FindWidgetComponent(const std::string& Name)
	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == Name)
				return *iter;
		}

		return nullptr;
	}

	template <typename T>
	CWidgetComponent* CreateWidgetComponent(const std::string& Name)
	{
		CWidgetComponent* Widget = FindWidgetComponent(Name);

		if (Widget)
			return Widget;

		Widget = new CWidgetComponent;

		Widget->m_Owner = this;
		Widget->m_Scene = m_Scene;
		Widget->SetName(Name);

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		Widget->CreateWidget<T>(Name);

		m_WidgetComponentList.push_back(Widget);

		return Widget;
	}
};

