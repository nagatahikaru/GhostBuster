#include "stdafx.h"
#include "GolemEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"

GolemEnemy::GolemEnemy()
{

}

GolemEnemy::~GolemEnemy()
{
}

bool GolemEnemy::Start()
{
	srand(time(nullptr));
	m_golem.Init("Assets/modelData/Golem.tkm");
	m_golem.SetPosition(m_position);
	m_player = FindGO<Player>("player");
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	m_golemController.Init(50.0f, 100.0f, m_position);
	m_golemController.SetCollisionActive(true);
	m_existence = true;
	m_hp = 50;
	return true;
}

void GolemEnemy::Update()
{
	if (!m_inGameUI)
	{
		m_inGameUI = FindGO<InGameUI>("inGameUI");
		return;
	}
	if(m_inGameUI->m_blackout)
	{
		return;
	}
	Move();
}

void GolemEnemy::Move()
{

	Vector3 dif = m_player->m_position - m_position;
	dif.y = 0;
	float distance = dif.Length();
	if (distance > 2000.0f)
	{
		Wandering(m_golem);		
	}
	else
	{
		m_speed = 100.0f;
		dif.Normalize();
		m_moveSpeed = dif * m_speed;
		Rotation();
	}
	//重力処理
	if (!m_golemController.IsOnGround())
	{
		m_moveSpeed.y -= 20.0f;
	}
	else
	{
		m_jaumTime -= g_gameTime->GetFrameDeltaTime();
		if(m_jaumTime<=0)
		{
			m_jaumTime = 0;
		}
	}
	if (m_player->m_position.y > m_position.y + 100 && m_jaumTime <= 0)
	{
		m_moveSpeed.y += 500.0f;
		m_jaumTime = 4.0f;
	}

	if(m_position.y < -500.0f)
	{
		m_golemController.SetPosition(Vector3(500.0f, 850.0f, 0.0f));
	}	

	Atk();
	m_position = m_golemController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_golem.SetPosition(m_position);
	m_golem.Update();
	
}

//回転処理
void GolemEnemy::Rotation()
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_position;
	toPlayer.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y軸回りの回転を設定
	m_golem.SetRotation(m_rotation);
}

void GolemEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//攻撃処理
	//現在の位置前方に突進

}



void GolemEnemy::Damage(int damage)
{	
	m_damageCoolTime -= g_gameTime->GetFrameDeltaTime();
	if (m_damageCoolTime <= 0.0f)
	{
		m_damageCoolTime = 0.0f;
	}
	else
	{
		//クールタイム中はダメージを受けない
		return;
	}
	m_hp -= damage;
	m_damageCoolTime = 2.0f;
	if (m_hp <= 0)
	{
		m_golemController.SetCollisionActive(false);
		Deactivate();
	}
}

void GolemEnemy::PlayAnimation()
{

}

void GolemEnemy::Render(RenderContext& rc)
{
	m_golem.Draw(rc);
}