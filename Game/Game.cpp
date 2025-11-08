#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "SnowEnemyManager.h"
#include "SnowBallManager.h"



Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_snowEnemyManager);


}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_snowEnemyManager = NewGO<SnowEnemyManager>(0, "snowEnemyManager");
	//m_gameBGM = NewGO<SoundSource>(0, "gameBGM");
	m_player = FindGO<Player>("player");
	m_snowBallManager = NewGO<SnowBallManager>(0,"snowBallManager");
	
	return true;
}

void Game::Update()
{
	GameClearProcess();	
	GameOverProcess();
}

void Game::GameClearProcess()
{
	//ゲームクリア処理
	//クリア条件：仮　残基が5以上　想定：星(虹色に光る)を3つ集める
	if(m_player->m_residue >= 5)
	{
		//m_gameclear = NewGO<GameClear>(0, "gameClear");
	}

}

void Game::GameOverProcess()
{
	//ゲームオーバー処理
	//オーバー条件：残基が0以下
	//ゲームオーバー後はゲームをリトライするか選べるようにする
	if(m_player->m_residue <= 0)
	{
		DeleteGO(this);
	}
}

