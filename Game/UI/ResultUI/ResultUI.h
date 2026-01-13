/**
* ResultUI.h
* 結果画面のUIクラス
*/
#pragma once
#include "UI/UI.h"
#include "Player.h"
#include "UI/InGameUI/InGameUI.h"


enum ReTime {
	reTime_sec,
	reTime_tensec,
	reTime_min,
	reTime_tenmin,
	reTime_num
};

enum ReResidue {
	reResidue_owncount,
	reResidue_tencount,
	reResidue_mincount,
	reResidue_num
};

enum ReItem {
	reItem_none,
	reItem_snowball,
	reItem_num
};


enum ReScoreType {
	reScoreType_Item,
	reScoreType_NormalEnemy,
	reScoreType_GimmickEnemy,
	reScoreType_BossEnemy,
	reScoreType_TimeBonus,
	reScoreType_Num
};

enum { reMaxScoreDigit = 6 };


// UI用名前空間
namespace reUI {
	//時間UI用名前空間
	namespace reTimer {
		constexpr int ONE_SECOND = 1;			//1	 秒
		constexpr int TEN_SECOND = 10;			//10 秒
		constexpr int ONE_MINUTE = 60;			//60 秒
		constexpr int TEN_MINUTE = 600;			//600 秒


		const Vector3 POS[reTime_num] = {
			{  960.0f, 490.0f, 0.0f },	//1秒
			{  860.0f, 490.0f, 0.0f },	//10秒
			{  660.0f, 490.0f, 0.0f },	//60秒
			{  560.0f, 490.0f, 0.0f }	//600秒
		};


		const int DIGIT[reTime_num] = {
			ONE_SECOND,		//1秒
			TEN_SECOND,		//10秒
			ONE_MINUTE,		//60秒
			TEN_MINUTE		//600秒
		};


		const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };
	}





	//スコアUI用名前空間
	namespace reScore {
		const Vector3 POS[reMaxScoreDigit] = {
			{  960.0f, 390.0f, 0.0f },	//1
			{  860.0f, 390.0f, 0.0f },	//10
			{  760.0f, 390.0f, 0.0f },	//100
			{  660.0f, 390.0f, 0.0f },	//1,000
			{  560.0f, 390.0f, 0.0f },	//10,000
			{  460.0f, 390.0f, 0.0f },	//10,0000
		};

		const int DIGIT[reMaxScoreDigit] = {
			1,		//1
			10,		//10
			100,	//100
			1000,	//1,000
			10000,	//10,000
			100000	//100,000
		};

		static const int MIN = 0;
		static const int MAX = 999999;

		const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };

		//各スコアタイプごとの得点
		const int TYPE[reScoreType_Num] = {
			//10, //Coin
			50, //Item
			100,//NormalEnemy
			150,//GimmickEnemy
			500,//BossEnemy
			20  //TimeBonus
		};
	}

	//アイテムUI用名前空間
	namespace reItem {
		const Vector3 POS[reItem_num] = {
			{ -900.0f, -400.0f, 0.0f },//なし
			{ -900.0f, -400.0f, 0.0f } //雪玉
		};

		static const int NONE = 0;

		const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };
	}
}


/**
* ResultUIクラス
*/
class ResultUI :public UI
{
public:
	ResultUI();
	~ResultUI();
	bool Start() override;
	void Update()override;
	void InitializeScore();//スコアUI初期化
	void InitializeClearTime();//クリアタイムUI初期化
	void InitializeGetStar();//獲得スターUI初期化
	void Direction();
	void Render(RenderContext& rc)override;


public:
	bool m_blackout = false;//暗転フラグ
	bool m_sceneMovement;//場面移動のためのフラグ
	float m_nowTime = 0.0f;//現在の時間
	int m_nowResidue = 0;//現在の残基数
	int m_nowItem = 0;//現在のアイテム
	int m_nowScore = 0;//現在のスコア


private:
	Player* m_player;//プレイヤー
	InGameUI* m_inGameUI;//InGameUIのインスタンス

	//arrayは普通の配列より安全(他の場所に探しに行かずその場で例外を判定するから)
	std::array<Timer, reTime_num> m_timeUI;			//arrayを使った時間のSprite
	std::array<Score, reMaxScoreDigit> m_scoreUI;	//スコアUI
	SpriteRender m_koronSprite;						//時間の真ん中コロンの表示
	SpriteRender m_overSelectionFrame;				//終了する選択UI
	SpriteRender m_lordSelectionFrame;				//GameLordに行く選択UI
	SpriteRender m_playerfestureUI;					//プレイヤー顔アイコン
	SpriteRender m_itemColumnUI;					//アイテム欄
	SpriteRender m_map;								//マップ表示
	float m_black = 1.0f;								//黒色
	float m_transparency = 0.5f;						//透明度
	float m_overFrameTransparency = 1.0f;				//GameEndFrameColor
	float m_lordFrameTransparency = 0.5f;				//GameLordFrameColor
	float m_cyan;									//シアン色
	float m_blue = 0.81960784313f;					//青色
	float m_red = 0.0f;								//赤色
	float m_green = 0.63137254902f;					//緑色
};

