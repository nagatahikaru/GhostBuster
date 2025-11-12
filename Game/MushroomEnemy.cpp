#include "stdafx.h"
#include "MushroomEnemy.h"
#include "Player.h"

MushroomEnemy::MushroomEnemy()
{

}

MushroomEnemy::~MushroomEnemy()
{
	//m_characterController.RemoveRigidBoby();
}

bool MushroomEnemy::Start()
{
	srand(time(nullptr));
	m_mushroom.Init("Assets/modelData/Mushroom.tkm");	
	m_mushroom.SetPosition(m_position);	
	m_player = FindGO<Player>("player");	
	m_hp = 10;
	return true;
}

void MushroomEnemy::SetPosition(const Vector3& pos)
{
	if (!m_IsSpawn)
	{
		return;
	}
	m_position = pos;

	m_characterController.Init(50.0f, 100.0f, m_position);
	m_isInited = true;
	m_IsSpawn = false;
}

void MushroomEnemy::Update()
{
	if (!m_player)
	{
		return;
	}
	Move();
	//PlayAnimation();
}

void MushroomEnemy::Move()
{
	Vector3 dif = m_player->m_position - m_position;
	float distance = dif.Length();
	//ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ªˆê’èˆÈ‰º‚Ìê‡
	//‹[‘Ô‚ğ‰ğ‚¢‚ÄUŒ‚‚ğ‚·‚é
	if (distance <= 250.0f)
	{
		m_form = 1;
	}
	//‹[‘Ô‚µ‚Ä‚½‚ç“®‚©‚È‚¢
	if (m_form == 0)
	{
		return;
	}

	if (distance >= 2000.0f)
	{
		m_form = 0;
	}

	m_speed = 100.0f;
	dif.Normalize();
	m_moveSpeed = dif * m_speed;
	m_moveSpeed.y -= 150.0f;

	Atk();
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
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
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y²‰ñ‚è‚Ì‰ñ“]‚ğİ’è
	m_mushroom.SetRotation(m_rotation);
}

void MushroomEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//UŒ‚ˆ—
	//Œ»İ‚ÌˆÊ’u‘O•û‚É“Ëi

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
	m_hp -= damage;
	if (m_hp <= 0)
	{
		m_characterController.RemoveRigidBoby();
		m_IsSpawn = true;
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
