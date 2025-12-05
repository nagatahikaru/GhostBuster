#include "stdafx.h"
#include "GhostEnemyManager.h"
#include "GhostEnemy.h"
#include "ObjectPool.h"
#include "UI/InGameUI/InGameUI.h"


namespace {
	const Vector3 ENEMY_BASE_SPAWN_POS[GhostEnemyBaseSpawnPosNum] = {
		//ポジションをランダムで決定するための基準点
		{1000.0f,900.0f,1000.0f},
		{-1000.0f,900.0f,1000.0f},
		{1000.0f,900.0f,-1000.0f},
		{-1000.0f,900.0f,-1000.0f},
		{0.0f,900.0f,1000.0f},
		{0.0f,900.0f,-1000.0f},
		{1000.0f,900.0f,0.0f},
		{-1000.0f,900.0f,0.0f},
	};
}


GhostEnemyManager::GhostEnemyManager()
{

}



GhostEnemyManager::~GhostEnemyManager()
{
	// メモリ解放
	m_ghostEnemyPool.Clear();
}

bool GhostEnemyManager::Start()
{
	// オブジェクトプールの初期化
	m_ghostEnemyPool.Init(10, "ghostEnemy");
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	return true;
}

void GhostEnemyManager::Update()
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

void GhostEnemyManager::Reclaim()
{
	//敵死亡時の回収処理
	auto reclaimed = m_ghostEnemyPool.Reclaim();
	
	for (auto enemy : reclaimed) {
		// 例：スコア加算処理
		m_inGameUI->AddScore(30);
	}	
}


void GhostEnemyManager::Regeneration()
{
	// スポーン間隔をランダムに設定
	if (m_spawnTimeFrag)
	{
		m_spawnInterval = (rand() % 10)+1;
		m_spawnTimeFrag = false;
	}
	// オブジェクトプールから敵をスポーン
	auto ghostEnemys = m_ghostEnemyPool.Spawn(m_spawnInterval, m_elapseTime);

	// 敵の出現位置をランダムに設定
	if (ghostEnemys) {
		//ランダムな出現位置
		// 出現位置の基準点をランダムで決定
		int baseSpawnPosNum = rand() % GhostEnemyBaseSpawnPosNum;

		// 出現位置の基準点を設定
		m_spawnPos = ENEMY_BASE_SPAWN_POS[baseSpawnPosNum];
		Vector3 spawnPos = m_spawnPos;

		// 基準点から半径250の円範囲内でランダムに出現位置を決定
		float angle = (rand() % 360) * 3.1415f / 180.0f;
		float radius = rand() % 250;
		spawnPos.x += cosf(angle) * radius;
		spawnPos.z += sinf(angle) * radius;
		ghostEnemys->m_existence = true;
		ghostEnemys->OnSpawn(spawnPos);
	}
}