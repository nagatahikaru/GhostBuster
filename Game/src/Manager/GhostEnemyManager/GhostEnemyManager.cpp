#include "stdafx.h"
#include "GhostEnemyManager.h"
#include "src/Actor/Character/Enemy/GhostEnemy/GhostEnemy.h"
#include "ObjectPool.h"
#include "src/UI/InGameUI/InGameUI.h"
#include "src/Actor/Character/Player/Player.h"


namespace {
	const Vector3 ENEMY_BASE_SPAWN_POS[GhostEnemyBaseSpawnPosNum] = {
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
	m_player = Player::GetInstance();
	return true;
}

void GhostEnemyManager::Update()
{
	if (!m_inGameUI)
	{
		m_inGameUI = FindGO<InGameUI>("inGameUI");
		return;
	}
	if (m_inGameUI->GetSBlackout())
	{
		return;
	}
	//敵の再生処理
	Regeneration();		
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
		ghostEnemys->SetEnemyExistence(true);
		ghostEnemys->OnSpawn(spawnPos);
	}
}