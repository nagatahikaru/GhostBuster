#pragma once
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"


class Enemy;
class Player;
class InGameUI;


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
	

	CharacterController m_golemController;//ìñÇΩÇËîªíË
	
	private:
	ModelRender m_golem;//ÉSÅ[ÉåÉÄ
	InGameUI* m_inGameUI;
};

