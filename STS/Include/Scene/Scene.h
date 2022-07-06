#pragma once
#include "../GameInfo.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/WidgetComponent.h"

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
	CSharedPtr<class CGameObject> m_CameraObj;
	CSharedPtr<class CGameObject> m_Monster;
	CSharedPtr<class CGameObject> m_Map;
	CSharedPtr<class CTileMap>		m_TileMap;

	std::vector<CSharedPtr<CWidgetWindow>>	m_vecWidgetWindow;
	bool m_StartGame;
public:
	std::list<CSharedPtr<class CGameObject>>	 m_CardList;
	bool m_SceneUsedCard;

	bool m_BlackLayerSwitch;
	bool m_MapLayerSwitch;
	bool m_ShopLayerSwitch;

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
	class CGameObject* GetMonster() const
	{
		return m_Monster;
	}
	class CGameObject* GetMap() const
	{
		return m_Map;
	}

	class CTileMap* GetTileMap()	const
	{
		return m_TileMap;
	}
	class CGameObject* GetCameraObj() const
	{
		return m_CameraObj;
	}

	void SetTileMap(class CTileMap* TileMap);
	void SetPlayer(class CGameObject* Player);
	void SetCameraObj(class CGameObject* Camera);
	void SetMonster(class CGameObject* Monster);
	void SetMap(class CGameObject* Map);

	void AddWidgetComponent(CWidgetComponent* Widget)
	{
		m_WidgetComponentList.push_back(Widget);
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

