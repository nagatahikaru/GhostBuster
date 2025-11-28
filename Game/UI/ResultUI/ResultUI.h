/**
* ResultUI.h
* 結果画面のUIクラス
*/
#pragma once
#include "UI/UI.h"


/**
* ResultUIクラス
*/


class ResultUI :public UI
{
public:
	ResultUI();
	~ResultUI();
	bool Start() override;
	void Update()override;
	void Direction();
	void Render(RenderContext& rc)override;
};

