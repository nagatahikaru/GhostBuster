#pragma once
class MushroomEnemy:public IGameObject
{
public:
	MushroomEnemy();
	~MushroomEnemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender m_mushroom;//ƒLƒmƒR‚Ì“G
};

