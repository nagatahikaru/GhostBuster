#include "stdafx.h"
#include "UI/TiterUI/TiterUI.h"


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
	//タイトル画面の演出
	Vector4 titerColor(1.0f,1.0f, 0.31372549019f, m_transparency);
	if (m_fadeIn)
	{
		// フェードイン → アルファ増加（表示へ）
		m_transparency += g_gameTime->GetFrameDeltaTime()* m_blinking;
		if (m_transparency >= 1.0f)
		{
			m_transparency = 1.0f;
			m_fadeIn = false; // 次はフェードアウトへ
		}
	}
	else
	{
		// フェードアウト → アルファ減少（透明へ）
		m_transparency -= g_gameTime->GetFrameDeltaTime()* m_blinking;
		if (m_transparency <= 0.0f)
		{
			m_transparency = 0.0f;
			m_fadeIn = true; // 次はフェードインへ
		}
	}
	if (g_pad[0]->IsPress(enButtonA))
	{
		//画面転換するときに点滅速度を加速する
		m_blinking = 15;
	}
	m_spriteRender.Update();
	m_spriteRender.SetMulColor(titerColor);

}

//描画処理
void TiterUI::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
