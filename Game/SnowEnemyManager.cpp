#include "stdafx.h"
#include "SnowEnemyManager.h"
#include "SnowEnemy.h"
#include "ObjectPool.h"


namespace {
	const Vector3 ENEMY_BASE_SPAWN_POS[SnowEnemyBaseSpawnPosNum] = {
		//ポジションをランダムで決定するための基準点
		{-500.0f,1000.0f,-600.0f},
		{-700.0f,1000.0f,200.0f},
		{0.0f,1000.0f,800.0f},
		{0.0f,1000.0f,-800.0f},
		{300.0f,1000.0f,400.0f},
		{-300.0f,1000.0f,-400.0f},
		{700.0f,1000.0f,-200.0f},
		{500.0f,1000.0f,600.0f}
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
	return true;
}

void SnowEnemyManager::Update()
{
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
