/**
* TiterUI.h
* タイトルに表示するUIクラス
*/
#pragma once
#include "src/UI/UI.h"

/**
* TiterUIクラス
*/


class TiterUI :public UI
{
public:
	TiterUI();
	~TiterUI();
	bool Start() override;
	void Update()override;
	void Direction();
	void Render(RenderContext& rc)override;


	bool m_blinkingfrag=false;
private:
	float m_transparency;
	float m_blinking;
	bool m_fadeIn = true;

};

