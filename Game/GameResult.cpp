#include "stdafx.h"
#include "GameResult.h"
#include "GameTiter.h"
#include "UI/ResultUI/ResultUI.h"

GameResult::GameResult()
{

}

GameResult::~GameResult()
{
	DeleteGO(m_resultUI);
}

bool GameResult::Start()
{
	m_GameResultSprite.Init("Assets/sprite/GameLoad_2.DDS", 1920.0f, 1080.0f);
	m_resultUI=NewGO<ResultUI>(0,"resultUI");
	return true;
}

void GameResult::Update()
{
	if (g_pad[0]->IsPress(enButtonX))
	{
		NewGO<GameTiter>(0, "gametiter");
		DeleteGO(this);
	}
}

void GameResult::Render(RenderContext& rc)
{
	m_GameResultSprite.Draw(rc);
}

