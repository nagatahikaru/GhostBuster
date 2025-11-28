#include "stdafx.h"
#include "GameOver.h"
#include "UI/OverUI/OverUI.h"
#include "GameResult.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{
	DeleteGO(m_overUI);
}

bool GameOver::Start()
{
	m_gameOverSprite.Init("Assets/sprite/GameOver_2.DDS", 1920.0f, 1080.0f);
	m_overUI = NewGO<OverUI>(0, "overUI");	
	return true;
}

void GameOver::Update()
{
	if (g_pad[0]->IsPress(enButtonA))
	{
		NewGO<GameResult>(0, "gameResult");		
		DeleteGO(this);
		return;
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_gameOverSprite.Draw(rc);
}