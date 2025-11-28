#pragma once
#include "UI/OverUI/OverUI.h"


class GameResult;
class OverUI;

class GameOver :public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);


private:
	OverUI* m_overUI;
	GameResult* m_gameresult;
	SpriteRender m_gameOverSprite;	
};

