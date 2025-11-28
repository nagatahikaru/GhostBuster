#include "stdafx.h"
#include "GameTiter.h"
#include "UI/TiterUI/TiterUI.h"
#include "GameLoad.h"

GameTiter::GameTiter()
{

}

GameTiter::~GameTiter()
{
	DeleteGO(m_titerUI);
}

bool GameTiter::Start()
{
	m_gameTiterSprite.Init("Assets/sprite/GameTiter_2.DDS", 1920.0f, 1080.0f);
	m_titerUI =NewGO<TiterUI>(0, "titerUI");
	return true;
}

void GameTiter::Update()
{
	if (g_pad[0]->IsPress(enButtonA))
	{
		m_standby = 0.5f;
		m_conversion = true;
	}
	if (m_conversion == true)
	{
		m_standby -= g_gameTime->GetFrameDeltaTime();
	}
	if (m_standby<=0)
	{
		NewGO<GameLoad>(0, "gameload");
		DeleteGO(this);
		return;
	}

}

void GameTiter::Render(RenderContext& rc)
{
	m_gameTiterSprite.Draw(rc);
}