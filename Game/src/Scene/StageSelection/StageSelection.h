#pragma once

#include "src/Actor/Object/BackGround/BackGround.h"
#include "src/Scene/GameLoad/GameLoad.h"

class StageSelection:public IGameObject
{
public:
	StageSelection() {};
	~StageSelection();
	bool Start();
	void Update();
	void Selection();
	void Blinking();
	void Conversion();
	void Render(RenderContext& rc);

	SpriteRender m_stageSelectionRender;//ステージ選択画面用スプライトレンダー
	SpriteRender m_selectionRender[4];//選択肢用スプライトレンダー
	BackGround* m_backGround;//背景
	GameLoad* m_gameLoad;//ゲームロードシーン

	int m_selectionType = 0;//選択肢の種類
	int m_selectionType2 = 1;//選択肢の種類
	int m_selectionType3 = 2;//選択肢の種類
	int m_selectionType4 = 3;//選択肢の種類
	int m_select = 1;//選択されたステージ保存用変数
private:
	bool m_conversion = false;//画面転換処理フラグ
	float m_standby = 2.0f;//点滅時間の待機時間
	float m_waitTime=1.0f;//入力待機時間
	float m_transparency = 1.0f;//透明度管理用変数
	bool m_fadeIn;//フェードイン処理フラグ
	float m_blinking;//点滅速度管理用変数
	bool m_blinkingfrag = false;//点滅速度加速フラグ
	float m_selectionWaitTime = 0.2f;//選択肢入力待機時間

	Vector4 m_RedColor = Vector4(1.0f, 0.0f, 0.0f, m_transparency);//赤色
	Vector4 m_NormalColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);//通常色
};

