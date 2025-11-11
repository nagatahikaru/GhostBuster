#include "stdafx.h"
#include "SnowEnemyManager.h"
#include "SnowEnemy.h"


namespace {
	const Vector3 ENEMY_BASE_SPAWN_POS[EnemyBaseSpawnPosNum] = {
		{700.0f,1000.0f,-200.0f},
		{500.0f,1000.0f,600.0f}
	};
}


SnowEnemyManager::SnowEnemyManager()
{
	
}

	

SnowEnemyManager::~SnowEnemyManager()
{
	m_snowEnemyPool.Clear();
}

bool SnowEnemyManager::Start()
{
	m_snowEnemyPool.Init(16, "snowEnemy");

	int baseSpawnPosNum = rand() % EnemyBaseSpawnPosNum;

	m_spawnPos = ENEMY_BASE_SPAWN_POS[baseSpawnPosNum];
	
	return true;
}

void SnowEnemyManager::Update()
{
	Regeneration();
}


void SnowEnemyManager::Regeneration()
{
	if (m_spawnTimeFrag)
	{
		m_spawnInterval = rand() % 10;
		m_spawnTimeFrag = false;
	}
	auto SnowEnemy= m_snowEnemyPool.Spawn(m_spawnInterval, m_elapseTime);

	if (SnowEnemy) {
		// ?? ƒ‰ƒ“ƒ_ƒ€‚ÈoŒ»ˆÊ’u
		Vector3 spawnPos = m_spawnPos;

		spawnPos.x = (rand() % 501) - 250;
		spawnPos.z = (rand() % 501) - 250;
		SnowEnemy->m_IsSpawn = true;
		SnowEnemy->SetPosition(spawnPos);
		
	}	
}









