#include "stdafx.h"
#include "GolemEnemy.h"
#include "Player.h"

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
	m_characterController.Init(50.0f, 100.0f, m_position);
	m_hp = 10;
	m_IsSpawn = false;
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
	if(distance<=2000.0f)
	{
		m_speed = 100.0f;
		dif.Normalize();
		m_moveSpeed = dif * m_speed;
	}
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y -= 250.0f;
	}
	if(m_position.y < -500.0f)
	{
		m_characterController.SetPosition(Vector3(0.0f, 1000.0f, 0.0f));
	}
	if (distance > 2000.0f)
	{
		Wandering();
	}

	Atk();
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_golem.SetPosition(m_position);
	m_golem.Update();
	Rotation();
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

void GolemEnemy::Wandering()
{
	//徘徊処理
	//ランダムなベクトルを取得
	if(!randVec)
	{
		m_vec = rand() % 361;
		randVec = true;
	}	
	m_rotation.SetRotationDegY((float)m_vec);
	//そのベクトルに向かって移動

	//一定時間経過後、再度ランダムなベクトルを取得

}

void GolemEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//攻撃処理
	//現在の位置前方に突進

}

bool GolemEnemy::CanAtk() {
	if (m_coolTimeFrag)
	{
		m_coolTime -= g_gameTime->GetFrameDeltaTime();
		if (m_coolTime <= 0.0f)
		{
			m_coolTime = 0.0f;
			m_coolTimeFrag = false;
		}
		else
		{
			return false;
		}
	}
	Vector3 dif = m_position - m_player->m_position;
	if (dif.Length() > 750.0f) {
		return false;
	}
	return true;
}

void GolemEnemy::Damage(int damage)
{
	m_hp -= damage;
	if (m_hp <= 0)
	{
		m_characterController.RemoveRigidBoby();
		m_IsSpawn = true;
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