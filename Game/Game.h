#pragma once
//#include "sound/SoundSource.h"
#include "UI/InGameUI/InGameUI.h"


class Player;
class GameCamera;
class BackGround;
class SnowEnemy;
class SnowBallManager;
class SnowEnemyManager;
class MushroomEnemyManager;
class GhostEnemyManager;
class GolemEnemy;
class GameOver;
class GameClera;
class GameLoad;
class InGameUI;
class GameClear;
class GameTiter;


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
	

private:
	// "*"がある時は->で　それ以外の時は"."で"*"を使わない
	Player* m_player;         //プレイヤー
	GameCamera* m_gameCamera; //ゲームカメラ
	//SoundSource* m_gameBGM;   //ゲーム中のBGM
	GameClear* m_gameclear;   //ゲームクリア
	BackGround* m_backGround; //背景	
	SnowEnemyManager* m_snowEnemyManager;//雪だるま型の敵
	SnowBallManager* m_snowBallManager;//雪玉
	MushroomEnemyManager* m_mushroomEnemyManager;//キノコ型の敵
	GhostEnemyManager* m_ghostEnemyManager;//幽霊型の敵
	GolemEnemy* m_golemEnemy;//ゴーレム型の敵
	GameOver* m_gameOver;
	GameClera* m_gameclera;
	GameLoad* m_gameLoad;
	InGameUI* m_inGameUI;
	GameTiter* m_gameTiter;
};

