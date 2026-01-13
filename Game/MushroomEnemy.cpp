#include "stdafx.h"
#include "MushroomEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"
#include "BulletCallback.h"

MushroomEnemy::MushroomEnemy()
{

}

MushroomEnemy::~MushroomEnemy()
{
	if (m_mushroomCollisionObject != nullptr)
	{
		delete m_mushroomCollisionObject;
		m_mushroomCollisionObject = nullptr;
	}
}

bool MushroomEnemy::Start()
{
	srand(time(nullptr));
	m_mushroom.Init("Assets/modelData/Mushroom.tkm");
	m_mushroom.SetPosition(m_position);	
	m_player = Player::GetInstance();
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	m_mushroomController.Init(25.0f, 80.0f, m_position);
	m_mushroomCollisionScalr = Vector3(75.0f,300.0, 75.0f);
	m_mushroomCollisionObject = new CollisionObject;
	m_mushroomCollisionObject->CreateBox(
		m_position,
		Quaternion::Identity,
		m_mushroomCollisionScalr);
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
	Tach(*m_mushroomCollisionObject, m_mushroomController,false);
	

	//PlayAnimation();
}

void MushroomEnemy::Move()
{
	Vector3 dif = m_player->m_position - m_position;
	dif.y = 0;
	float distance = dif.Length();
	//ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ªˆê’èˆÈ‰º‚Ìê‡
	if (distance >= 2000.0f)
	{
		//ˆê’èˆÈã—£‚ê‚½‚çœpœjs“®‚ðs‚¤
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
	m_mushroomCollisionObject->SetPosition(m_position);
	m_mushroomCollisionObject->SetRotation(Quaternion::Identity);
	m_mushroomCollisionObject->Update();
	m_position = m_mushroomController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_mushroom.SetPosition(m_position);
	m_mushroom.Update();
	Rotation();

}

//‰ñ“]ˆ—
void MushroomEnemy::Rotation()
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_position;
	toPlayer.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// YŽ²‰ñ‚è‚Ì‰ñ“]‚ðÝ’è
	m_mushroom.SetRotation(m_rotation);
}

void MushroomEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//UŒ‚ˆ—
	//Œ»Ý‚ÌˆÊ’u‘O•û‚É“Ëi

	Tach(*m_mushroomCollisionObject, m_mushroomController, true);
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

void MushroomEnemy::PlayAnimation()
{

}

void MushroomEnemy::Render(RenderContext& rc)
{
	m_mushroom.Draw(rc);
}
