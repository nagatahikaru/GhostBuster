#include "stdafx.h"
#include <time.h> 
#include "SnowEnemy.h"
#include "Player.h"
#include "SnowBall.h"
#include "SnowBallManager.h"
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"


SnowEnemy::SnowEnemy()
{

}

SnowEnemy::~SnowEnemy()
{
	if (m_snowCollisionObject != nullptr)
	{
		delete m_snowCollisionObject;
		m_snowCollisionObject = nullptr;
	}
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
	m_snowController.Init(25.0f, 80.0f, m_position);
	m_player = Player::GetInstance();
	m_hp = 10;
	m_snowBallManager = FindGO<SnowBallManager>("snowBallManager");
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	m_snowCollisionScalr = Vector3(25.0f, 80.0, 25.0f);
	m_snowCollisionObject = new CollisionObject;
	m_snowCollisionObject->CreateBox(
		m_position,
		Quaternion::Identity,
		m_snowCollisionScalr);
	return true;
}

void SnowEnemy::OnSpawn(const Vector3& pos)
{
	m_snow[0].SetPosition(m_position);
	m_snow[1].SetPosition(m_position);
	m_hp = m_maxHp;
	m_form = 0;
	m_position = pos;
	m_snowController.SetCollisionActive(true);
	m_snowController.SetPosition(pos);
}

void SnowEnemy::Update()
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
	Tach(*m_snowCollisionObject,m_position,m_hp);

	//PlayAnimation();
}

void SnowEnemy::Move()
{
	Vector3 dif = m_player->m_position- m_position;
	dif.y = 0;
	float distance=dif.Length();
	m_speed = 100.0f;
	dif.Normalize();
	m_moveSpeed = dif * m_speed;
	if (!m_snowController.IsOnGround())
	{
		m_moveSpeed.y -= 200.0f;
	}
	else
	{
		m_jaumTime -= g_gameTime->GetFrameDeltaTime();
		if(m_jaumTime<=0)
		{
			m_jaumTime = 0;
		}
	}
	if (m_player->m_position.y > m_position.y + 100&& m_jaumTime <=0&&m_form==1)
	{
		m_moveSpeed.y += 1000.0f;
		m_jaumTime=4.0f;
	}
	//ƒvƒŒƒCƒ„[‚Æ‚Ì‹——£‚ªˆê’èˆÈ‰º‚Ìê‡
//‹[‘Ô‚ð‰ð‚¢‚ÄUŒ‚‚ð‚·‚é
	if (distance <= 250.0f)
	{
		m_form = 1;
	}
	//‹[‘Ô‚µ‚Ä‚½‚ç“®‚©‚È‚¢
	if (m_form == 0)
	{		
		m_moveSpeed.x = 0;
		m_moveSpeed.z = 0;
	}
	if (distance >= 2000.0f)
	{
		m_form = 0;
	}
	if (distance <= 750 && m_form == 1)
	{
		Atk();
	}
	m_snowCollisionObject->SetPosition(m_position);
	m_snowCollisionObject->SetRotation(Quaternion::Identity);
	m_snowCollisionObject->Update();
	m_position = m_snowController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_snow[m_form].SetPosition(m_position);
	m_snow[m_form].Update();
	if(m_form==1)
	{
		Rotation();
	}
	
}

//‰ñ“]ˆ—
void SnowEnemy::Rotation()
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_position;
	toPlayer.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// YŽ²‰ñ‚è‚Ì‰ñ“]‚ðÝ’è
	m_snow[m_form].SetRotation(m_rotation);
}

void SnowEnemy::Atk()
{	
	if (!CanAtk()) {
		return;
	}
	// “G‚ÌŒü‚«i‘O•ûŒüƒxƒNƒgƒ‹j
	Vector3 dir(0, 0, 1);      // Z+•ûŒü‚ðŠî€‚Ì‘OŒü‚«‚É‚·‚é
	Quaternion rot = m_rotation;
	rot.Apply(dir);
	dir.Normalize(); // ”O‚Ì‚½‚ß³‹K‰»

	// “G‚ÌˆÊ’u(­‚µ‘O‚É‚¸‚ç‚·‚ÆŽ©‘R)
	Vector3 pos = m_position + dir * 10.0f + Vector3(0.0f, 10.0f, 0);

	// ”­ŽË–½—ß
	m_snowBallManager->Fire(pos, dir, rot);
	m_coolTime = 3.5f;
	m_coolTimeFrag = true;
}

void SnowEnemy::PlayAnimation()
{

}

void SnowEnemy::Render(RenderContext& rc)
{
	m_snow[m_form].Draw(rc);
}
