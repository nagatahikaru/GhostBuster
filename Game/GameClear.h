#pragma once
#include "UI/ClearUI/ClearUI.h"

class GameResult;
class ClearUI;

class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	
private:
	GameResult* m_gameResult;
	SpriteRender m_gameClearSprite;
	ClearUI* m_clearUI;


};

