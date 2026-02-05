#include "stdafx.h"
#include "DropItemsManager.h"
#include "src/Actor/Object/Item/DropItems/DropItems.h"
#include "ObjectPool.h"

namespace
{
	int NONE = 0;
}

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
	if(itemType== NONE)
	{
		//アイテム無しなら処理を抜ける
		return;
	}
	//ドロップアイテムをプールから取得
	auto dropItem = m_dorpItemsPool.AtkSpawn();
	if (dropItem)
	{
		//取得したドロップアイテムの初期化
		dropItem->SetDropItem(position, itemType);
	}
}

