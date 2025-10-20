#include "stdafx.h"
#include <cmath>
#include "GameCamera.h"
#include "Player.h"
#include <iostream>
#include <cmath>

namespace
{
	Vector3 START_GAME_CAMERA(0.0f, 80.0f, -100.0);
	const Vector3 IN_GAME_CAMERA(0.0f, 0.0f, -10.0f);
	const Vector3 OUT_GAME_CAMERA(0.0f, 150.0f, -100.0f);
	const float CAMERA_MOVE_SPEED = 1000.0f;
	const float CAMERA_COLLISION = 5.0f;
	const float CAMERA_NEAR = 1.0f;
	const float CAMERA_FAR = 15000.0f;
	const float CAMERA_POINT_ABOVE = 80.0f;
	const float CAMERA_POINT_BEHIND = 50.0f;
	const float CAMERA_DISTANCE = 50.0f;
	const float CAMERA_UP_LIMIT = -0.6;
	const float CAMERA_DOWN_LIMIT = 0.7;
	const float CAMERA_CLOSER_SPEED = 1.0f;
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

void GameCamera::FixedCamera()
{
	if (m_fixedCameraFlag == false)
	{
		m_toCameraPos.Set(IN_GAME_CAMERA);
	}
	else if (m_fixedCameraFlag == true)
	{
		//m_toCameraPos.Set(CLEAR_GAME_CAMERA);
	}
}

bool GameCamera::Start()
{
	/*m_toCameraPos.Set(0.0f, 0.0f, -10.0f);*/

	FixedCamera();
	m_player = FindGO<Player>("player");
	//ばねカメラの初期化
	m_springCamera.Init(
		*g_camera3D,		//ばねカメラの処理を行うカメラを指定する。
		CAMERA_MOVE_SPEED,			//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		CAMERA_COLLISION				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。

	);

	g_camera3D->SetNear(CAMERA_NEAR);
	g_camera3D->SetFar(CAMERA_FAR);
	return true;
}

void GameCamera::Update()
{
	CameraMove();

	//ばねカメラの更新
	m_springCamera.Update();

	//カメラの距離によってプレイヤーの透明、不透明を切り替える
	CameraDistance();
}

void GameCamera::CameraMove()
{
	//カメラの更新
		//注視点を計算する
	Vector3 target = m_player->m_position;
	//target.x= m_player->m_position.x;
	////プレイヤーの足元からちょっと上を注視点とする
	target.y += CAMERA_POINT_ABOVE;
	//target.z += CAMERA_POINT_BEHIND;

	Vector3 toCameraPosOld = m_toCameraPos;

	Vector3 pos = target + m_toCameraPos;

	//m_t += 0.01f;
	////if (m_springCamera.GetCamera()->GetTargetToPositionLength() < CAMERA_DISTANCE)
	////{
	//	Vector3 r;
	//	r.Lerp(m_t, m_toCameraPos, target);
	//	pos = r;
	////}

	if (m_cameraMoveFlag == true)
	{

		if (m_fixedCameraFlag == false) {


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
			if (toPosDir.y < CAMERA_UP_LIMIT) {
				//カメラが上を向きすぎ
				m_toCameraPos = toCameraPosOld;
			}
			else if (toPosDir.y > CAMERA_DOWN_LIMIT) {
				//カメラが下を向きすぎ
				m_toCameraPos = toCameraPosOld;
			}

			//視点を計算する
			//Vector3 pos = target + m_toCameraPos;
			//メインカメラに注視点と視点を設定すること
			/*g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(pos);*/

			//バネカメラに注視点と視点を設定する。
			m_springCamera.SetPosition(pos);
			m_springCamera.SetTarget(target);
		}
	}

	if (m_fixedCameraFlag == true)
	{
		//視点を計算する
		//Vector3 pos = target + m_toCameraPos;
		//メインカメラに注視点と視点を設定すること
		/*g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);*/
		//バネカメラに注視点と視点を設定する。
		m_springCamera.SetPosition(OUT_GAME_CAMERA);
		m_springCamera.SetTarget(target);
	}


}

void GameCamera::CameraDistance()
{
	if (m_springCamera.GetCamera()->GetTargetToPositionLength() < CAMERA_DISTANCE)
	{
		//m_playerRenderFlag = false; //プレイヤーを透明にする
		m_player->m_renderFlag = false;
	}
	else
	{
		//m_playerRenderFlag = true; //プレイヤーを不透明にする
		m_player->m_renderFlag = true;
	}
}