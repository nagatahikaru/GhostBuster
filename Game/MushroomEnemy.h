#pragma once
#include "Enemy.h"

class Enemy;
class Player;

class MushroomEnemy:public Enemy
{
public:
	MushroomEnemy();
	~MushroomEnemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void OnSpawn(const Vector3& pos);
	bool CanAtk();
	void Atk();
	void Move();
	void Rotation();
	void Damage(int damage);
	void PlayAnimation();

	CharacterController m_mushroomController;//“–‚½‚è”»’è
	
private:
	ModelRender m_mushroom;//ƒLƒmƒR‚Ì“G
};

