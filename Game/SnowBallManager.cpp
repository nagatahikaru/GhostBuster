#include "stdafx.h"
#include "SnowBallManager.h"
#include "SnowBall.h"
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
	m_snowBallPool.Init(30, "snowBall");
	return true;
}

void SnowBallManager::Fire(const Vector3& pos, const Vector3& dir, const Quaternion& rot)
{
	auto snowBall = m_snowBallPool.AtkSpawn();

	if (snowBall) {
		snowBall->Fire(pos, dir, 3000.0f, rot);
	}
}
 