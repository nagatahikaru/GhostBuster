#pragma once
class GhostEnemy:public IGameObject
{
public:
	GhostEnemy();
	~GhostEnemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender m_ghost;//—H—ì‚Ì“G
};

