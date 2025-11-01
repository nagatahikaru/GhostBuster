#include "stdafx.h"
#include <time.h> 
#include "SnowEnemy.h"
#include "Player.h"

SnowEnemy::SnowEnemy()
{

}

SnowEnemy::~SnowEnemy()
{

}

bool SnowEnemy::Start()
{
	srand(time(nullptr));
	m_position = Vector3(rand() % 300, 0.0f, rand() % 400);
	m_snow[0].Init("Assets/modeldeta/SnowMan.tkm");
	m_snow[1].Init("Assets/modeldeta/SnowMan.tkm");
	for(int i=0;i<2;i++)
	{
		m_snow[i].SetPosition(m_position);
	}
	m_hitJudgment.GetCollider();
	m_hitJudgment.SetPosition(m_position);
	m_player=FindGO<Player>("player");
	return true;
}

void SnowEnemy::Update()
{
	if (!m_player)
	{
		return;
	}
	Move();
	Atk();
	
}

void SnowEnemy::Move()
{
	Vector3 dif = m_position - m_player->m_position;
	dif.Normalize();
	//ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ªˆê’èˆÈ‰º‚Ìê‡
	//‹[‘Ô‚ğ‰ğ‚¢‚ÄUŒ‚‚ğ‚·‚é
	/*if (dif.Normalize() <= 100.0f)
	{
		m_form = 1;
	}*/
	//‹[‘Ô‚µ‚Ä‚½‚ç“®‚©‚È‚¢
	if (m_form == 0)
	{
		return;
	}
	m_snow[m_form].SetPosition(m_position);
	m_snow[m_form].Update();

}

//‰ñ“]ˆ—
void SnowEnemy::Rotation()
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_position;
	toPlayer.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y²‰ñ‚è‚Ì‰ñ“]‚ğİ’è
	m_snow[m_form].SetRotation(m_rotation);
}

void SnowEnemy::Atk()
{
	//if()
	{
		
	}
}

void SnowEnemy::Damage(int damage)
{
	m_hp -= damage;
}

void SnowEnemy::Render(RenderContext& rc)
{
	m_snow[m_form].Draw(rc);
}
