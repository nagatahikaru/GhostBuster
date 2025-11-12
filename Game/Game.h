#pragma once
//#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class SnowEnemy;
class SnowBallManager;
class SnowEnemyManager;
class MushroomEnemyManager;
class GhostEnemyManager;
class GolemEnemy;
//class GameClear;

//Gameシーンを管理するクラス。
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	//更新処理
	void Update();
	void GameClearProcess();//ゲームクリア
	void GameOverProcess();//ゲームオーバー
	

	// "*"がある時は->で　それ以外の時は"."で"*"を使わない
	Player* m_player;         //プレイヤー
	GameCamera* m_gameCamera; //ゲームカメラ
	SoundSource* m_gameBGM;   //ゲーム中のBGM
	//GameClear* m_gameclear;   //ゲームクリア
	BackGround* m_backGround; //背景	
	SnowEnemyManager* m_snowEnemyManager;//雪だるま型の敵
	SnowBallManager* m_snowBallManager;//雪玉
	MushroomEnemyManager* m_mushroomEnemyManager;//キノコ型の敵
	GhostEnemyManager* m_ghostEnemyManager;//幽霊型の敵
	GolemEnemy* m_golemEnemy;//ゴーレム型の敵
};

