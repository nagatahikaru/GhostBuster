#include "stdafx.h"
#include "GhostEnemy.h"
#include "src/Actor/Character/Player/Player.h"
#include "src/Actor/Character/Enemy/Enemy.h"
#include "src/UI/InGameUI/InGameUI.h"

namespace {
	float JUMP_TIME = 4.0f;//ジャンプ
	float ZERO_FLOAT = 0.0f;
	float MAX_BUOYANCY_POWER = 1000.0f;//浮力の力
	float BUOYANCY_POWER = 190.0f;//浮力の力
	float SPEED = 100.0f;//移動速度
	float GRAVITY = 200.0f;//重力
	float DEFAULT_DISTANCE = 2000.0f;//プレイヤーとの距離
	Vector3 COLLISION_SCALR = Vector3(75.0f, 300.0f, 75.0f);//当たり判定の大きさ
	float CHARACTER_HEIGHT = 80.0f;//キャラクターの高さ
	float CHARACTER_RADIUS = 30.0f;//キャラクターの半径
	float ENEMY_HP = 10.0f;//敵の体力
	float PLAYER_UP_HEIGHT = 100.0f;//プレイヤーの高さ
}


GhostEnemy::GhostEnemy()
{

}

GhostEnemy::~GhostEnemy()
{
	if (m_ghostCollisionObject != nullptr)
	{
		delete m_ghostCollisionObject;
		m_ghostCollisionObject = nullptr;
	}
}

bool GhostEnemy::Start()
{
	srand(time(nullptr));
	m_ghost.Init("Assets/modelData/Ghost.tkm");
	m_ghost.SetPosition(m_transform.m_position);
	m_player = Player::GetInstance();
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	m_ghostController.Init(CHARACTER_RADIUS, CHARACTER_HEIGHT, m_transform.m_position);
	m_ghostCollsitinoScalr = COLLISION_SCALR;
	m_ghostCollisionObject = new CollisionObject;
	m_ghostCollisionObject->CreateBox(
		m_transform.m_position,
		Quaternion::Identity,
		m_ghostCollsitinoScalr);
	SetEnemyHp(ENEMY_HP);
	return true;
}

void GhostEnemy::OnSpawn(const Vector3& pos)
{
	Enemy::OnSpawn(pos, m_ghostController);	
}

void GhostEnemy::Update()
{
	if (!m_inGameUI)
	{
		m_inGameUI = FindGO<InGameUI>("inGameUI");
		return;
	}
	if (m_inGameUI->GetSBlackout())
	{
		return;
	}	

	Tach(*m_ghostCollisionObject,m_ghostController,false,m_itemTypeNone);
	Move();
}

void GhostEnemy::Move()
{

	m_direction = m_player->m_position - m_transform.m_position;
	m_distance = m_direction.Length();
	//プレイヤーとの距離が一定以下の場合
	//擬態を解いて攻撃をする

	if (m_distance >= DEFAULT_DISTANCE)
	{
		//一定以上離れたら徘徊行動を行う
		Wandering(m_ghost);
	}

	m_transform.m_speed = SPEED;
	m_direction.Normalize();
	m_transform.m_moveSpeed = m_direction * m_transform.m_speed;
	m_transform.m_moveSpeed.y -= GRAVITY;

	/**
	 * ジャンプ処理
	 * プレイヤーの高さよりも低い場合にジャンプする
	 */
	if (m_player->m_position.y + PLAYER_UP_HEIGHT > m_transform.m_position.y&& GetTime() <= ZERO_FLOAT)
	{
		m_buoyancy = BUOYANCY_POWER;
		SetTime(JUMP_TIME);
	}
	else
	{
		m_buoyancy = BUOYANCY_POWER;
		float jaumTime = ZERO_FLOAT;
		 jaumTime -= g_gameTime->GetFrameDeltaTime();
		 SetTime(jaumTime);
		if (GetTime() <= ZERO_FLOAT)
		{
			SetTime(ZERO_FLOAT);
		}
	}
	m_transform.m_moveSpeed.y += m_buoyancy;

	Atk();
	m_ghostCollisionObject->SetPosition(m_transform.m_position);
	if (m_distance < DEFAULT_DISTANCE)
	{
		m_ghostCollisionObject->SetRotation(Quaternion::Identity);
	}
	m_ghostCollisionObject->Update();
	m_transform.m_position = m_ghostController.Execute(m_transform.m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_ghost.SetPosition(m_transform.m_position);
	m_ghost.Update();
	Rotation(m_ghost);
}

void GhostEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//攻撃処理
	//現在の位置前方に突進
	Tach(*m_ghostCollisionObject, m_ghostController, true,m_itemTypeNone);
}

void GhostEnemy::PlayAnimation()
{

}

void GhostEnemy::Render(RenderContext& rc)
{	
	m_ghost.Draw(rc);
}