#include "stdafx.h"
#include "DropItems.h"
#include "DropItemsManager.h"

DropItems::DropItems()
{
}
DropItems::~DropItems()
{
}
bool DropItems::Start()
{
	m_dropItemModel.Init("Assets/modelData/snowball.tkm");
	m_dropItemModel.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_dropItemCollisionObj.CreateSphere(
		Vector3(0.0f, 0.0f, 0.0f),
		Quaternion::Identity,
		0.5f
	);
	return true;
}
void DropItems::Update()
{
	// 座標を取得してモデルと当たり判定オブジェクトに反映させる。
	//Vector3 pos = m_dropItemCollisionObj.GetPosition();
	//m_dropItemModel.SetPosition(pos);
}
void DropItems::Render(RenderContext& rc)
{
//	m_dropItemModel.Draw(rc);
}
void DropItems::SetDropItem(const Vector3& position, int itemType)
{
	// 座標を設定。
	m_dropItemCollisionObj.SetPosition(position);
	// アイテムの種類を設定。
	m_itemType = itemType;
}
