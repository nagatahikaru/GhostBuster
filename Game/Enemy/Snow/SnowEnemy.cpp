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

//デストラクタ
SnowEnemy::~SnowEnemy()
{
	if (m_snowCollisionObject != nullptr)
	{
		delete m_snowCollisionObject;
		m_snowCollisionObject = nullptr;
	}
}

//初期化処理
bool SnowEnemy::Start()
{
	//乱数初期化
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
	m_snowCollisionScalr = Vector3(75.0f,  300.0, 75.0f);
	m_snowCollisionObject = new CollisionObject;
	m_snowCollisionObject->CreateBox(
		m_position,
		Quaternion::Identity,
		m_snowCollisionScalr);
	return true;
}

//スポーン処理
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

//更新処理
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
	Tach(*m_snowCollisionObject, m_snowController,false);

	//PlayAnimation();
}

//移動処理
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
	//プレイヤーとの距離が一定以下の場合
	//擬態を解いて攻撃をする
	if (distance <= 250.0f)
	{
		m_form = 1;
	}
	//擬態してたら動かない
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

//回転処理
void SnowEnemy::Rotation()
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_position;
	toPlayer.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y軸回りの回転を設定
	m_snow[m_form].SetRotation(m_rotation);
}

void SnowEnemy::Atk()
{	
	if (!CanAtk()) {
		return;
	}
	// 敵の向き（前方向ベクトル）
	Vector3 dir(0, 0, 1);      // Z+方向を基準の前向きにする
	Quaternion rot = m_rotation;
	rot.Apply(dir);
	dir.Normalize(); // 念のため正規化

	// 敵の位置(少し前にずらすと自然)
	Vector3 pos = m_position + dir * 10.0f + Vector3(0.0f, 10.0f, 0);

	// 発射命令
	m_snowBallManager->Fire(pos, dir, rot);
	m_coolTime = 3.5f;
	m_coolTimeFrag = true;
}

//アイテムドロップ
void SnowEnemy::DoropItem()
{
	if (m_hp <= 0)
	{
		//アイテムドロップ処理
		int randNum = rand() % 100;
		if(randNum < 30)
		{
			//30%の確率で雪玉をドロップ
			SnowBall* snowBall = FindGO<SnowBall>("snowBall");
			//雪玉をドロップ
			snowBall->Fire(m_position + Vector3(0.0f, 50.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), 0.0f, Quaternion::Identity);

		}
	}
}

//アニメーション設定
void SnowEnemy::PlayAnimation()
{

}

//描画処理
void SnowEnemy::Render(RenderContext& rc)
{
	m_snow[m_form].Draw(rc);
}
