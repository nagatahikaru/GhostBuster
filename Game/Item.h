#pragma once

class Player;

class Item:public IGameObject
{
public:
	Item();
	~Item();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Player* m_player;//プレイヤー
	ModelRender m_starRender;//大人化アイテム(☆)
	ModelRender m_magicalHat;//魔女化アイテム(魔女帽子)


};

