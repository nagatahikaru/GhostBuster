#pragma once
class ItemBox:public IGameObject
{
public:
	ItemBox();
	~ItemBox();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender m_itemBox;//アイテムボックス
};

