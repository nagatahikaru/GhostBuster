#pragma once
class ItemBox:public IGameObject
{
public:
	ItemBox() {};
	~ItemBox();
	bool Start();
	void Update();
	void RandomItem();//アイテムをランダムで決定する関数
	void Render(RenderContext& rc);

	ModelRender m_itemBox;//アイテムボックス
	CollisionObject m_itemBoxObject;//アイテムボックスの当たり判定
};

