#pragma once

class SnowEnemy;
class Player;

class SnowBall:public IGameObject
{	
public:
	SnowBall();
	~SnowBall();
	bool Start();
	void Update();
	void Atk();
	void Move();
	void Deceleration();
	void Fire(const Vector3& pos, const Vector3& dir, float speed, const Quaternion& rot);
	void Render(RenderContext& rc);



private:
	Player* m_player;
	SnowEnemy* m_snowEnemy;
	ModelRender m_snowBallModel;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_direction;
	Vector3 m_ballCollisionScale;	
	CollisionObject* m_ballcollisionObj;
	Quaternion m_rotation;     //クォータニオン
	float m_speed=0.0f;
	float m_gravity = 0.1f;	
};

