#pragma once
#include "../Ref.h"
#include "../Animation/Animation.h"
#include "../Widget/WidgetComponent.h"
#include "../CardFlag.h"


class CGameObject :
	public CRef //����Ʈ ������ ��ӹޱ�
{
	friend class CScene; //������ ���� ���� �����ϴ�.
	friend class CInput;

protected:
	CGameObject();
	//CGameObject(const CGameObject& Obj);
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

	Vector2 m_OriginPos;
	//ĳ���� ��� ����, �ӵ�
	//float m_AttackDir;
	//float m_AttackSpeed;

	//�÷��̾�, �� �̵����� �ִϸ��̼�
	bool m_MoveObject;
	float m_MovingObject;
	float m_DirValue;

	float m_Time;

	//������
	int m_MaxHP;
	int m_HP;

	int m_Energy;
	int m_MaxEnergy;
	bool m_UsedCard;
	bool m_CardControl;

	//���ݿ���
	bool m_EnableAttack;
	bool m_AttackCard;
	int m_Shield; //��
	
	//���� ������ ����
	bool m_EnableDamaged;

	//ī�� ������Ʈ ����
	bool m_SelectedCard;
	bool m_ExtinctCard;

	//���� �̻�
		//����
	int m_Atk; //����, ���Ҿ���
	int m_Dex; //��ø, ���� ����
	int m_Demon; //����, ���� ����
	int m_Gate; //�ٸ�����Ʈ, ���� �ʸ�

	int m_Rage; //���� ����(���Ҿ���)
	int m_Ritual; //�ǽ�(���� ����)

	//�����
	int m_Vulnerable; //���(������)
	int	m_Weak;//��ȭ(������)

	int m_BuffArr[(int)Buff::Max]; //���� ���� �迭

	bool m_isDeath;

	//�߷� ����
	bool		m_PhysicsSimulate; //�����ùķ��̼� �۵� ��ų������ ����
	bool		m_Ground;	// ���� ��� �ִ� �������� �ƴ���
	float		m_GravityAccel; 
	float		m_FallTime; //��ü�� �������� �ð�(�� �ʵ��� ��������)
	float		m_FallStartY; //��� �������� y���� �� �������� �ֳ�
	bool		m_Jump;
	float		m_JumpVelocity; //���� �ӵ�



public:
	class CCollider* FindCollider(const std::string& Name);

	ERender_Layer GetRenderLayer() const
	{
		return m_RenderLayer;
	}
	void SetRenderLayer(ERender_Layer Layer)
	{
		m_RenderLayer = Layer;
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
public: /////////////////�ִϸ��̼� ����////////////////////////////
	void SetMoveObject(bool Move)
	{
		m_MoveObject = Move;
	}

	int* GetBuffArr() {
		return m_BuffArr;
	}

	//���� ���� �̰� true�̸� �ִϸ��̼� �۵�
	void SetEnableAttack(bool Enable)
	{
		m_EnableAttack = Enable;
	}
	void SetEnableDamaged(bool Enable)
	{
		m_EnableDamaged = Enable;
	}

	//���� ����
	virtual void AddShield(int Shield);

	void ClearShield() {
		m_Shield = 0;
	}
	int GetShield() {
		return m_Shield;
	}
	void SetShield(int value) {
		m_Shield = value;
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
	void SetSelectedCard(bool Enable)
	{
		m_SelectedCard = Enable;
	}
	bool GetSelectedCard()
	{
		return m_SelectedCard;
	}
	void SetCardControl(bool Enable)
	{
		m_CardControl = Enable;
	}
	bool GetCardControl()
	{
		return m_CardControl;
	}
	int GetHP() {
		return m_HP;
	}
	void SetHP(int Value)
	{
		m_HP = Value;
	}
	int GetMaxHP() {
		return m_MaxHP;
	}
	void SetMaxHP(int Value)
	{
		m_MaxHP = Value;
	}
	bool GetIsDeath() {
		return m_isDeath;
	}
	void SetIsDeath(bool Enable) 
	{
		m_isDeath = Enable;
	}
	bool GetIsExtinctCard() {
		return m_ExtinctCard;
	}
	void SetIsExtinctCard(bool Enable) {
		m_ExtinctCard = Enable;
	}
		
	void ClearBuffArr();
	//�߷°���
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
			m_FallStartY = m_Pos.y; //��ġ y�� �̸� �����ص�
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
		m_OriginPos.x = x;
		m_OriginPos.y = y;
	}
	void SetPrevPos(float x, float y)
	{
		m_PrevPos.x = x;
		m_PrevPos.y = y;
	}
	void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
		m_OriginPos = Pos;
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
	void MoveDir(const Vector2& Dir); //Ư�� ���� �̵�
	void Move(const Vector2& MoveValue); //��� �������� (x, y) �� �̵��ض�
	void Move(float Angle); //Ư�� ������ �̵��ض�

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
		if (m_Animation) //�ִϸ��̼��� �������� ó��
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
	T* AddCollider(const std::string& Name) //�浹ü �̸� �����ָ鼭 �߰��ϱ�
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

