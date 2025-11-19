#pragma once
#include "Enemy.h"

class Player;
class Enemy;

class GhostEnemy:public Enemy
{
public:
	GhostEnemy();	
	~GhostEnemy();
	bool Start();
	void Update();
	void Damage(int amount);
	void OnSpawn(const Vector3& pos);
	void Render(RenderContext& rc);
	void Atk();
	void Move();
	void PlayAnimation();	
	//“–‚½‚è”»’è
	CharacterController m_ghostController;
	private:
	ModelRender m_ghost;//—H—ì‚Ì“G
	
};

