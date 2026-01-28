#include "stdafx.h"
#include "StageSelection.h"
#include "Object/BackGround/BackGround.h"
#include "Scene/GameLoad/GameLoad.h"

StageSelection::~StageSelection()
{

}

bool StageSelection::Start()
{
	//ステージ選択画面の初期化
	m_stageSelectionRender.Init("Assets/sprite/StageSelection.DDS", 1920, 1080);
	//各選択肢の初期化
	m_selectionRender[m_selectionType].Init("Assets/sprite/WhiteCircle.DDS", 100.0f, 100.0f);
	m_selectionRender[m_selectionType2].Init("Assets/sprite/WhiteCircle.DDS", 100.0f, 100.0f);
	m_selectionRender[m_selectionType3].Init("Assets/sprite/WhiteCircle.DDS", 100.0f, 100.0f);
	m_selectionRender[m_selectionType4].Init("Assets/sprite/WhiteCircle.DDS", 100.0f, 100.0f);
	//各選択肢の位置設定
	m_selectionRender[m_selectionType].SetPosition(Vector3(-800.0f, 0.0f, 0.0f));
	m_selectionRender[m_selectionType2].SetPosition(Vector3(0.0f, 470.0f, 0.0f));
	m_selectionRender[m_selectionType3].SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_selectionRender[m_selectionType4].SetPosition(Vector3(800.0f, 480.0f, 0.0f));
	//各選択肢の色設定

	m_selectionRender[m_selectionType].SetMulColor(m_RedColor);
	m_selectionRender[m_selectionType2].SetMulColor(m_NormalColor);
	m_selectionRender[m_selectionType3].SetMulColor(m_NormalColor);
	m_selectionRender[m_selectionType4].SetMulColor(m_NormalColor);	
	//各選択肢の更新
	m_selectionRender[m_selectionType].Update();
	m_selectionRender[m_selectionType2].Update();
	m_selectionRender[m_selectionType3].Update();
	m_selectionRender[m_selectionType4].Update();

	m_backGround = NewGO<BackGround>(0, "backGround");
	return true;
}

//更新処理
void StageSelection::Update()
{
	//入力待機時間	
	if (m_waitTime >= 0.0f)
	{
		m_waitTime -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	Blinking();

	//各選択肢の色設定と更新
	m_selectionRender[m_selectionType].SetMulColor(m_RedColor);
	m_selectionRender[m_selectionType2].SetMulColor(m_NormalColor);
	m_selectionRender[m_selectionType3].SetMulColor(m_NormalColor);
	m_selectionRender[m_selectionType4].SetMulColor(m_NormalColor);
	m_selectionRender[m_selectionType].Update();
	m_selectionRender[m_selectionType2].Update();
	m_selectionRender[m_selectionType3].Update();
	m_selectionRender[m_selectionType4].Update();
	Conversion();
}

//画面転換処理
void StageSelection::Conversion()
{
	//点滅時間の待機時間が0以下になったら
	if (m_standby <= 0)
	{
		//ゲームロードシーンへ移行
		NewGO<GameLoad>(0, "gameload");
		DeleteGO(this);
		return;
	}
}

//点滅処理
void StageSelection::Blinking()
{
	//ステージ選択処理
	Selection();
	//決定処理
	//Aボタンが押されたとき
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//画面転換処理開始
		//点滅時間の待機時間を設定
		m_standby = 0.5f;
		//点滅処理のフラグを通す
		m_conversion = true;
		//点滅速度を加速するフラグを通す
		m_blinkingfrag = true;
	}
	//点滅処理
	//画面転換処理中
	if (m_conversion == true)
	{
		//点滅処理
		if (m_fadeIn)
		{
			// フェードイン → アルファ増加（表示へ）
			m_transparency += g_gameTime->GetFrameDeltaTime() * m_blinking;
			if (m_transparency >= 1.0f)
			{
				m_transparency = 1.0f;
				m_fadeIn = false; // 次はフェードアウトへ
			}
		}
		else
		{
			// フェードアウト → アルファ減少（透明へ）
			m_transparency -= g_gameTime->GetFrameDeltaTime() * m_blinking;
			if (m_transparency <= 0.0f)
			{
				m_transparency = 0.0f;
				m_fadeIn = true; // 次はフェードインへ
			}
		}
		if (m_blinkingfrag)
		{
			//画面転換するときに点滅速度を加速する
			m_blinking = 15;
		}

		//点滅時間の待機時間を減らす
		m_standby -= g_gameTime->GetFrameDeltaTime();
	}
}

//ステージ選択処理
void StageSelection::Selection()
{
	//左キーが押されたとき
	if (GetAsyncKeyState(VK_LEFT) || g_pad[0]->IsTrigger(enButtonLeft))
	{
		if(m_selectionWaitTime<=0.0f)
		{
			//左キーが押されたとき
			int emptiness = m_selectionType4;
			m_selectionType4 = m_selectionType3;
			m_selectionType3 = m_selectionType2;
			m_selectionType2 = m_selectionType;
			m_selectionType = emptiness;
			m_selectionWaitTime = 0.2f;
		}
		else
		{
			m_selectionWaitTime -= g_gameTime->GetFrameDeltaTime();
			return;
		}

	}
	if (GetAsyncKeyState(VK_RIGHT) || g_pad[0]->IsTrigger(enButtonRight))
	{
		if (m_selectionWaitTime <= 0.0f)
		{
			//右キーが押されたとき
			int emptiness = m_selectionType;
			m_selectionType = m_selectionType2;
			m_selectionType2 = m_selectionType3;
			m_selectionType3 = m_selectionType4;
			m_selectionType4 = emptiness;
			m_selectionWaitTime = 0.2f;
		}
		else
		{
			m_selectionWaitTime -= g_gameTime->GetFrameDeltaTime();
			return;
		}

	}
	//決定処理
	//選択されているステージをm_selectに格納
	//決定できるようにする
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_select = m_selectionType;
	}		
	

	//選択されたステージを背景に反映させる
	m_backGround->StageSelectSet(m_select+1);
}

//描画処理
void StageSelection::Render(RenderContext& rc)
{
	//描画処理
	m_stageSelectionRender.Draw(rc);
	m_selectionRender[m_selectionType].Draw(rc);
	m_selectionRender[m_selectionType2].Draw(rc);
	m_selectionRender[m_selectionType3].Draw(rc);
	m_selectionRender[m_selectionType4].Draw(rc);
}