#include "stdafx.h"
#include "src/UI/TiterUI/TiterUI.h"


TiterUI::TiterUI()
{	

}

TiterUI::~TiterUI()
{

}

//開始処理
bool TiterUI::Start()
{
	
	m_spriteRender.Init("Assets/sprite/GameStrat.DDS", 700.0f, 300.0f);
	Vector3 pos(496.0f, 0.0f, 0.0f);
	m_spriteRender.SetPosition(pos);
	m_spriteRender.Update();
	m_transparency = 0.0;
	m_blinking = 1.0f;
	m_blinkingfrag = false;
	return true;
}

//更新処理
void TiterUI::Update()
{	
	Direction();
}


//演出表示(死亡時の暗転のような)
void TiterUI::Direction()
{
	// フェード処理
	const float deltaTime = g_gameTime->GetFrameDeltaTime();
	const float fadeSpeed = m_blinkingfrag ? 15.0f : 1.0f;

	if (m_fadeIn)
	{
		m_transparency += deltaTime * fadeSpeed;
		if (m_transparency >= 1.0f)
		{
			m_transparency = 1.0f;
			m_fadeIn = false;
		}
	}
	else
	{
		m_transparency -= deltaTime * fadeSpeed;
		if (m_transparency <= 0.0f)
		{
			m_transparency = 0.0f;
			m_fadeIn = true;
		}
	}

	// 色設定を先に行う
	constexpr float YELLOW_BLUE = 0.31372549019f;  // 定数化
	m_spriteRender.SetMulColor(Vector4(1.0f, 1.0f, YELLOW_BLUE, m_transparency));
	m_spriteRender.Update();
}

//描画処理
void TiterUI::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
