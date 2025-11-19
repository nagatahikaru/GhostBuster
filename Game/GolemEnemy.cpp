#include "stdafx.h"
#include "GolemEnemy.h"
#include "Player.h"
#include "Enemy.h"

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
	m_golemController.Init(50.0f, 100.0f, m_position);
	m_golemController.SetCollisionActive(true);
	m_existence = true;
	m_hp = 50;
	return true;
}

void GolemEnemy::Update()
{
	if (!m_player)
	{
		return;
	}
	Move();

}

void GolemEnemy::Move()
{

	Vector3 dif = m_player->m_position - m_position;
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
	if(m_player->m_position.y> m_position.y+100)
	{
		m_moveSpeed.y += 200.0f;
	}
	//d—Íˆ—
	if (m_golemController.IsOnGround())
	{
		m_moveSpeed.y -= 250.0f;
	}
	if(m_position.y < -500.0f)
	{
		m_golemController.SetPosition(Vector3(0.0f, 1000.0f, 0.0f));
	}	

	Atk();
	m_position = m_golemController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_golem.SetPosition(m_position);
	m_golem.Update();
	
}

//‰ñ“]ˆ—
void GolemEnemy::Rotation()
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_position;
	toPlayer.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y²‰ñ‚è‚Ì‰ñ“]‚ğİ’è
	m_golem.SetRotation(m_rotation);
}

void GolemEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//UŒ‚ˆ—
	//Œ»İ‚ÌˆÊ’u‘O•û‚É“Ëi

}



void GolemEnemy::Damage(int damage)
{	
	Enemy::Damage(damage, m_golemController);
}

void GolemEnemy::PlayAnimation()
{

}

void GolemEnemy::Render(RenderContext& rc)
{
	m_golem.Draw(rc);
}