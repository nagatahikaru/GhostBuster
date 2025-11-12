#include "stdafx.h"

#include "Player.h"
#include "GameCamera.h"
#include "SnowEnemy.h"
#include "SnowEnemyManager.h"
#include "GhostEnemy.h"
#include "GhostEnemyManager.h"
#include "GolemEnemy.h"
#include "MushroomEnemy.h"
#include "MushroomEnemyManager.h"

//#include "ObjectPool.h"



Player::Player()
{
	
}

Player::~Player()
{

}

bool Player::Start()
{
	

	//アニメーションクリップの読み込み
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	//モデルの初期化
	m_modelRender[0].Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//子供モデル
	m_modelRender[1].Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//子供モデル
	m_modelRender[2].Init("Assets/modelData/unityChanDX.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisZ);//大人化モデル
	m_modelRender[3].Init("Assets/modelData/MagicalUnity.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisZ);//魔法少女モデル
	m_position = Vector3{ 500.0f,1600.0f,0.0f };
	for(int i=0;i<3;i++)
	{
		m_modelRender[i].SetPosition(m_position);
	}	
	m_playerCollisionScale = Vector3(25.0f, 10.0f, 25.0f);
	m_playerCollisionObj = new CollisionObject;
	m_playerCollisionObj->CreateBox(
		m_position,
		Quaternion::Identity,
		m_playerCollisionScale);

	m_formState = 1;
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	const auto& enemys = FindGOs<SnowEnemy>("snowenemy");
	const auto& ghostEnemys = FindGOs<GhostEnemy>("ghostEnemy");
	const auto& mushroomEnemys = FindGOs<MushroomEnemy>("mushroomEnemy");
	m_golemEnemy = FindGO<GolemEnemy>("golemEnemy");
	m_residue = 3;
	m_jumpingPower = 550.0f;
	return true;
}

//更新処理
void Player::Update()
{
	Move();
	Rotate();
	PlayAnimation();
	ContactJudgment();
}

//移動処理
void Player::Move()
{	
	//xzの移動速度を0.0fにする
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持って来る。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//ｙ方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0;

	//左スティックの入力量と200.0fを乗算
	right *= stickL.x * 200.0f;
	forward *= stickL.y * 200.0f;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	//最初いきなり加速せず
	if (g_pad[0]->IsPress(enButtonB))
	{
		m_moveSpeed.x *= m_time; // Bボタンが押されている間、時間経過で加速していく
		m_moveSpeed.z *= m_time; // Bボタンが押されている間、時間経過で加速していく
		if (m_time <= 5.0f)
		{
			m_time += g_gameTime->GetFrameDeltaTime(); // 経過時間を更新
			sperd = true;
		}
		if(sperd)
		{
			m_time = 5.0f;
		}		
	}
	else
	{
		//経過時間を減算していく
		m_time = m_reset;
		sperd = false;
	}
	if (m_time <= m_reset) // 経過時間が0以下になったら
	{
		m_time = m_reset; // 経過時間を0にリセット
	}

	//地面についていたら
	if (m_characterController.IsOnGround())
	{
		//重力をなくす
		m_moveSpeed.y = 0.0f;
		m_playerAnimationState = 0;
		m_jumpCount = 0;
	}
	else//地面についていなかったら
	{
		//重力を発生させる
		const float gravety = 200.0f;//重力の定数
		m_moveSpeed.y -= gravety* g_gameTime->GetFrameDeltaTime()*4;
	}

	if(m_position.y<=-800.0f)
	{
		m_position = Vector3{ 500.0f,1600.0f,0.0f };		
	}


	if (g_pad[0]->IsTrigger(enButtonX))
	{
		int form=m_formState;
		m_formState=m_form1;
		m_form1 = m_form2;
		m_form2 = form;

	}
	//ジャンプの処理
	//Jボタンを押したときジャンプのカウントが最大でなければジャンプする
	//形態によってジャンプできる回数は変化する
	if (g_pad[0]->IsTrigger(enButtonA) && m_jumpCount < m_formState)
	{
		
		//上方向に250の初速を加える
		m_moveSpeed.y += m_jumpingPower;
	}
	//キャラクターコントローラーを使って座標を移動させる
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_playerCollisionObj->SetPosition(m_position);
	m_playerCollisionObj->SetRotation(Quaternion::Identity);
	m_playerCollisionObj->Update();
	m_modelRender[m_formState].SetPosition(m_position);
	m_modelRender[m_formState].Update();
}

//回転処理
void Player::Rotate()
{
	//入力方向を持ってくる
	Vector3 forward = m_moveSpeed;
	forward.y = 0;
	forward.Normalize();
	//向きをセット
	m_rotation.SetRotationYFromDirectionXZ(forward);
	//絵描きさんに回転を教える
	m_modelRender[m_formState].SetRotation(m_rotation);
}

void Player::ContactJudgment()
{
	
	const auto snowenemys = FindGOs<SnowEnemy>("snowEnemy");
	const auto ghostenemys = FindGOs<GhostEnemy>("ghostEnemy");
	const auto mushroomenemys = FindGOs<MushroomEnemy>("mushroomEnemy");

	//雪だるま型の敵との当たり判定	
	for (auto snowEnemy : snowenemys)
	{
		if (!snowEnemy->m_isInited) continue;

		//ポインタ参照には*がいる
		if (m_playerCollisionObj->IsHit(snowEnemy->m_characterController))
		{
			// 当たり判定があったときの処理
			snowEnemy->Damage(10);
			m_position.y += m_jumpingPower;
		}
	}
	//幽霊型の敵との当たり判定
	for (auto ghostEnemys : ghostenemys)
	{
		if (!ghostEnemys->m_isInited) continue;

		//ポインタ参照には*がいる
		if (m_playerCollisionObj->IsHit(ghostEnemys->m_characterController))
		{
			// 当たり判定があったときの処理
			ghostEnemys->Damage(10);
			m_position.y += m_jumpingPower;
		}
	}
	//キノコ型の敵との当たり判定
	for (auto mushroomEnemys : mushroomenemys)
	{
		if (!mushroomEnemys->m_isInited) continue;
		//ポインタ参照には*がいる
		if (m_playerCollisionObj->IsHit(mushroomEnemys->m_characterController))
		{
			// 当たり判定があったときの処理
			mushroomEnemys->Damage(10);
			m_position.y += m_jumpingPower;
		}
	}
	if (m_golemEnemy == nullptr)
	{
		return;
	}
	//ゴーレム型の敵との当たり判定
	if(m_golemEnemy->m_isInited)
	{
		//ポインタ参照には*がいる
		if (m_playerCollisionObj->IsHit(m_golemEnemy->m_characterController))
		{
			// 当たり判定があったときの処理
			m_golemEnemy->Damage(10);
			m_position.y += m_jumpingPower;
		}
	}
}

//アニメーションの再生
void Player::PlayAnimation()
{
	if(m_formState<=1)
	{
		//ジャンプの処理
		if (g_pad[0]->IsTrigger(enButtonA) && m_jumpCount < m_formState) // Aボタンが押されたら
		{
			m_playerAnimationState = 3;
			m_jumpCount++;
		}
		//地面についていなかったら
		if (!m_characterController.IsOnGround())
		{
			m_playerAnimationState = 3;
		}

		if (m_playerAnimationState != 3) { // ジャンプ中は無視
			//ｘかｚの移動速度があったら（スティックの入力があったら）
			if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
			{
				//歩きアニメーションを再生する
				m_playerAnimationState = 1;
				//走るアニメーションを再生する
				if (g_pad[0]->IsPress(enButtonB))
				{
					m_playerAnimationState = 2;
				}
			}
			//ｘとｚの移動速度が無かったら（スティックの入力が無かったら）
			else
			{
				m_playerAnimationState = 0;
			}
		}
	}
	if(m_formState>=2)
	{
		//ジャンプの処理
		//if (g_pad[0]->IsTrigger(enButtonA) && m_jumpCount < m_formState) // Aボタンが押されたら
		//{
		//	m_playerAnimationState = 3;
		//	m_jumpCount++;
		//}
		////地面についていなかったら
		//if (!m_characterController.IsOnGround())
		//{
		//	m_playerAnimationState = 3;
		//}
		//if (m_playerAnimationState != 3) { // ジャンプ中は無視
		//	//ｘかｚの移動速度があったら（スティックの入力があったら）
		//	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		//	{
		//		//歩きアニメーションを再生する
		//		m_playerAnimationState = 1;
		//		//走るアニメーションを再生する
		//		if (g_pad[0]->IsPress(enButtonB))
		//		{
		//			m_playerAnimationState = 2;
		//		}
		//	}
		//	//ｘとｚの移動速度が無かったら（スティックの入力が無かったら）
		//	else
		//	{
		//		m_playerAnimationState = 0;
		//	}
		//}
	}
	m_modelRender[m_formState].PlayAnimation(m_playerAnimationState);
}
//ダメージ処理
void Player::Damage(int damage)
{
	//形態ダウン
	m_formState -= damage;
	if (m_formState == 0)
	{
		m_formState = 1;
		m_residue--;
	}
}


void Player::Render(RenderContext& rc)
{
	if (!m_gameCamera)
	{
		return;
	}

	wchar_t be[129];
	m_posRender.SetPosition(-896.0f, 200.0f, 0.0f);
	m_posRender.SetColor(g_vec4White);
	Vector3 pos = m_position;
	swprintf(be, 129, L"pos:x=%.0f,y=%.0f,z=%.0f", pos.x,pos.y,pos.z);
	m_posRender.SetText(be);
	m_posRender.Draw(rc);

	//プレイヤーが描画される設定になっていたら描画する
	if(m_gameCamera->m_playerRenderFlag)
	{
		//現在の形態状態のモデルレンダーを描画する
		m_modelRender[m_formState].Draw(rc);
	}
}