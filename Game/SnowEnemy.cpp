#include "stdafx.h"
#include <time.h> 
#include "SnowEnemy.h"
#include "Player.h"
#include "SnowBall.h"
#include "SnowBallManager.h"


SnowEnemy::SnowEnemy()
{

}

SnowEnemy::~SnowEnemy()
{
	//m_characterController.RemoveRigidBoby();

}

bool SnowEnemy::Start()
{
	srand(time(nullptr));
	m_snow[0].Init("Assets/modelData/SnowMan.tkm");
	m_snow[1].Init("Assets/modelData/SnoEnemy.tkm");
	for (int i = 0; i < 2; i++)
	{
		m_snow[i].SetPosition(m_position);
	}
	m_player = FindGO<Player>("player");
	m_snowBallManager = FindGO<SnowBallManager>("snowBallManager");
	m_hp = 10;

	return true;
}

void SnowEnemy::SetPosition(const Vector3& pos)
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

void SnowEnemy::Update()
{
	if (!m_player)
	{
		return;
	}
	Move();	
	//PlayAnimation();
}

void SnowEnemy::Move()
{
	Vector3 dif = m_player->m_position- m_position;
	float distance=dif.Length();
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
	m_snow[m_form].SetPosition(m_position);
	m_snow[m_form].Update();
	Rotation();
	
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
	if (!CanAtk()) {
		return;
	}
	// “G‚ÌŒü‚«i‘O•ûŒüƒxƒNƒgƒ‹j
	Vector3 dir(0, 0, 1);      // Z+•ûŒü‚ğŠî€‚Ì‘OŒü‚«‚É‚·‚é
	Quaternion rot = m_rotation;
	rot.Apply(dir);
	dir.Normalize(); // ”O‚Ì‚½‚ß³‹K‰»

	// “G‚ÌˆÊ’u(­‚µ‘O‚É‚¸‚ç‚·‚Æ©‘R)
	Vector3 pos = m_position + dir * 10.0f + Vector3(0.0f, 10.0f, 0);

	// ”­Ë–½—ß
	m_snowBallManager->Fire(pos, dir, rot);
	m_coolTime = 3.5f;
	m_coolTimeFrag = true;
}

bool SnowEnemy::CanAtk() {
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


void SnowEnemy::Damage(int damage)
{
	m_hp -= damage;
	if (m_hp <= 0)
	{
		m_characterController.RemoveRigidBoby();
		m_IsSpawn = true;
		Deactivate();
	}
}

void SnowEnemy::PlayAnimation()
{

}

void SnowEnemy::Render(RenderContext& rc)
{
	m_snow[m_form].Draw(rc);

	Vector3 dif = m_position - m_player->m_position;
	float distance = dif.Length();
	wchar_t be[129];
	m_distance.SetPosition(-896.0f, 300.0f, 0.0f);
	m_distance.SetColor(g_vec4White);
	float Distance = distance;
	swprintf(be, 129, L"Distance:%.0f", Distance);
	m_distance.SetText(be);
	m_distance.Draw(rc);
}
