#include "stdafx.h"
#include "InGameUI.h"
#include "Player.h"
#include "Item.h"


InGameUI::InGameUI()
{	

}

InGameUI::~InGameUI()
{

}

//開始処理
bool InGameUI::Start()
{
	m_spriteRender.Init("Assets/sprite/Blackout.DDS", 1920.0f, 1080.0f);
	m_overSelectionFrame.Init("Assets/sprite/SelectionFrame.DDS", 500.0f, 300.0f);
	m_lordSelectionFrame.Init("Assets/sprite/SelectionFrame.DDS", 500.0f, 300.0f);
	m_player = FindGO<Player>("player");
	m_item = FindGO<Item>("item");
	m_timeLimit = 120.0f;
	return true;
}

//更新処理
void InGameUI::Update()
{	
	PlayerResidueUI();
	ItemUI();
	MapUI();
	TimeUI();
	Direction();
}

//残基表示
void InGameUI::PlayerResidueUI()
{
	wchar_t be[129];
	m_residueUI.SetPosition(-896.0f, 500.0f, 0.0f);
	m_residueUI.SetScale(3.0f);
	int residue = m_player->m_residue;
	swprintf(be, 129, L"%0d", residue);
	m_residueUI.SetText(be);
}

//アイテム欄表示
void InGameUI::ItemUI()
{

	if (m_item)
	{
		//所持しているアイテムによって変わる



	}
}

//マップ表示
void InGameUI:: MapUI()
{

}

//時間表示
void InGameUI::TimeUI()
{
	if (m_blackout)
	{
		return;
	}
	m_timeLimit -= g_gameTime->GetFrameDeltaTime();	
	wchar_t be[129];
	m_timeUI.SetPosition(-400.0f, 500.0f, 0.0f);
	m_timeUI.SetScale(3.0f);
	int minet = m_timeLimit / 60;		//分　今の時間/60で分が出る	
	int sec = m_timeLimit- (minet * 60);//秒　今の時間-（分*60）で秒が出る
	swprintf(be, 129, L"%02d:%02d", minet, sec);
	m_timeUI.SetText(be);
}

//演出表示(死亡時の暗転のような)
void InGameUI::Direction()
{
	//プレイヤーの残基が0以下の時、又はNボタンを押した際に半暗転する
	if (m_player->m_residue <= 0||g_pad[0]->IsTrigger(enButtonLB2)|| m_timeLimit<=0.0f)
	{
		m_blackout = true;
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			m_transparency = 0.5;
		}
		if (m_player->m_residue <= 0 || m_timeLimit <= 0.0f)
		{
			m_transparency = 0.8;
		}
	}	
	Vector4 blackoutColor(m_black, m_black, m_black, m_transparency);
	m_spriteRender.Update();
	m_spriteRender.SetMulColor(blackoutColor);
	//プレイヤーの残基が０より大きい時Bボタンを押したら半暗転を解除する
	if (m_player->m_residue > 0 && g_pad[0]->IsTrigger(enButtonLB1))
	{
		m_blackout = false;
	}	
}

//画面移動先選択UI
void InGameUI::Selection()
{
	Vector3 Frame1(0.0f, 400.0f, 0.0f);
	Vector3 Frame2(0.0f, 300.0f, 0.0f);
	m_overSelectionFrame.SetPosition(Frame1);
	m_lordSelectionFrame.SetPosition(Frame2);
	Vector4 OverFrameColor(m_cyan, m_cyan, m_cyan, m_overFrameTransparency);
	Vector4 LordFrameColor(m_cyan, m_cyan, m_cyan, m_lordFrameTransparency);

	if (GetAsyncKeyState('W'))
	{
		m_overFrameTransparency = 1.0f;
		m_lordFrameTransparency = 0.5f;


	}
	if (GetAsyncKeyState('S'))
	{
		m_overFrameTransparency = 0.5f;
		m_lordFrameTransparency = 1.0f;


	}

	m_overSelectionFrame.SetMulColor(OverFrameColor);
	m_lordSelectionFrame.SetMulColor(LordFrameColor);

	m_overSelectionFrame.Update();
	m_lordSelectionFrame.Update();
}

//描画処理
void InGameUI::Render(RenderContext& rc)
{
	if (m_blackout)
	{
		m_spriteRender.Draw(rc);
	}
	m_timeUI.Draw(rc);
	m_residueUI.Draw(rc);

	//m_itemColumnUI.Draw(rc);
	//m_itemSprite.Draw(rc);
	//m_map.Draw(rc);	
}
