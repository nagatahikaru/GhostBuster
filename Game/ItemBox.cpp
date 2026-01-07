#include "stdafx.h"
#include "ItemBox.h"
#include <random>
#include "Player.h"

ItemBox::~ItemBox()
{
}

bool ItemBox::Start()
{
	m_itemBox.Init("Assets/modelData/itemBox.tkm");
	m_itemBox.SetScale(Vector3(0.3f, 0.3f, 0.3f));
	m_itemBoxObject.CreateBox(
		Vector3(0.0f, 0.0f, 0.0f),
		Quaternion::Identity,
		Vector3(1.0f, 1.0f, 1.0f)
	);
	return true;
}

void ItemBox::Update()
{
	m_itemBox.Update();

}

void ItemBox::RandomItem()
{

	//0~2‚Ìƒ‰ƒ“ƒ_ƒ€‚È®”‚ğ¶¬
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 2);
	int randomItem = dist(mt);
	//Player::GetInstance()->SetCurrentItem(static_cast<Player::EnItem>(randomItem));
}


void ItemBox::Render(RenderContext& rc)
{
	m_itemBox.Draw(rc);
}


