#pragma once
#include "UI/TiterUI/TiterUI.h"


class TiterUI;
class StageSelection;

class GameTiter : public IGameObject
{
public:
	GameTiter();
	~GameTiter();
	bool Start();
	void Update();
	void Render(RenderContext& rc);


private:
	TiterUI* m_titerUI;
	StageSelection* m_stageSelection;
	bool m_conversion=false;
	float m_standby=2.0f;
	SpriteRender m_gameTiterSprite;
	FontRender m_font;
	float m_waitTime;//“ü—Í‘Ò‹@ŽžŠÔ
};

