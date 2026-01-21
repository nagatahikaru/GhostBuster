#include "stdafx.h"
#include "SnowEnemyManager.h"
#include "SnowEnemy.h"
#include "ObjectPool.h"
#include "UI/InGameUI/InGameUI.h"


namespace {
	const Vector3 ENEMY_BASE_SPAWN_POS[SnowEnemyBaseSpawnPosNum] = {
		//ポジションをランダムで決定するための基準点
		{358.0f,-466.0f,-3855.0f},
		{-967.0f,139.0f,0.0f},
		{-4841.0f,-466.0f,234.0f},
		{-4951.0f,-466.0f,-2317.0f},
		{808.0f,-2.0f,3074.0f},
		{2904.0f,-466.0f,3912.0f},
		{-1307.0f,-466.0f,5312.0f},
		{4443.0f,-78.0f,818.0f}
	};
}


SnowEnemyManager::SnowEnemyManager()
{
	
}

	

SnowEnemyManager::~SnowEnemyManager()
{
	// メモリ解放
	m_snowEnemyPool.Clear();
}

bool SnowEnemyManager::Start()
{
	// オブジェクトプールの初期化
	m_snowEnemyPool.Init(10, "snowEnemy");
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	return true;
}

void SnowEnemyManager::Update()
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
	//敵の再生処理
	Regeneration();
}


void SnowEnemyManager::Regeneration()
{	
		// スポーン間隔をランダムに設定
		if (m_spawnTimeFrag)
		{
			m_spawnInterval = (rand() % 10) + 1;
			m_spawnTimeFrag = false;
		}
		// オブジェクトプールから敵をスポーン
		auto snowEnemys = m_snowEnemyPool.Spawn(m_spawnInterval, m_elapseTime);

		// 敵の出現位置をランダムに設定
		if (snowEnemys) {
			//ランダムな出現位置
			// 出現位置の基準点をランダムで決定
			int baseSpawnPosNum = rand() % SnowEnemyBaseSpawnPosNum;

			// 出現位置の基準点を設定
			m_spawnPos = ENEMY_BASE_SPAWN_POS[baseSpawnPosNum];
			Vector3 spawnPos = m_spawnPos;

			// 基準点から半径250の円範囲内でランダムに出現位置を決定
			float angle = (rand() % 360) * 3.1415f / 180.0f;
			float radius = rand() % 250;
			spawnPos.x += cosf(angle) * radius;
			spawnPos.z += sinf(angle) * radius;
			snowEnemys->m_existence = true;
			snowEnemys->OnSpawn(spawnPos);
		}
	
}
