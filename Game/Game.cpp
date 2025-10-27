#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"



Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);


}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	//m_gameBGM = NewGO<SoundSource>(0, "gameBGM");
	m_player = FindGO<Player>("player");
	
	return true;
}

void Game::Update()
{
	GameClearProcess();	
	GameOverProcess();
	ResidueCalculation();
}

void Game::GameClearProcess()
{
	//ゲームクリア処理
	//クリア条件：仮　残基が5以上　想定：星を3つ集める
	if(m_playerResidue >= 5)
	{
		//m_gameclear = NewGO<GameClear>(0, "gameClear");
	}

}

void Game::GameOverProcess()
{
	//ゲームオーバー処理
	//オーバー条件：残基が0以下
	//ゲームオーバー後はゲームをリトライするか選べるようにする
	if(m_playerResidue <= 0)
	{
		DeleteGO(this);
	}
}

//残基計算
void Game::ResidueCalculation()
{
 	int form = m_player->m_formState;
	//形態が範囲外になったら残基を減らすor増やす
	if (form <= -1)
	{
		m_playerResidue--;
		m_player->m_formState = 0;
	}
	if(form > 2)
	{
		m_playerResidue++;
		m_player->m_formState = 2;
	}

}