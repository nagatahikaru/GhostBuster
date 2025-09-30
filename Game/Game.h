#pragma once
#include "sound/SoundSource.h"

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
	//更新処理
	void Update();

	// "*"がある時は->で　それ以外の時は"."で"*"を使わない
	Player* player;         //プレイヤー
	GameCamera* gameCamera; //ゲームカメラ
	SoundSource* gameBGM;   //ゲーム中のBGM
	GameClear* gameclear;   //ゲームカメラ
	BackGround* backGround; //背景	
};

