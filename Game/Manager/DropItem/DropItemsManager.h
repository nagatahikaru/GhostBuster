#pragma once
#include "UI/InGameUI/InGameUI.h"
#include "GameCamera.h"
#include "ObjectPool.h"
class DropItems;

class DropItemsManager : public IGameObject
{
public:
	DropItemsManager();
	~DropItemsManager() override;
	bool Start() override;
	void Update() override;
	void DropItemSet(const Vector3& position, int itemType);
private:
	ObjectPool<DropItems> m_dorpItemsPool;
	int m_maxDropItemNum = 20;
	int m_dorpItemType = 0; //ドロップアイテムの種類
	int m_snowballItem = 1; //スノーボールアイテムの種類
	int m_sterItem = 2; //スターアイテムの種類
	int m_mushroomItem = 3; //キノコアイテムの種類
	GameCamera* m_gameCamera;
	InGameUI* m_inGameUI;
};

