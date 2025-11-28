#include "stdafx.h"
#include "GameClear.h"
#include "GameResult.h"
#include "UI/ClearUI/ClearUI.h"

GameClear::GameClear()
{

}

GameClear::~GameClear()
{
	DeleteGO(m_clearUI);
}

bool GameClear::Start()
{
	m_gameClearSprite.Init("Assets/sprite/GaemClear_2.DDS", 1920.0f, 1080.0f);
	m_clearUI = NewGO<ClearUI>(0,"clearUI");
	
	return true;
}

void GameClear::Update()
{
	if (g_pad[0]->IsPress(enButtonB))
	{
		NewGO<GameResult>(0, "gameresult");
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_gameClearSprite.Draw(rc);
}