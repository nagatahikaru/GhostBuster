#pragma once
#include "ObjectPool.h"
#include "src/UI/InGameUI/InGameUI.h"


class SnowEnemy;
class InGameUI;


enum { SnowEnemyBaseSpawnPosNum = 8};

class SnowEnemyManager:public IGameObject
{
public:
	SnowEnemyManager();
	~SnowEnemyManager();
	bool Start() override;
	void Update() override;
	void Regeneration();
	
	

private:
	ObjectPool<SnowEnemy> m_snowEnemyPool;
	float m_elapseTime = 0.0f;
	bool m_spawnTimeFrag = true;
	float m_spawnInterval = 0.0f;
	int m_randomNumber = 0;
	Vector3 m_spawnPos;
	Vector3 m_enemyBaseSpawnPos;
	InGameUI* m_inGameUI;
};

