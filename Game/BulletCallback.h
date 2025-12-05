#pragma once
#include <btBulletDynamicsCommon.h>

//“–‚½‚è”»’è—p
namespace nepen {
	enum enCollisionObject {
		enCollirionPlayer = 1,
		enCollirionEnemy = 2,
		enCollirionPlayerAtk = 3,
		enCollirionEnemyAtk = 4,
		enCollirionItem = 5,
		enCollirionStage = 6,
	};
}

struct BulletCallback : public btCollisionWorld::ConvexResultCallback
{
	bool m_isHit = false;
	btCollisionObject* m_me = nullptr;

	btScalar addSingleResult(
		btCollisionWorld::LocalConvexResult& convexResult,
		bool normalInWorldSpace) override
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != nepen::enCollirionPlayer
			&& convexResult.m_hitCollisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT)
		{
			return 0.0f;
		}
		m_isHit = true;
		return 0.0f;
	}
};
