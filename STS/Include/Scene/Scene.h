#pragma once
#include "../GameInfo.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/WidgetComponent.h"
#include "../GameObject/MapIconObject.h"
#include "../GameObject/CameraObject.h"

class CScene
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();

private:
	class CSceneResource* m_Resource;
	class CCamera* m_Camera;
	class CSceneCollision* m_Collision;

protected:
	std::list<CSharedPtr<class CGameObject>>	 m_ObjList[(int)ERender_Layer::Max];
	//이 오브젝트 목록을 이용해 씬을 그려내고 있다. 매 프레임마다 y소팅, 혹은 정렬을 해주어야 한다.
	std::list<CSharedPtr<CWidgetComponent>>	m_WidgetComponentList;
	CSharedPtr<class CGameObject> m_Player;
	CSharedPtr<class CCameraObject> m_CameraObj;
	
	CSharedPtr<class CGameObject> m_Map;
	CSharedPtr<class CTileMap>	  m_TileMap;
	vector<CSharedPtr<CGameObject>> m_MonstersList;
	vector<CSharedPtr<CMapIconObject>> m_Stage;

	//CSharedPtr<CReward> m_CReward;
	CSharedPtr<class CWidgetWindow> m_Reward;

	std::vector<CSharedPtr<CWidgetWindow>>	m_vecWidgetWindow;
	bool m_StartGame;
	bool m_IsBattle;
public:
	std::list<CSharedPtr<class CGameObject>>	 m_CardList;
	bool m_SceneUsedCard;

	bool m_BlackLayerSwitch;
	bool m_MapLayerSwitch;

	bool m_ShopLayerSwitch;
	bool m_RewardSwitch;

	bool m_RestSwitch;
	bool m_DefeatSwitch;
	bool m_ClearSwitch;
public:
	bool GetGameStart() {
		return m_StartGame;
	}
	void SetGameStart(bool Enable) {
		m_StartGame = Enable;
	}
	class CSceneCollision* GetCollision() const
	{
		return m_Collision;
	}

	class CCamera* GetCamera() const
	{
		return m_Camera;
	}

	class CSceneResource* GetSceneResource() const
	{
		return m_Resource;
	}

	class CGameObject* GetPlayer() const
	{
		return m_Player;
	}
	//class CGameObject* GetMonster() const
	//{
	//	return m_vecMonsters;
	//}

	class CGameObject* GetMap() const
	{
		return m_Map;
	}

	class CTileMap* GetTileMap()	const
	{
		return m_TileMap;
	}
	class CCameraObject* GetCameraObj() const
	{
		return m_CameraObj;
	}
	void SetTileMap(class CTileMap* TileMap);
	void SetPlayer(class CGameObject* Player);
	void SetCameraObj(class CCameraObject* Camera);
	void SetMap(class CGameObject* Map);

	void AddWidgetComponent(CWidgetComponent* Widget)
	{
		m_WidgetComponentList.push_back(Widget);
	}
	void AddStage(CMapIconObject* stage)
	{
		m_Stage.push_back(stage);
	}
	void SetStageIcon(bool Enable);
	void StageSort();

	vector<CSharedPtr<CGameObject>> GetMonsters() const
	{
		return m_MonstersList;
	}
	void AddMonsters(CGameObject* Mon) 
	{
		m_MonstersList.push_back(Mon);
	}
	bool CheckMonsters();
	void MonstersBuffControl ();

	void SetIsBattle(bool Enable) {
		m_IsBattle = Enable;
	}
	bool GetIsBattle()
	{
		return m_IsBattle;
	}


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	void SetUseCard(bool Enable)
	{
		m_SceneUsedCard = Enable;
	}
	void SetBlackSwitch(bool Enable)
	{
		m_BlackLayerSwitch = Enable;
	}
	bool GetBlackSwitch()
	{
		return m_BlackLayerSwitch;
	}
	void SetMapSwitch(bool Enable)
	{
		m_MapLayerSwitch = Enable;
	}
	bool GetMapSwitch()
	{
		return m_MapLayerSwitch;
	}
	void SetShopSwitch(bool Enable)
	{
		m_ShopLayerSwitch = Enable;
	}
	bool GetShopSwitch()
	{
		return m_ShopLayerSwitch;
	}
	void SetRewardSwitch(bool Enable)
	{
		m_RewardSwitch = Enable;
	}
	bool GetRewardSwitch()
	{
		return m_RewardSwitch;
	}
	void SetRestSwitch(bool Enable)
	{
		m_RestSwitch = Enable;
	}
	bool GetRestSwitch()
	{
		return m_RestSwitch;
	}
	void SetDefeatSwitch(bool Enable)
	{
		m_DefeatSwitch = Enable;
	}
	bool GetDefeatSwitch()
	{
		return m_DefeatSwitch;
	}
	void SetClearSwitch(bool Enable)
	{
		m_ClearSwitch = Enable;
	}
	bool GetClearSwitch()
	{
		return m_ClearSwitch;
	}
	void GameSet();

	CSharedPtr<class CWidgetWindow> GetReward(){
		return m_Reward;
	}
public:
	template <typename T>
	T* CreateObject(const std::string& Name = "GameObject") //Name = 디폴트인자로 해놓음 이름 안지으면 저걸로 해둠
	{
		T* Obj = new T;

		Obj->SetName(Name);
		Obj->m_Scene = this;

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		m_ObjList[(int)Obj->GetRenderLayer()].push_back((CGameObject*)Obj);

		return Obj;
	}
	//template <typename T>
	//T* CreateCard(const std::string& Name = "Card") //Name = 디폴트인자로 해놓음 이름 안지으면 저걸로 해둠
	//{
	//	T* Obj = new T;

	//	Obj->SetName(Name);
	//	Obj->m_Scene = this;

	//	if (!Obj->Init())
	//	{
	//		SAFE_DELETE(Obj);
	//		return nullptr;
	//	}

	//	m_CardList[(int)Obj->GetRenderLayer()].push_back((CGameObject*)Obj);

	//	return Obj;
	//}

	template <typename T>
	T* CreateWidgetWindow(const std::string& Name = "Window")
	{
		T* Window = new T;

		Window->SetName(Name);
		Window->m_Scene = this;

		if (!Window->Init())
		{
			SAFE_DELETE(Window);
			return nullptr;
		}

		m_vecWidgetWindow.push_back(Window);

		return (T*)Window;
	}

	template <typename T>
	T* FindWidget(const std::string& Name)
	{
		size_t	Size = m_vecWidgetWindow.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecWidgetWindow[i]->GetName() == Name)
				return (T*)m_vecWidgetWindow[i].Get();
		}

		return nullptr;
	}

private:
	static bool SortY(const CSharedPtr<class CGameObject>& Src, const CSharedPtr<class CGameObject>& Dest);
	static bool SortYWidgetComponent(const CSharedPtr<class CWidgetComponent>& Src, const CSharedPtr<class CWidgetComponent>& Dest);
	static bool SortWidget(const CSharedPtr<CWidgetWindow>& Src, const CSharedPtr<CWidgetWindow>& Dest);
	static bool SortCard(const CSharedPtr<class CGameObject>& Src, const CSharedPtr<class CGameObject>& Dest);
	static bool SortCard2(const CSharedPtr<class CGameObject>& Src, const CSharedPtr<class CGameObject>& Dest);
};

