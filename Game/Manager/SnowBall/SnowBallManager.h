#pragma once
#include "ObjectPool.h"

class SnowBall;


class SnowBallManager:public IGameObject
{
public:
	SnowBallManager();
	~SnowBallManager();
	bool Start() override;
	void Update() override {}
	void Fire(const Vector3& pos, const Vector3& dir, const Quaternion& rot);

private:
	ObjectPool<SnowBall> m_snowBallPool;



};

