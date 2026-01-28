#pragma once
//アクターの基底クラス

class Actor :public IGameObject
{
public:
	Actor();
	virtual ~Actor();


public:
	Transform m_transform;


protected:
	ModelRender m_modelRender;
};

