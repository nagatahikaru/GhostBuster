#include "stdafx.h"
#include "SnowBall.h"
#include "SnowEnemy.h"
#include "Player.h"
#include "UI/InGameUI/InGameUI.h"
#include "BackGround.h"


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
	m_player = Player::GetInstance();
	m_snowEnemy = FindGO<SnowEnemy>("snowEnemy");
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	m_backGroud = FindGO<BackGround>("backGround");
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
	if (!m_isActive|| m_inGameUI->m_blackout) return;
	Move();
	DropMove();
}

void SnowBall::Atk()
{
	m_player->Damage(1);//一段階プレイヤーの形態を下げる	
	this->Deactivate(); // 雪玉を非アクティブにする
}

void SnowBall::Move()
{
	if (m_dropFlag)
	{
		return;
	}
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
	Deceleration();
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

void SnowBall::Dorop(Vector3&pos)
{
	m_position = pos;
	Activate();
	Quaternion rot;
	m_snowBallModel.SetPosition(m_position);
	m_snowBallModel.SetRotation(rot);
	m_dropFlag = true;
}

void SnowBall::DropMove()
{
	if (!m_dropFlag)return;
	Vector3 pos = m_player->m_position - m_position;
	float dir =pos.Length();
	if (dir >= 100.0f)
	{
		m_player->m_itemStatus = 1;//アイテム所持状況を1にする
		Deactivate();
		m_dropFlag = false;
	}
	//地面に着地したら非アクティブにする
	if (dir<=1000.0f)
	{
		Deactivate();
		m_dropFlag = false;
	}
}


void SnowBall::Render(RenderContext& rc)
{
	if (!m_isActive) return; // 非アクティブなら描画スキップ
	// モデルの描画処理
	m_snowBallModel.Draw(rc); // モデルを描画
}