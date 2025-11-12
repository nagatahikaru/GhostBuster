#include "stdafx.h"
#include "UI.h"
#include "Item.h"
#include "Player.h"

UI::UI()
{	

}

UI::~UI()
{

}

//開始処理
bool UI::Start()
{
	return true;
}

//更新処理
void UI::Update()
{
	//時間表示
	
	//残基表示
	
	
	//アイテム欄表示
	
	if (m_item)
	{
		//所持しているアイテムによって変わる



	}
	
	//マップ表示
	
}

//描画処理
void UI::Render(RenderContext& rc)
{
	m_timeUI.Draw(rc);
	m_residueUI.Draw(rc);
	m_itemColumnUI.Draw(rc);
	m_itemSprite.Draw(rc);
	m_map.Draw(rc);
}
