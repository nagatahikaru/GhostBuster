#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "UI/InGameUI/InGameUI.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定
	m_toCameraPos.Set(0.0f, 125.0f, -350.0f);
	//プレイヤーのインスタンスを探す
	m_player = FindGO<Player>("player");

	//ばねカメラの初期化
	m_springCamera.Init(
		*g_camera3D,		//ばねカメラの処理を行うカメラを指定する。
		1000.0f,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。

	);

	//カメラのニアクリップとファークリップを設定する //おそらく近平面と遠平面
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(100000.0f);
	m_inGameUI = FindGO<InGameUI>("inGameUI");
	return true;
}

void GameCamera::Update()
{
	if (m_inGameUI->m_blackout)
	{
		return;
	}

	//カメラの更新
	//注視点を計算する
	Vector3 target = m_player->GetPosition();
	//target.x= m_player->m_position.x;
	////プレイヤーの足元からちょっと上を注視点とする
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す
	float posX = g_pad[0]->GetRStickXF();
	float posY = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * posX);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * posY);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.6f) {
		//カメラが上を向きすぎ
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.7f) {
		//カメラが下を向きすぎ
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する
	Vector3 pos = target + m_toCameraPos;
	//メインカメラに注視点と視点を設定すること
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//バネカメラに注視点と視点を設定する。
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);

	////ばねカメラの更新
	m_springCamera.Update();

	if (m_springCamera.GetCamera()->GetTargetToPositionLength() < 50.0f)
	{
		m_playerRenderFlag = false; //プレイヤーを透明にする
	}
	else
	{
		m_playerRenderFlag = true; //プレイヤーを不透明にする
	}
	if (m_springCamera.GetCamera()->GetTargetToPositionLength()>=200.0f)
	{
		m_springCamera.Refresh();
	}
}