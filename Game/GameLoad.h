#pragma once
#include "BackGround.h"

class PlayerTest;
class BackGround;
class SnowEnemy;
class SnowBallManager;
class SnowEnemyManager;
class MushroomEnemyManager;
class GhostEnemyManager;
class GolemEnemy;
class Game;


class GameLoad :public IGameObject
{
	public:
	GameLoad();
	~GameLoad();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);
	
	PlayerTest* m_player = nullptr;
	//SoundSource* m_gameBGM;   //ƒQ[ƒ€’†‚ÌBGM
	//GameClear* m_gameclear;   //ƒQ[ƒ€ƒNƒŠƒA
	BackGround* m_backGround; //”wŒi	
	SnowEnemyManager* m_snowEnemyManager;//á‚¾‚é‚ÜŒ^‚Ì“G
	SnowBallManager* m_snowBallManager;//á‹Ê
	MushroomEnemyManager* m_mushroomEnemyManager;//ƒLƒmƒRŒ^‚Ì“G
	GhostEnemyManager* m_ghostEnemyManager;//—H—ìŒ^‚Ì“G
	GolemEnemy* m_golemEnemy;//ƒS[ƒŒƒ€Œ^‚Ì“G
	Game* m_game;
	


private:
	SpriteRender m_gameLoadSprite;
	SpriteRender m_loadBarSpriteRender;
	SpriteRender m_unitySpriteRender;
	SpriteRender m_unity1SpriteRender;
	bool m_loadFlag=false;
	bool m_showUnity = false;
	bool m_loadStartFlag = true;
	float m_loadTimer;

};

