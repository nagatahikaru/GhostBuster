#pragma once
#include "UI/InGameUI/InGameUI.h"


class SnowEnemy;
class Player;
class InGameUI;
class BackGround;


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
	void Dorop(Vector3& pos);
	void DropMove();
	void Fire(const Vector3& pos, const Vector3& dir, float speed, const Quaternion& rot);
	void Render(RenderContext& rc);



private:
	BackGround* m_backGroud;
	InGameUI* m_inGameUI;
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
	bool m_dropFlag = false;//雪玉を落とすフラグ

};

