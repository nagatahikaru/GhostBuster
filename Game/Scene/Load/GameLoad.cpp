#include "stdafx.h"
#include "GameLoad.h"
#include "Player.h"
#include "GameCamera.h"
#include "SnowEnemyManager.h"
#include "SnowBallManager.h"
#include "MushroomEnemyManager.h"
#include "GhostEnemyManager.h"
#include "GolemEnemy.h"
#include "Game.h"
#include "BackGround.h"


GameLoad::GameLoad()
{
}

GameLoad::~GameLoad()
{
}
bool GameLoad::Start()
{
	m_backGround = FindGO<BackGround>("backGround");

	m_gameLoadSprite.Init("Assets/sprite/GameLoad_2.DDS", 1920.0f, 1080.0f);

	m_loadBarSpriteRender.Init("Assets/sprite/Enemy.DDS", 100.0f, 150.0f);

	m_unitySpriteRender.Init("Assets/sprite/Sign_No.DDS", 200.0f, 200.0f);
	m_unitySpriteRender.SetPosition(Vector3(-50.0f, -125.0f, 0.0f));

	m_unity1SpriteRender.Init("Assets/sprite/Sign_Okay.DDS", 200.0f, 200.0f);
	m_unity1SpriteRender.SetPosition(Vector3(-50.0f, -125.0f, 0.0f));
	
	return true;
}
void GameLoad::Update()
{
	if (m_loadFlag)
	{
	m_player=NewGO<PlayerTest>(0, "player");	
	m_snowEnemyManager=NewGO<SnowEnemyManager>(0, "snowEnemyManager");
	m_mushroomEnemyManager=NewGO<MushroomEnemyManager>(0, "mushroomEnemyManager");
	m_ghostEnemyManager=NewGO<GhostEnemyManager>(0, "ghostEnemyManager");
	if(m_backGround->m_stageSelect==4)
	{
		m_golemEnemy = NewGO<GolemEnemy>(0, "golemEnemy");
	}
	//m_gameBGM = NewGO<SoundSource>(0, "gameBGM");
	m_snowBallManager=NewGO<SnowBallManager>(0, "snowBallManager");
	m_loadFlag = false;
}
	// ここにロード処理を実装
	m_loadTimer += g_gameTime->GetFrameDeltaTime();

	int unityFrame = (int)(m_loadTimer * 3) % 2; // 0または1を交互に切り替える
	if (unityFrame == 0)
	{
		m_showUnity = true; // ユニティちゃんの表示フラグをtrueに設定
	}
	else
	{
		m_showUnity = false; // ユニティちゃんの表示フラグをfalseに設定
	}

	//時間経過でロードバーを伸ばす。
	float scale = 1.0f + m_loadTimer * 1.534;
	if (scale > 15.0f) scale = 15.0f; // 最大15倍まで
	//スプライトが左から右に伸びるようにXの位置を補正する
	float wide = 100.0f * scale;
	//スプライトの大きさと位置を設定
	m_loadBarSpriteRender.SetScale(Vector3(scale, 1.15f, 1.0f));
	//スプライトの中心が画面中央になるように位置を調整
	m_loadBarSpriteRender.SetPosition(Vector3(-815.0f + wide / 2.0f, -292.0f, 0.0f));

	if (m_loadTimer > 15)
	{
		//if (m_GameLoadBGM != nullptr)
		//{
		//	m_GameLoadBGM->Stop();
		//	m_GameLoadBGM = nullptr;
		//}
		// ロードが完了したらゲームを開始
		NewGO<Game>(0, "game");
		DeleteGO(this);
		return;
	}
	m_loadBarSpriteRender.Update();
}

void GameLoad::Render(RenderContext& rc)
{
	m_gameLoadSprite.Draw(rc);
	m_loadBarSpriteRender.Draw(rc);
	if (m_showUnity == true)
	{
		m_unitySpriteRender.Draw(rc);
	}
	else
	{
		m_unity1SpriteRender.Draw(rc);
	}
	if (m_loadStartFlag)
	{
		m_loadFlag = true;
		m_loadStartFlag = false;
	}
}

