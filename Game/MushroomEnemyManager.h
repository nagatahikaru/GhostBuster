#pragma once
#include "ObjectPool.h"

class MushroomEnemy;

enum { MushroomEnemyBaseSpawnPosNum = 8 };

class MushroomEnemyManager :public IGameObject
{
public:
	MushroomEnemyManager();
	~MushroomEnemyManager()override;
	bool Start()override;
	void Update()override;
	void Regeneration();

private:
	ObjectPool<MushroomEnemy> m_mushroomEnemyPool;
	float m_elapseTime = 0.0f;//経過時間
	bool m_spawnTimeFrag = true;//スポーン時間フラグ
	float m_spawnInterval = 0.0f;//スポーン間隔
	int m_randomNumber = 0;//ランダムナンバー
	Vector3 m_spawnPos;//スポーン位置
	Vector3 m_enemyBaseSpawnPos;//敵の基本スポーン位置
};

