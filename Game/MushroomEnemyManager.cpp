#include "stdafx.h"
#include "MushroomEnemyManager.h"
#include "MushroomEnemy.h"
#include "ObjectPool.h"


namespace {
	const Vector3 ENEMY_BASE_SPAWN_POS[MushroomEnemyBaseSpawnPosNum] = {
		//ポジションをランダムで決定するための基準点
		{2000.0f,800.0f,2000.0f},
		{-2000.0f,800.0f,2000.0f},
		{2000.0f,800.0f,-2000.0f},
		{-2000.0f,800.0f,-2000.0f},
		{0.0f,800.0f,2000.0f},
		{0.0f,800.0f,-2000.0f},
		{2000.0f,800.0f,0.0f},
		{-2000.0f,800.0f,0.0f},
	};
}


MushroomEnemyManager::MushroomEnemyManager()
{

}



MushroomEnemyManager::~MushroomEnemyManager()
{
	// メモリ解放
	m_mushroomEnemyPool.Clear();
}

bool MushroomEnemyManager::Start()
{
	// オブジェクトプールの初期化
	m_mushroomEnemyPool.Init(10, "mushroomEnemy");

	// 出現位置の基準点をランダムで決定
	int baseSpawnPosNum = rand() % MushroomEnemyBaseSpawnPosNum;

	// 出現位置の基準点を設定
	m_spawnPos = ENEMY_BASE_SPAWN_POS[baseSpawnPosNum];

	return true;
}

void MushroomEnemyManager::Update()
{
	//敵の再生処理
	Regeneration();
}


void MushroomEnemyManager::Regeneration()
{
	// スポーン間隔をランダムに設定
	if (m_spawnTimeFrag)
	{
		m_spawnInterval = rand() % 10;
		m_spawnTimeFrag = false;
	}
	// オブジェクトプールから敵をスポーン
	auto mushroomEnemy = m_mushroomEnemyPool.Spawn(m_spawnInterval, m_elapseTime);

	// 敵の出現位置をランダムに設定
	if (mushroomEnemy) {
		//ランダムな出現位置
		Vector3 spawnPos = m_spawnPos;

		spawnPos.x = (rand() % 501) - 250;
		spawnPos.z = (rand() % 501) - 250;
		mushroomEnemy->m_IsSpawn = true;
		mushroomEnemy->SetPosition(spawnPos);

	}
}
