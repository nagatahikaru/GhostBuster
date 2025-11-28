#include "stdafx.h"
#include "MushroomEnemyManager.h"
#include "MushroomEnemy.h"
#include "ObjectPool.h"
#include "GameCamera.h"
#include "UI/InGameUI/InGameUI.h"


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
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	return true;
}

void MushroomEnemyManager::Update()
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


void MushroomEnemyManager::Regeneration()
{
	// スポーン間隔をランダムに設定
	if (m_spawnTimeFrag)
	{
		m_spawnInterval = (rand() % 10) + 1;
		m_spawnTimeFrag = false;
	}
	// オブジェクトプールから敵をスポーン
	auto mushroomEnemys = m_mushroomEnemyPool.Spawn(m_spawnInterval, m_elapseTime);

	// 敵の出現位置をランダムに設定
	if (mushroomEnemys) {
		//ランダムな出現位置
		// 出現位置の基準点をランダムで決定
		int baseSpawnPosNum = rand() % MushroomEnemyBaseSpawnPosNum;

		// 出現位置の基準点を設定
		m_spawnPos = ENEMY_BASE_SPAWN_POS[baseSpawnPosNum];
		Vector3 spawnPos = m_spawnPos;

		// 基準点から半径250の円範囲内でランダムに出現位置を決定
		float angle = (rand() % 360) * 3.1415f / 180.0f;
		float radius = rand() % 250;
		spawnPos.x += cosf(angle) * radius;
		spawnPos.z += sinf(angle) * radius;
		mushroomEnemys->m_existence = true;
		mushroomEnemys->OnSpawn(spawnPos);
	}
}
