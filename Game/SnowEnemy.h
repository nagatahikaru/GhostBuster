#pragma once
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"


class Player;
class SnowBall;
class SnowBallManager;
class Enemy;
class InGameUI;


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
	void PlayAnimation();
	void Render(RenderContext& rc);
		
	CharacterController m_snowController;//ìñÇΩÇËîªíË
	CollisionObject* m_snowCollisionObject;
	Vector3 m_snowCollisionScalr;
private:	
	ModelRender m_snow[2];//ê·ÇæÇÈÇ‹Ç…ã[ë‘Ç∑ÇÈìG
	SnowBallManager* m_snowBallManager;	
	int m_form = 0; //ê·ÇæÇÈÇ‹ÇÃå`ë‘
	FontRender m_distance;
	InGameUI* m_inGameUI;	
};

