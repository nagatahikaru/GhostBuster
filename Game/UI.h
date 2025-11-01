#pragma once

class Item;

class UI:public IGameObject
{
public:
	UI();
	~UI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	FontRender m_time;//時間表示
	FontRender m_residue;//プレイヤー残基UI
	SpriteRender m_itemColumn;//アイテム欄
	SpriteRender m_itemSprite;//表示アイテム
	SpriteRender m_map;//マップ表示
	Item* m_item;//アイテム
};

