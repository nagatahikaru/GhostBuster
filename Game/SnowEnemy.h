#pragma once
#include "ObjectPool.h"

class Player;
class SnowBall;
class SnowBallManager;

class SnowEnemy:public IGameObject
{
public:
	SnowEnemy();
	~SnowEnemy()override;
	bool Start();
	void Update();
	void SetPosition(const Vector3& pos);
	bool CanAtk();
	void Atk();
	void Move();
	void Rotation();
	void Damage(int damage);
	void PlayAnimation();
	void Render(RenderContext& rc);
		
	CharacterController m_characterController;//当たり判定

	bool m_IsSpawn = true;
private:
	ObjectPool<SnowEnemy> m_snowEnemyPool;
	ModelRender m_snow[2];//雪だるまに擬態する敵
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_snowEnemyCollisionScale;
	Player* m_player;
	SnowBallManager* m_snowBallManager;	
	Quaternion m_rotation;     //クォータニオン。
	int m_form = 0;
	int m_hp=0;
	int m_posStert=0;
	float m_speed = 0.0f;
	FontRender m_distance;
	float m_coolTime;
	bool m_coolTimeFrag = false;
	
};

