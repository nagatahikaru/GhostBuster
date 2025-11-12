#include "stdafx.h"
#include "SnowBall.h"
#include "SnowEnemy.h"
#include "Player.h"


SnowBall::SnowBall()
{

}

SnowBall::~SnowBall()
{
	if (m_ballcollisionObj) {
		delete m_ballcollisionObj;
		m_ballcollisionObj = nullptr;
	}
}

bool SnowBall::Start()
{
	m_snowBallModel.Init("Assets/modelData/SnowBall.tkm");
	m_player = FindGO<Player>("player");
	m_snowEnemy = FindGO<SnowEnemy>("snowEnemy");
	
	m_ballcollisionObj = new CollisionObject;

	m_ballcollisionObj->CreateSphere(
		m_position,
		Quaternion::Identity,
		20.0f);
	return true;
}

void SnowBall::Fire(const Vector3& pos, const Vector3& dir, float speed, const Quaternion& rot)
{
	m_position = pos;
	m_direction = dir;
	m_speed = speed;
	Activate();
	m_snowBallModel.SetPosition(m_position);
	m_snowBallModel.SetRotation(rot);
}

void SnowBall::Update()
{
	if (!m_isActive) return;
	Move();
}

void SnowBall::Atk()
{
	m_player->Damage(1);//一段階プレイヤーの形態を下げる	
	this->Deactivate(); // 雪玉を非アクティブにする
}

void SnowBall::Move()
{
	float dt = g_gameTime->GetFrameDeltaTime();
	m_position += m_direction * m_speed * dt;
	
	if (m_ballcollisionObj->IsHit(m_player->m_characterController))
	{
		Atk();
	}
	
	m_position.y -= m_gravity;

	m_snowBallModel.SetPosition(m_position);
	m_snowBallModel.Update();	
	m_ballcollisionObj->SetPosition(m_position);
	m_ballcollisionObj->SetRotation(Quaternion::Identity);
	m_ballcollisionObj->Update();
}

//減速処理
void SnowBall::Deceleration()
{
	int magnification = 200;
	m_speed -= g_gameTime->GetFrameDeltaTime() * magnification;
	if (m_speed <= 0.0f)
	{
		Deactivate();
	}
}


void SnowBall::Render(RenderContext& rc)
{
	if (!m_isActive) return; // 非アクティブなら描画スキップ
	// モデルの描画処理
	m_snowBallModel.Draw(rc); // モデルを描画
}