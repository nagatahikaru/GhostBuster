#include "stdafx.h"
#include "Player.h"

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
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	m_modelRender.SetShadowCasterFlag(false);
	m_position = Vector3{ 200.0f,0.0f,50.0f };
	m_modelRender.SetPosition(m_position);
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_renderFlag = true;
	return true;
}

void Player::Update()
{
	Move();
	Rotate();
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
	}
	else//地面についていなかったら
	{
		//重力を発生させる
		const float gravety = 25.5f;//重力の定数
		m_moveSpeed.y -= gravety;
	}
	//キャラクターコントローラーを使って座標を移動させる
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
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

void Player::Render(RenderContext& renderContext)
{
	if(m_renderFlag)
	{
		m_modelRender.Draw(renderContext);
	}
}