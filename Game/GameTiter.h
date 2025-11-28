#pragma once
#include "UI/TiterUI/TiterUI.h"


class TiterUI;
class GameLoad;

class GameTiter : public IGameObject
{
public:
	GameTiter();
	~GameTiter();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	TiterUI* m_titerUI;
	GameLoad* m_gameLoad;
private:
	bool m_conversion=false;
	float m_standby=2.0f;
	SpriteRender m_gameTiterSprite;
	FontRender m_font;

};

