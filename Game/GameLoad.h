#pragma once

class Player;
class GameLoad :public IGameObject
{
	public:
	GameLoad();
	~GameLoad();
	bool Start() override;
	void Update() override;

	Player* m_player = nullptr;
};

