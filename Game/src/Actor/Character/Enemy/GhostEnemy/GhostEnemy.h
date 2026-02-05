#pragma once
#include "src/Actor/Character/Enemy/Enemy.h"
#include "src/UI/InGameUI/InGameUI.h"

class Player;
//class Enemy;
//class InGameUI;



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

private:
	//当たり判定CharacterController
	CharacterController m_ghostController;
	CollisionObject* m_ghostCollisionObject;
	ModelRender m_ghost;//幽霊の敵
	InGameUI* m_inGameUI;
	Player* m_player;
	float m_distance;//プレイヤーとの距離
	Vector3 m_direction;//プレイヤーへの方向ベクトル
	int m_itemTypeNone = 0; //ドロップ無し
	Vector3 m_ghostCollsitinoScalr;
	float m_buoyancy = 0.0f; //浮遊感


};


