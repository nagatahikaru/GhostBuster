#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"

Player::Player()
{
	
}

Player::~Player()
{

}

bool Player::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	
	m_position = Vector3{ 200.0f,0.0f,50.0f };
	m_modelRender.SetPosition(m_position);
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	
	return true;
}

void Player::Update()
{
	Move();
	Rotate();
	PlayAnimation();
	SetAnimation();
}

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
	if (g_pad[0]->IsPress(enButtonB) && m_time <= m_initialVelocity)
	{
		m_moveSpeed.x *= m_acceleration; // Bボタンが押されている間は右方向の速度を1.5倍にする
		m_moveSpeed.z *= m_acceleration; // Bボタンが押されている間は前方向の速度を1.5倍にする
		m_time += g_gameTime->GetFrameDeltaTime(); // 経過時間を更新
	}
	//Bボタンが押されて1秒後は移動速度を2倍にする
	else if (g_pad[0]->IsPress(enButtonB) && m_time >= m_initialVelocity)
	{
		float speedBaika = 5.0f;
		m_moveSpeed.x *= speedBaika; // Bボタンが押されている間は右方向の速度を2倍にする
		m_moveSpeed.z *= speedBaika; // Bボタンが押されている間は前方向の速度を2倍にする
		m_time += g_gameTime->GetFrameDeltaTime(); // 経過時間を更新
	}
	else
	{
		//経過時間を減算していく
		m_time = m_reset;
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
		m_playerState = 0;
		m_jumpCount = 0;
	}
	else//地面についていなかったら
	{
		//重力を発生させる
		const float gravety = 5.5f;//重力の定数
		m_moveSpeed.y -= gravety;
	}

	//ジャンプの処理
//Aボタンを押したときジャンプのカウントが最大でなければジャンプする
	if (g_pad[0]->IsTrigger(enButtonA) && m_jumpCount < m_maxJumpCount)
	{

		m_moveSpeed.y += 250.0f;
	}
	//キャラクターコントローラーを使って座標を移動させる
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Player::Rotate()
{
	//カメラの前方向を持ってくる
	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0;
	forward.Normalize();
	//向きをセット
	m_rotation.SetRotationYFromDirectionXZ(forward);
	//絵描きさんに回転を教える
	m_modelRender.SetRotation(m_rotation);
}

//ステート管理
void Player::PlayAnimation()
{
	//ジャンプの処理
	if (g_pad[0]->IsTrigger(enButtonA) && m_jumpCount < m_maxJumpCount) // Aボタンが押されたら
	{
		m_playerState=3;
		m_jumpCount++;
	}
	//地面についていなかったら
	if (!m_characterController.IsOnGround())
	{		
		m_playerState=3;		
	}

	if (m_playerState!=3) { // ジャンプ中は無視
		//ｘかｚの移動速度があったら（スティックの入力があったら）
		if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		{
			//歩きアニメーションを再生する
			m_playerState=1;
			//走るアニメーションを再生する
			if (g_pad[0]->IsPress(enButtonB))
			{
				m_playerState=2;
			}
		}
		//ｘとｚの移動速度が無かったら（スティックの入力が無かったら）
		else
		{
			m_playerState=0;
		}
	}
}

//アニメーションの切り替え
void Player::SetAnimation()
{
	//switch文
	switch (m_playerState) {
		//プレイヤーステートが0（待機）だったら
	case 0:
		//待機アニメーションを再生する
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//プレイヤーステートが1（歩き）だったら
	case 1:
		//歩きアニメーションを再生する
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 2:
		//走るアニメーションを再生する
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	case 3:
		//ジャンプアニメーション
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	}
}


void Player::Render(RenderContext& renderContext)
{
	if (!m_gameCamera)
	{
		return;
	}
	if(m_gameCamera->m_playerRenderFlag)
	{
		m_modelRender.Draw(renderContext);
	}
}