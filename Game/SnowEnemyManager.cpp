#include "stdafx.h"
#include "SnowEnemyManager.h"
#include "SnowEnemy.h"

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
		int randIndex = rand() % m_spawnPoints.size();
		Vector3 spawnPos = m_spawnPoints[randIndex];

		spawnPos.x += Random(-50.0f, 50.0f);
		spawnPos.z += Random(-50.0f, 50.0f);
		SnowEnemy->SetPosition(spawnPos);
		SnowEnemy->m_spawnPos=true;
	}	
}

float SnowEnemyManager::Random(float min, float max)
{
	return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}







