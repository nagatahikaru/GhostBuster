#pragma once
#include "src/Actor/Character/Enemy/Enemy.h"
#include "src/UI/InGameUI/InGameUI.h"


class Enemy;
class Player;
class InGameUI;

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
	void PlayAnimation();

	CharacterController m_mushroomController;//“–‚½‚è”»’è
	CollisionObject* m_mushroomCollisionObject;
	Vector3 m_mushroomCollisionScalr;
private:
	ModelRender m_mushroom;//ƒLƒmƒR‚Ì“G
	InGameUI* m_inGameUI;
};

