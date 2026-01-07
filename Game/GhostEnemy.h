#pragma once
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"

class Player;
class Enemy;
class InGameUI;



class GhostEnemy:public Enemy
{
public:
	GhostEnemy();	
	~GhostEnemy();
	bool Start();
	void Update();
	void OnSpawn(const Vector3& pos);
	void Render(RenderContext& rc);
	void Atk();
	void Move();
	void PlayAnimation();	
	//当たり判定CharacterController
	CharacterController m_ghostController;
	CollisionObject* m_ghostCollisionObject;
	private:
	ModelRender m_ghost;//幽霊の敵
	InGameUI* m_inGameUI;
	Player* m_player;
	float m_distance;//プレイヤーとの距離
	Vector3 m_direction;//プレイヤーへの方向ベクトル
	int m_blinking0=0;//点滅用カウンター
	int m_blinking1 = 1;//点滅用カウンター
	Vector3 m_ghostCollsitinoScalr;



};


