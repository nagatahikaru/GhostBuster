/**
* UI.h
* 画面に表示されるUIの基底クラス
*/
#pragma once
#include "InGameUI.h"
#include "UI/UI.h"
class Player;


enum EnTime {
	enTime_sec,
	enTime_tensec,
	enTime_min,
	enTime_tenmin,
	enTime_num
};


enum EnResidue {
	enResidue_owncount,
	enResidue_tencount,
	enResidue_mincount,
	enResidue_num
};


enum EnItem {
	enItem_none,
	enItem_snowball,
	enItem_star,
	enItem_mushroom,
	enItem_num
};


/**
* InGameUIクラス
*/


enum { enMaxScoreDigit = 6 };


enum EnScoreType {
	enScoreType_Item,
	enScoreType_NormalEnemy,
	enScoreType_GimmickEnemy,
	enScoreType_BossEnemy,
	enScoreType_TimeBonus,
	enScoreType_Num
};


// UI用名前空間
namespace nsUI {
	//時間UI用名前空間
	namespace nsTimer {
		constexpr int ONE_SECOND = 1;			//1	 秒
		constexpr int TEN_SECOND = 10;			//10 秒
		constexpr int ONE_MINUTE = 60;			//60 秒
		constexpr int TEN_MINUTE = 600;			//600 秒

		constexpr float LIMIT = 120.0f;	//120秒

		const Vector3 POS[enTime_num] = {
			{  960.0f, 490.0f, 0.0f },	//1秒
			{  860.0f, 490.0f, 0.0f },	//10秒
			{  660.0f, 490.0f, 0.0f },	//60秒
			{  560.0f, 490.0f, 0.0f }	//600秒
		};


		const int DIGIT[enTime_num] = {
			ONE_SECOND,		//1秒
			TEN_SECOND,		//10秒
			ONE_MINUTE,		//60秒
			TEN_MINUTE		//600秒
		};


		const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };
	}


	//残基UI用名前空間
	namespace nsResidue {
		constexpr int ONE_COUNT = 1;
		constexpr int TEN_COUNT = 10;
		constexpr int HUN_COUNT = 100;

		constexpr int MIN = 0;
		constexpr int MAX = 999;

		const Vector3 POS[enResidue_num] = {
			{-570.0f,445.0f,0.0f},
			{-670.0f,445.0f,0.0f},
			{-770.0f,445.0f,0.0f}
		};

		const int COUNT[enResidue_num] = {
			ONE_COUNT,
			TEN_COUNT,
			HUN_COUNT
		};

		const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };
	}


	//スコアUI用名前空間
	namespace nsScore {
		const Vector3 POS[enMaxScoreDigit] = {
			{  960.0f, 390.0f, 0.0f },	//1
			{  860.0f, 390.0f, 0.0f },	//10
			{  760.0f, 390.0f, 0.0f },	//100
			{  660.0f, 390.0f, 0.0f },	//1,000
			{  560.0f, 390.0f, 0.0f },	//10,000
			{  460.0f, 390.0f, 0.0f },	//10,0000
		};

		const int DIGIT[enMaxScoreDigit] = {
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
		const int TYPE[enScoreType_Num] = {
			//10, //Coin
			50, //Item
			100,//NormalEnemy
			150,//GimmickEnemy
			500,//BossEnemy
			20  //TimeBonus
		};
	}


	//アイテムUI用名前空間
	namespace nsItem {
		const Vector3 POS[enItem_num] = {
			{ -900.0f, -400.0f, 0.0f },//なし
			{ -900.0f, -400.0f, 0.0f },//雪玉
			{ -900.0f, -400.0f, 0.0f },//星
			{-900.0f, -400.0f, 0.0f } //本
		};

		static const int NONE = 0;

		const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };
	}
}


//時間UI用構造体
struct Timer {
	Timer() :
		nowTime(0)
	{
	}
	int nowTime;
	SpriteRender spriteRender;
};


//残基UI用構造体
struct Residue {
	Residue() :
		nowResidue(0)
	{
	}
	int nowResidue;
	SpriteRender spriteRender;
};


//アイテムUI用構造体
struct Item {
	Item() :
		nowItem(0)
	{
	}
	int nowItem;
	SpriteRender spriteRender;
};


//スコアUI用構造体
struct Score {
	Score() :
		nowScore(0)
	{
	}
	int nowScore;
	SpriteRender spriteRender;
};


class InGameUI :public UI
{

	float m_gameTimer = 0.0f;//ゲームタイマー
public:
	//コンストラクタ・デストラクタ
	InGameUI() : m_gameTimer(0.0f)
		, m_nowTime(nsUI::nsTimer::LIMIT)
		,m_nowResidue(0)
		,m_nowItem(0)
		,m_nowScore(0){};
	~InGameUI();
	bool Start() override;
	void Update()override;
	void Direction();
	void Selection();
	void Render(RenderContext& rc)override;
	void AddScore(int score);//スコア加算

protected:
	void PlayerResidueUI();//プレイヤー残基UI
	void InitializeTimer();//時間UI初期化
	void InitializeResidue();//残基UI初期化
	void InitializeItem();//アイテムUI初期化
	void InitializeScore();//スコアUI初期化
	void ItemUI();//アイテムUI
	void MapUI();//マップUI


private:
	/** 現在の時間を計測する */
	void MeasureNowTime();
	



public:	
	bool m_blackout=false;//暗転フラグ
	bool m_sceneMovement;//場面移動のためのフラグ
	float m_nowTime = 0.0f;//現在の時間
	int m_nowResidue = 0;//現在の残基数
	int m_nowItem = 0;//現在のアイテム
	int m_nowScore = 0;//現在のスコア


private:
	Player* m_player;//プレイヤー
	

	//arrayは普通の配列より安全(他の場所に探しに行かずその場で例外を判定するから)
	std::array<Timer, enTime_num> m_timeUI;			//arrayを使った時間のSprite
	std::array<Residue, enResidue_num> m_residueUI;	//プレイヤー残基UI
	std::array<Item, enItem_num> m_itemUI;			//アイテムUI
	std::array<Score, enMaxScoreDigit> m_scoreUI;	//スコアUI
	SpriteRender m_koronSprite;						//時間の真ん中コロンの表示
	SpriteRender m_overSelectionFrame;				//終了する選択UI
	SpriteRender m_lordSelectionFrame;				//GameLordに行く選択UI
	SpriteRender m_playerfestureUI;					//プレイヤー顔アイコン
	SpriteRender m_itemColumnUI;					//アイテム欄
	SpriteRender m_map;								//マップ表示
	float m_black=1.0f;								//黒色
	float m_transparency=0.5f;						//透明度
	float m_overFrameTransparency=1.0f;				//GameEndFrameColor
	float m_lordFrameTransparency=0.5f;				//GameLordFrameColor
	float m_cyan;									//シアン色
	float m_blue= 0.81960784313f;					//青色
	float m_red=0.0f;								//赤色
	float m_green= 0.63137254902f;					//緑色
};

