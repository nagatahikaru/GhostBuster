/**
* ClearUI.h
* クリア画面のUIクラス
*/
#pragma once
#include "UI/UI.h"

/**
* ClearUIクラス
*/


class ClearUI :public UI
{
public:
	ClearUI();
	~ClearUI();
	bool Start() override;
	void Update()override;
	void Direction();
	void Render(RenderContext& rc)override;
};

