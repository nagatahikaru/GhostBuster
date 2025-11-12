#include "stdafx.h"
#include "GhostEnemyManager.h"
#include "GhostEnemy.h"
#include "ObjectPool.h"

namespace {
	const Vector3 ENEMY_BASE_SPAWN_POS[GhostEnemyBaseSpawnPosNum] = {
		//ポジションをランダムで決定するための基準点
		{1000.0f,800.0f,1000.0f},
		{-1000.0f,800.0f,1000.0f},
		{1000.0f,800.0f,-1000.0f},
		{-1000.0f,800.0f,-1000.0f},
		{0.0f,800.0f,1000.0f},
		{0.0f,800.0f,-1000.0f},
		{1000.0f,800.0f,0.0f},
		{-1000.0f,800.0f,0.0f},
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

	// 出現位置の基準点をランダムで決定
	int baseSpawnPosNum = rand() % GhostEnemyBaseSpawnPosNum;

	// 出現位置の基準点を設定
	m_spawnPos = ENEMY_BASE_SPAWN_POS[baseSpawnPosNum];

	return true;
}

void GhostEnemyManager::Update()
{
	//敵の再生処理
	Regeneration();
}


void GhostEnemyManager::Regeneration()
{
	// スポーン間隔をランダムに設定
	if (m_spawnTimeFrag)
	{
		m_spawnInterval = rand() % 10;
		m_spawnTimeFrag = false;
	}
	// オブジェクトプールから敵をスポーン
	auto ghostEnemy = m_ghostEnemyPool.Spawn(m_spawnInterval, m_elapseTime);

	// 敵の出現位置をランダムに設定
	if (ghostEnemy) {
		//ランダムな出現位置
		Vector3 spawnPos = m_spawnPos;

		spawnPos.x = (rand() % 501) - 250;
		spawnPos.z = (rand() % 501) - 250;
		ghostEnemy->m_IsSpawn = true;
		ghostEnemy->SetPosition(spawnPos);

	}
}