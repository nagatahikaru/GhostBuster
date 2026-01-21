#include "stdafx.h"
#include "DropItemsManager.h"
#include "DropItems.h"
#include "GameCamera.h"
#include "UI/InGameUI/InGameUI.h"
#include "Player.h"
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
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	//ドロップアイテムプールの初期化
	m_dorpItemsPool.Init(m_maxDropItemNum,"dropitems");
	return true;
}
void DropItemsManager::Update()
{
	if (!m_inGameUI)
	{
		m_inGameUI = FindGO<InGameUI>("inGameUI");
		return;
	}
	if (m_inGameUI->m_blackout)
	{
		return;
	}
	//ドロップアイテムプールの回収処理
	auto reclaimed = m_dorpItemsPool.Reclaim();
	for (auto item : reclaimed)
	{
		//スコア加算処理
		Player::GetInstance()->m_score+=(item->m_itemType * 100);
	}
}

void DropItemsManager::DropItemSet(const Vector3& position, int itemType)
{
	//ドロップアイテムをプールから取得
	DropItems* dropItem = m_dorpItemsPool.AtkSpawn();
	if (dropItem)
	{
		//取得したドロップアイテムの初期化
		dropItem->SetDropItem(position, itemType);
	}
}

