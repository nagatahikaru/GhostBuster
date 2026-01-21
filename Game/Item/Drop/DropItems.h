#pragma once

class DropItemsManager;

class DropItems : public IGameObject
{
	public:
	DropItems();
	~DropItems();
	bool Start() override;
	void Update() override;
	void SetDropItem(const Vector3& position, int itemType);
	void Render(RenderContext& rc) override;

	DropItemsManager* m_dropItemsManager; //ドロップアイテムマネージャーのポインタ
	ModelRender m_dropItemModel;			//落ちているアイテムのモデルレンダー
	CollisionObject m_dropItemCollisionObj;	//落ちているアイテムの当たり判定
	int m_itemType = 0;						//アイテムの種類
};

