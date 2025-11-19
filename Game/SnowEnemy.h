#pragma once
#include "Enemy.h"

class Player;
class SnowBall;
class SnowBallManager;
class Enemy;

class SnowEnemy:public Enemy
{
public:
	SnowEnemy();
	~SnowEnemy()override;
	bool Start();
	void Update();
	void OnSpawn(const Vector3& pos);
	void Atk();
	void Move();
	void Rotation();
	void Damage(int damage);
	void PlayAnimation();
	void Render(RenderContext& rc);
		
	CharacterController m_snowController;//ìñÇΩÇËîªíË

private:	
	ModelRender m_snow[2];//ê·ÇæÇÈÇ‹Ç…ã[ë‘Ç∑ÇÈìG
	SnowBallManager* m_snowBallManager;	
	int m_form = 0; //ê·ÇæÇÈÇ‹ÇÃå`ë‘
	FontRender m_distance;

	
};

