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
	m_waitTime = 1.0f;
	return true;
}

void GameTiter::Update()
{
	m_waitTime -= g_gameTime->GetFrameDeltaTime();
	if (m_waitTime>=0.0f)
	{
		return;
	}
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_standby = 0.5f;
		m_conversion = true;
		m_titerUI->m_blinkingfrag = true;
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