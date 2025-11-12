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

	// 出現位置の基準点をランダムで決定
	int baseSpawnPosNum = rand() % SnowEnemyBaseSpawnPosNum;

	// 出現位置の基準点を設定
	m_spawnPos = ENEMY_BASE_SPAWN_POS[baseSpawnPosNum];
	
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
		m_spawnInterval = rand() % 10;
		m_spawnTimeFrag = false;
	}
	// オブジェクトプールから敵をスポーン
	auto SnowEnemy= m_snowEnemyPool.Spawn(m_spawnInterval, m_elapseTime);

	// 敵の出現位置をランダムに設定
	if (SnowEnemy) {
		//ランダムな出現位置
		Vector3 spawnPos = m_spawnPos;

		spawnPos.x = (rand() % 501) - 250;
		spawnPos.z = (rand() % 501) - 250;
		SnowEnemy->m_IsSpawn = true;
		SnowEnemy->SetPosition(spawnPos);
		
	}	
}
