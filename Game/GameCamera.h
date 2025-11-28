#pragma once
#include "camera/SpringCamera.h"
#include "UI/InGameUI/InGameUI.h"

class InGameUI;
class Player;
//ゲーム中のカメラを制御する
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();


	bool m_playerRenderFlag = true; //プレイヤーの描画フラグ


private:
	//メンバ変数
	InGameUI* m_inGameUI;
	Player* m_player;
	Vector3 m_toCameraPos;
	SpringCamera m_springCamera;   //ばねカメラ	
};