#include "stdafx.h"
#include "DropItemsManager.h"
#include "Object/Item/DropItems/DropItems.h"
#include "ObjectPool.h"

DropItemsManager::DropItemsManager()
{
}

DropItemsManager::~DropItemsManager()
{
	// メモリ解放
	m_dorpItemsPool.Clear();
}
bool DropItemsManager::Start()
{		
	//ドロップアイテムプールの初期化
	m_dorpItemsPool.Init(m_maxDropItemNum,"dropitems");
	return true;
}

void DropItemsManager::DropItemSet(const Vector3& position, int itemType)
{
	//ドロップアイテムをプールから取得
	auto dropItem = m_dorpItemsPool.AtkSpawn();
	if (dropItem)
	{
		//取得したドロップアイテムの初期化
		dropItem->SetDropItem(position, itemType);
	}
}

