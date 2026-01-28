#include "stdafx.h"
#include "Game.h"
#include "Character/Player/Player.h"
#include "Object/GameCamera/GameCamera.h"
#include "Object/BackGround/BackGround.h"
#include "Manager/SnowEnemyManager/SnowEnemyManager.h"
#include "Manager/SnowBallManager/SnowBallManager.h"
#include "Manager/MushroomEnemyManager/MushroomEnemyManager.h"
#include "Manager/GhostEnemyManager/GhostEnemyManager.h"
#include "Character/Enemy/GolemEnemy/GolemEnemy.h"
#include "Scene/GameResult/GameResult.h"
#include "Scene/GameLoad/GameLoad.h"
#include "Scene/Titer/GameTiter.h"
#include "UI/InGameUI/InGameUI.h"
#include "Manager/DropItemManager/DropItemsManager.h"


Game::Game()
{

}

Game::~Game()
{
	

	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_snowEnemyManager);
	if (m_cachedStage == 4) { DeleteGO(m_golemEnemy); }
	DeleteGO(m_snowBallManager);
	DeleteGO(m_mushroomEnemyManager);
	DeleteGO(m_ghostEnemyManager);
	DeleteGO(m_inGameUI);
	DeleteGO(m_playerTest);
	DeleteGO(m_dropItemsManager);
}

bool Game::Start()
{
	SkyCube* sky = NewGO<SkyCube>(0);     // スカイクラスのインスタンスを生成
	sky->SetLuminance(0.2f);              // スカイの輝度を設定
	sky->SetScale(2000.0f);               // スカイのスケールを設定
	sky->SetType(enSkyCubeType_DayToon_4);// スカイのタイプを設定
	m_playerTest = FindGO<PlayerTest>("player");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_backGround = FindGO<BackGround>("backGround");
	m_cachedStage = (m_backGround) ? m_backGround->m_stageSelect : 0;
	m_inGameUI = NewGO<InGameUI>(0, "inGameUI");
	m_player = Player::GetInstance();
	m_snowEnemyManager = FindGO<SnowEnemyManager>("snowEnemyManager");
	m_mushroomEnemyManager = FindGO<MushroomEnemyManager>("mushroomEnemyManager");
	m_ghostEnemyManager = FindGO<GhostEnemyManager>("ghostEnemyManager");
	m_dropItemsManager = FindGO<DropItemsManager>("dropItemsManager");
	if (m_cachedStage == 4)
	{
		m_golemEnemy = FindGO<GolemEnemy>("golemEnemy");
	}
	//m_gameBGM = FindGO<SoundSource>("gameBGM");
	m_snowBallManager = FindGO<SnowBallManager>("snowBallManager");
	m_directionTime = 8.0f;
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
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

void Game::GameClearProcess()
{
	//ゲームクリア処理
	//クリア条件：仮　残基が5以上　想定：星(虹色に光る)を3つ集める
	if(m_inGameUI->GetScore() >= 10000)
	{
		m_player->m_playerAnimationState = Player::enAnimationClip_Clear;
		m_directionTime -= g_gameTime->GetFrameDeltaTime();
		if(m_directionTime<=0.0f)
		{
			NewGO<GameResult>(0, "gameresult");
			DeleteGO(this);
		}
		return;
	}

}

void Game::GameOverProcess()
{
	//ゲームオーバー処理
	//オーバー条件：残基が0以下 	
	if(m_player->m_residue<=0||m_inGameUI->GetNowTime() <=0.0f)
	{
		m_player->m_playerAnimationState = Player::enAnimationClip_Death;
		m_directionTime -= g_gameTime->GetFrameDeltaTime();
		if(m_directionTime<=0.0f)
		{
			NewGO<GameResult>(0, "gameresult");
			DeleteGO(this);
		}
		return;
	}
	//ポーズ時にゲームをリトライするか終了するか選べるようにする
	if(m_inGameUI->GetSBlackout()){
		if (g_pad[0]->IsTrigger(enButtonA) && m_inGameUI->GetSceneMovement() == true)
		{
			PostQuitMessage(0);
			return;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_inGameUI->GetSceneMovement() == false)
		{
			NewGO<GameTiter>(0, "gametiter");			
			DeleteGO(this);
			return;
		}		
	}
}

