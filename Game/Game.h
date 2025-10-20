#pragma once
//#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class GameClear;

//Gameシーンを管理するクラス。
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	//更新処理
	void Update();

	// "*"がある時は->で　それ以外の時は"."で"*"を使わない
	Player* m_player;         //プレイヤー
	GameCamera* m_gameCamera; //ゲームカメラ
	SoundSource* m_gameBGM;   //ゲーム中のBGM
	GameClear* m_gameclear;   //ゲームカメラ
	BackGround* m_backGround; //背景	
};

