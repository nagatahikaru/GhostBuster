#include "stdafx.h"
#include "GolemEnemy.h"
#include "src/Actor/Character/Player/Player.h"
#include "src/Actor/Character/Enemy/Enemy.h"
#include "src/UI/InGameUI/InGameUI.h"
#include "BulletCallback.h"

namespace {
	int ITEM_TYPE_NONE = 0;
}



GolemEnemy::GolemEnemy()
{

}

GolemEnemy::~GolemEnemy()
{
	if (m_golemCollisionObject != nullptr)
	{
		delete m_golemCollisionObject;
		m_golemCollisionObject = nullptr;
	}
}

bool GolemEnemy::Start()
{
	srand(time(nullptr));
	m_golem.Init("Assets/modelData/Golem.tkm");
	m_golem.SetPosition(m_transform.m_position);
	m_golem.SetScale(Vector3(3.0f, 3.0f, 3.0f));
	m_player = Player::GetInstance();
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	m_golemController.Init(150.0f, 300.0f, m_transform.m_position);
	m_golemController.SetCollisionActive(true);
	m_golemCollisionScalr = Vector3(225.0f, 900.0, 225.0f);
	m_golemCollisionObject = new CollisionObject;
	m_golemCollisionObject->CreateBox(
		m_transform.m_position,
		Quaternion::Identity,
		m_golemCollisionScalr);
	SetEnemyExistence(true);
	SetEnemyHp(50);
	return true;
}

void GolemEnemy::Update()
{
	if (!m_inGameUI)
	{
		m_inGameUI = FindGO<InGameUI>("inGameUI");
		return;
	}
	if(m_inGameUI->GetSBlackout())
	{
		return;
	}
	
	Tach(*m_golemCollisionObject, m_golemController,false,ITEM_TYPE_NONE);
	Move();
}

void GolemEnemy::Move()
{

	Vector3 dif = m_player->m_position - m_transform.m_position;
	dif.y = 0;
	float distance = dif.Length();
	if (distance > 2000.0f)
	{
		Wandering(m_golem);		
	}
	else
	{
		m_transform.m_speed = 100.0f;
		dif.Normalize();
		m_transform.m_moveSpeed = dif * m_transform.m_speed;
		Rotation();
	}
	//重力処理
	if (!m_golemController.IsOnGround())
	{
		m_transform.m_moveSpeed.y -= 20.0f;
	}
	else
	{
		float jaumTime = GetTime();
		jaumTime -= g_gameTime->GetFrameDeltaTime();
		SetTime(jaumTime);
		if(GetTime()<=0)
		{
			SetTime(0);
		}
	}
	if (m_player->m_position.y > m_transform.m_position.y + 100 && GetTime() <= 0)
	{
		m_transform.m_moveSpeed.y += 500.0f;
		SetTime(4.0f);
	}

	if(m_transform.m_position.y < -500.0f)
	{
		m_golemController.SetPosition(Vector3(500.0f, 850.0f, 0.0f));
	}	

	Atk();
	m_golemCollisionObject->SetPosition(m_transform.m_position);
	m_golemCollisionObject->SetRotation(Quaternion::Identity);
	m_golemCollisionObject->Update();
	m_transform.m_position = m_golemController.Execute(m_transform.m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_golem.SetPosition(m_transform.m_position);
	m_golem.Update();
	
}

//回転処理
void GolemEnemy::Rotation()
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_transform.m_position;
	toPlayer.Normalize();
	m_transform.m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y軸回りの回転を設定
	m_golem.SetRotation(m_transform.m_rotation);
}

void GolemEnemy::Atk()
{
	if (!CanAtk()) {
		return;
	}
	//攻撃処理
	//現在の位置前方に突進

	Tach(*m_golemCollisionObject, m_golemController, true,ITEM_TYPE_NONE);
}



void GolemEnemy::Damage(int damage)
{	
	int coolTime = 0.0f;
	coolTime -= g_gameTime->GetFrameDeltaTime();
	SetTime(coolTime);
	if (GetTime() <= 0.0f)
	{
		SetTime(0.0f);
	}
	else
	{
		//クールタイム中はダメージを受けない
		return;
	}

	SetEnemyHp(damage);
	SetTime(2.0f);
	if (GetEnemyHp() <= 0)
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