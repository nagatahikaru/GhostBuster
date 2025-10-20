#include "stdafx.h"
#include "GameLoad.h"
#include "Player.h"

GameLoad::GameLoad()
{
	m_player = nullptr;
}

GameLoad::~GameLoad()
{
}
bool GameLoad::Start()
{
	m_player = NewGO<Player>(0, "player");
	return true;
}
void GameLoad::Update()
{

}

