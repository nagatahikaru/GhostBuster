#include "stdafx.h"
#include "GhostEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"

GhostEnemy::GhostEnemy()
{

}

GhostEnemy::~GhostEnemy()
{

}

bool GhostEnemy::Start()
{
	srand(time(nullptr));
	m_ghost.Init("Assets/modelData/Ghost.tkm");
	m_ghost.SetPosition(m_position);
	m_player = FindGO<Player>("player");
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	m_ghostController.Init(30.0f, 80.0f, m_position);
	m_hp = 10;
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
	if (m_inGameUI->m_blackout)
	{
		return;
	}

	Move();
	//PlayAnimation();
}

void GhostEnemy::Move()
{

	Vector3 dif = m_player->m_position - m_position;
	float distance = dif.Length();
	//プレイヤーとの距離が一定以下の場合
	//擬態を解いて攻撃をする

	if (distance >= 2000.0f)
	{
		//一定以上離れたら徘徊行動を行う
		Wandering(m_ghost);
	}

	m_speed = 100.0f;
	dif.Normalize();
	m_moveSpeed = dif * m_speed;
	m_moveSpeed.y -= 200.0f;
	if (m_player->m_position.y + 100.0 > m_position.y&& m_jaumTime <=0)
	{
		m_buoyancy = 1000.0f;
		m_jaumTime =4.0f;
	}
	else
	{
		m_buoyancy = 190.0f;
		m_jaumTime -= g_gameTime->GetFrameDeltaTime();
		if (m_jaumTime <= 0)
		{
			m_jaumTime = 0;
		}
	}
	m_moveSpeed.y += m_buoyancy;

	Atk();
	m_position = m_ghostController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_ghost.SetPosition(m_position);
	m_ghost.Update();
	Rotation(m_ghost);
}

void GhostEnemy::Damage(int amount)
{
	//m_damageCoolTime -= g_gameTime->GetFrameDeltaTime();
	//if (m_damageCoolTime <= 0.0f)
	//{
	//	m_damageCoolTime = 0.0f;
	//}
	//else
	//{
	//	//クールタイム中はダメージを受けない
	//	return;
	//}
	m_hp -= amount;
	if (m_hp <= 0)
	{
		m_ghostController.SetCollisionActive(false);
		Deactivate();
	}
}


void GhostEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//攻撃処理
	//現在の位置前方に突進
	
}

void GhostEnemy::PlayAnimation()
{

}

void GhostEnemy::Render(RenderContext& rc)
{
	m_ghost.Draw(rc);
}