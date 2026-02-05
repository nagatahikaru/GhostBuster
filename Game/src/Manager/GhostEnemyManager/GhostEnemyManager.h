#pragma once
#include "src/UI/InGameUI/InGameUI.h"
#include "ObjectPool.h"
class GhostEnemy;

enum { GhostEnemyBaseSpawnPosNum = 8 };



class GhostEnemyManager:public IGameObject
{
public:
	GhostEnemyManager();
	~GhostEnemyManager();
	bool Start()override;
	void Update()override;
	void Regeneration();	


private:
	ObjectPool<GhostEnemy> m_ghostEnemyPool;
	float m_elapseTime = 0.0f;//経過時間
	bool m_spawnTimeFrag = true;//スポーン時間フラグ
	float m_spawnInterval = 0.0f;//スポーン間隔
	int m_randomNumber = 0;//ランダムナンバー
	Vector3 m_spawnPos;//スポーン位置
	Vector3 m_enemyBaseSpawnPos;//敵の基本スポーン位置
	InGameUI* m_inGameUI;
	Player* m_player;	
};

