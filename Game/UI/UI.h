/**
* UI.h
* 画面に表示されるUIの基底クラス
*/
#pragma once


/**
* UIクラス
*/


class UI:public IGameObject
{
protected:
	SpriteRender m_spriteRender;
	FontRender m_fontRender;

public:
	virtual bool Start() override { return true; };
	virtual void Update()override {};
	virtual void Direction()=0;
	virtual void Render(RenderContext& rc)override {};
};

