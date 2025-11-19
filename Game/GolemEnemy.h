#pragma once
#include "Enemy.h"

class Enemy;
class Player;

class GolemEnemy:public Enemy
{
public:
	GolemEnemy();
	~GolemEnemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Atk();
	void Move();
	void Rotation();	
	void Damage(int damage);
	void PlayAnimation();
	

	CharacterController m_golemController;//“–‚½‚è”»’è
	
	private:
	ModelRender m_golem;//ƒS[ƒŒƒ€
};

