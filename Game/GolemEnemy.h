#pragma once
class GolemEnemy:public IGameObject
{
public:
	GolemEnemy();
	~GolemEnemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender m_golem;//ƒS[ƒŒƒ€

};

