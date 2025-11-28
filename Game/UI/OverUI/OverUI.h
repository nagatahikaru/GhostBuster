/**
* OverUI.h
* ゲームオーバー画面のUIクラス
*/
#pragma once
#include "UI/UI.h"

/**
* OverUIクラス
*/


class OverUI :public UI
{	
public:
	OverUI();
	~OverUI();
	bool Start() override;
	void Update()override;
	void Direction();
	void Render(RenderContext& rc)override;
};

