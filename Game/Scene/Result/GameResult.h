#pragma once
#include "UI/ResultUI/ResultUI.h"


class GameTiter;
class ResultUI;

class GameResult :public IGameObject
{
public:
	GameResult();
	~GameResult();
	bool Start();
	void Update();
	void Render(RenderContext&rc);

	
private:
	GameTiter* m_gametiter;
	SpriteRender m_GameResultSprite;
	ResultUI* m_resultUI;

};

