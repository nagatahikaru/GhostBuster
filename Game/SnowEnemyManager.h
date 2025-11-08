#pragma once
#include "ObjectPool.h"

class SnowEnemy;

enum { EnemyBaseSpawnPosNum = 2};

class SnowEnemyManager:public IGameObject
{
public:
	SnowEnemyManager();
	~SnowEnemyManager();
	bool Start() override;
	void Update() override;
	void Regeneration();
	//float Random(const float min, const float max);
	

private:
	ObjectPool<SnowEnemy> m_snowEnemyPool;
	float m_elapseTime = 0.0f;
	bool m_spawnTimeFrag = true;
	float m_spawnInterval = 0.0f;
	int m_randomNumber = 0;
	Vector3 m_spawnPos;
	Vector3 m_enemyBaseSpawnPos;
};

