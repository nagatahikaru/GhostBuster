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
	m_player = NewGO<Player>(0,"player");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_backGround = NewGO<BackGround>(0, "backGround");
	return true;
}

void Game::Update()
{
	if(g_pad[0]->IsTrigger(enButtonStart))
	{
		DeleteGO(this);
	}
}