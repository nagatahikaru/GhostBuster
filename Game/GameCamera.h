#pragma once
#include "camera/SpringCamera.h"

class Player;
//ゲーム中のカメラを制御する
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	//メンバ変数

	Player* m_player;
	Vector3 m_toCameraPos;
	SpringCamera m_springCamera;   //ばねカメラ

	bool m_playerRenderFlag = true; //プレイヤーの描画フラグ
};