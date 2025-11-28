#pragma once


class SnowMan:public IGameObject
{
public:
	SnowMan();
	~SnowMan();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	ModelRender m_snowMan;//雪だるまのオブジェクト
};

