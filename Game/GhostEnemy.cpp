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
	m_player = Player::GetInstance();
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
	Tach(m_ghostController);
}

void GhostEnemy::Move()
{

	m_direction = m_player->m_position - m_position;
	m_distance = m_direction.Length();
	//ÉvÉåÉCÉÑÅ[Ç∆ÇÃãóó£Ç™àÍíËà»â∫ÇÃèÍçá
	//ã[ë‘ÇâÇ¢ÇƒçUåÇÇÇ∑ÇÈ

	if (m_distance >= 2000.0f)
	{
		//àÍíËà»è„ó£ÇÍÇΩÇÁúpújçsìÆÇçsÇ§
		Wandering(m_ghost);
	}

	m_speed = 100.0f;
	m_direction.Normalize();
	m_moveSpeed = m_direction * m_speed;
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

void GhostEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//çUåÇèàóù
	//åªç›ÇÃà íuëOï˚Ç…ìÀêi
	
}

void GhostEnemy::PlayAnimation()
{

}

void GhostEnemy::Render(RenderContext& rc)
{	
	if(m_damageCoolTime<=0)
	{
		int blinkSpeed = m_blinking0;
		m_blinking0 = m_blinking1;
		m_blinking1 = blinkSpeed;
	}
	if(m_blinking0==0||m_blinking0==1)
	{
		//ì_ñ≈íÜÇÕï`âÊÇµÇ»Ç¢
		return;
	}
	m_ghost.Draw(rc);
}