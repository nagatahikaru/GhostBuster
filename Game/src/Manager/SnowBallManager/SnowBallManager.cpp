#include "stdafx.h"
#include "SnowBallManager.h"
#include "src/Actor/Object/Item/SnowBall/SnowBall.h"
#include "ObjectPool.h"


SnowBallManager::SnowBallManager()
{

}

SnowBallManager::~SnowBallManager()
{
	m_snowBallPool.Clear();
}

bool SnowBallManager::Start()
{
	//雪玉プールの初期化
	m_snowBallPool.Init(30, "snowBall");
	return true;
}

void SnowBallManager::Fire(const Vector3& pos, const Vector3& dir, const Quaternion& rot)
{
	//雪玉をプールから取得
	auto snowBall = m_snowBallPool.AtkSpawn();

	//雪玉の発射処理
	//取得した雪玉の初期化
	//pos:発射位置, dir:発射方向, speed:発射速度, rot:回転
	if (snowBall) {
		snowBall->Fire(pos, dir, 3000.0f, rot);
	}
}


 