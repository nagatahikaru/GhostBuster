#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "SnowEnemyManager.h"
#include "SnowBallManager.h"
#include "MushroomEnemyManager.h"
#include "GhostEnemyManager.h"
#include "GolemEnemy.h"
#include "GameOver.h"
#include "GameClear.h"
#include "GameLoad.h"
#include "GameTiter.h"
#include "UI/InGameUI/InGameUI.h"


Game::Game()
{

}

Game::~Game()
{
	Player::DeleteInstance();
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_snowEnemyManager);
	DeleteGO(m_mushroomEnemyManager);
	DeleteGO(m_ghostEnemyManager);
	DeleteGO(m_golemEnemy);
	DeleteGO(m_snowBallManager);
	DeleteGO(m_inGameUI);
}

bool Game::Start()
{
	SkyCube* sky = NewGO<SkyCube>(0);     // スカイクラスのインスタンスを生成
	sky->SetLuminance(0.2f);              // スカイの輝度を設定
	sky->SetScale(2000.0f);               // スカイのスケールを設定
	sky->SetType(enSkyCubeType_DayToon_4);// スカイのタイプを設定

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_inGameUI = NewGO<InGameUI>(0, "inGameUI");
	m_player = Player::GetInstance();
	m_snowEnemyManager = FindGO<SnowEnemyManager>("snowEnemyManager");
	m_mushroomEnemyManager = FindGO<MushroomEnemyManager>("mushroomEnemyManager");
	m_ghostEnemyManager = FindGO<GhostEnemyManager>("ghostEnemyManager");
	m_golemEnemy = FindGO<GolemEnemy>("golemEnemy");
	//m_gameBGM = FindGO<SoundSource>("gameBGM");
	m_snowBallManager = FindGO<SnowBallManager>("snowBallManager");

	//auto* pointLight = g_sceneLight->NewPointLight();
	//pointLight->SetPosition(Vector3(500.0f, 900.0f, 0.0f));
	//pointLight->SetColor(10.0f, 0.1f, 0.1f);
	//pointLight->SetRange(100.0f);
	//pointLight->SetAffectPowParam(3.0f);
	//pointLight->Update();
	return true;
}

void Game::Update()
{
	GameClearProcess();	
	GameOverProcess();
	

	//当たり判定を描画する。
PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

void Game::GameClearProcess()
{
	//ゲームクリア処理
	//クリア条件：仮　残基が5以上　想定：星(虹色に光る)を3つ集める
	if(m_player->m_residue >= 5)
	{
		NewGO<GameClear>(0, "gameclear");		
		DeleteGO(this);
		return;
	}

}

void Game::GameOverProcess()
{
	//ゲームオーバー処理
	//オーバー条件：残基が0以下 	
	if(m_player->m_residue<=0||m_inGameUI->m_nowTime<=0.0f)
	{
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
		return;
	}
	//ポーズ時にゲームをリトライするか終了するか選べるようにする
	if(m_inGameUI->m_blackout)
	{


		if (g_pad[0]->IsTrigger(enButtonA) && m_inGameUI->m_sceneMovement == true)
		{
			PostQuitMessage(0);
			return;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_inGameUI->m_sceneMovement == false)
		{
			NewGO<GameTiter>(0, "gametiter");			
			DeleteGO(this);
			return;
		}		
		
	}
}

