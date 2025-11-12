#pragma once

class Item;
class Player;

class UI:public IGameObject
{
public:
	UI();
	~UI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	FontRender m_timeUI;//時間表示
	FontRender m_residueUI;//プレイヤー残基UI
	SpriteRender m_playerfestureUI;//プレイヤー顔アイコン
	SpriteRender m_itemColumnUI;//アイテム欄
	SpriteRender m_itemSprite;//表示アイテム
	SpriteRender m_map;//マップ表示
	Item* m_item;//アイテム
};

