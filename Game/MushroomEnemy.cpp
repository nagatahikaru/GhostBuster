#include "stdafx.h"
#include "MushroomEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"

MushroomEnemy::MushroomEnemy()
{

}

MushroomEnemy::~MushroomEnemy()
{
	
}

bool MushroomEnemy::Start()
{
	srand(time(nullptr));
	m_mushroom.Init("Assets/modelData/Mushroom.tkm");
	m_mushroom.SetPosition(m_position);	
	m_player = FindGO<Player>("player");
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	m_mushroomController.Init(25.0f, 80.0f, m_position);
	m_hp = 10;
	return true;
}

void MushroomEnemy::OnSpawn(const Vector3& pos)
{
	Enemy::OnSpawn(pos, m_mushroomController);
}

void MushroomEnemy::Update()
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

void MushroomEnemy::Move()
{
	Vector3 dif = m_player->m_position - m_position;
	dif.y = 0;
	float distance = dif.Length();
	//プレイヤーとの距離が一定以下の場合
	if (distance >= 2000.0f)
	{
		//一定以上離れたら徘徊行動を行う
		Wandering(m_mushroom);
	}
	m_speed = 100.0f;
	dif.Normalize();
	m_moveSpeed = dif * m_speed;



	if (!m_mushroomController.IsOnGround())
	{
		m_moveSpeed.y-=20.0f;
	}
	else
	{
		m_jaumTime -= g_gameTime->GetFrameDeltaTime();
		if (m_jaumTime <= 0)
		{
			m_jaumTime = 0;
		}
	}
	if (m_player->m_position.y > m_position.y + 100 && m_jaumTime <= 0)
	{
		m_moveSpeed.y += 500.0f;
		m_jaumTime = 4.0f;
	}

	Atk();
	m_position = m_mushroomController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_mushroom.SetPosition(m_position);
	m_mushroom.Update();
	Rotation();

}

//回転処理
void MushroomEnemy::Rotation()
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_position;
	toPlayer.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y軸回りの回転を設定
	m_mushroom.SetRotation(m_rotation);
}

void MushroomEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//攻撃処理
	//現在の位置前方に突進

}

bool MushroomEnemy::CanAtk() {
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


void MushroomEnemy::Damage(int damage)
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
	if (m_hp <= 0)
	{
		m_mushroomController.SetCollisionActive(false);
		Deactivate();
	}
}

void MushroomEnemy::PlayAnimation()
{

}

void MushroomEnemy::Render(RenderContext& rc)
{
	m_mushroom.Draw(rc);
}
