/**
* UI.h
* 画面に表示されるUIの基底クラス
*/
#pragma once
#include "UI/UI.h"
class Player;
class Item;


/**
* InGameUIクラス
*/


class InGameUI :public UI
{
public:
	InGameUI();
	~InGameUI();
	bool Start() override;
	void Update()override;
	void Direction();
	void Selection();
	void Render(RenderContext& rc)override;


protected:
	void PlayerResidueUI();
	void TimeUI();
	void ItemUI();
	void MapUI();


public:
	float m_timeLimit;//制限時間	
	bool m_blackout=false;//暗転フラグ

private:
	Player* m_player;
	Item* m_item;//アイテム
	FontRender m_timeUI;//時間表示
	FontRender m_residueUI;//プレイヤー残基UI
	SpriteRender m_overSelectionFrame;//GameOverに行く選択UI
	SpriteRender m_lordSelectionFrame;//GameLordに行く選択UI
	SpriteRender m_playerfestureUI;//プレイヤー顔アイコン
	SpriteRender m_itemColumnUI;//アイテム欄
	SpriteRender m_itemSprite;//表示アイテム
	SpriteRender m_map;//マップ表示
	float m_black=1.0f;//画面の黒さ
	float m_transparency=0.5f;//透明度
	float m_overFrameTransparency=0.5;//GameOverFrameColor
	float m_lordFrameTransparency=0.5;//GameLordFrameColor
	float m_cyan;
};

