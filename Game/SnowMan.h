#pragma once
class SnowMan:public IGameObject
{
public:
	SnowMan();
	~SnowMan();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender m_snowMan;//雪だるまのオブジェクト
};

