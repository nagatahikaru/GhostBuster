#pragma once
#include "src/Actor/Character/Player/Player.h"

class DropItemsManager;

namespace Variable {
	const float DROP_ITEM_BOUNCE_HEIGHT = 0.5f; //ドロップアイテムのバウンスの高さ
	const float DROP_ITEM_BOUNCE_SPEED = 2.0f; //ドロップアイテムのバウンスの速度
	const float DROP_ITEM_ROTATION_SPEED = 1.0f; //ドロップアイテムの回転速度
	const float DROP_ITEM_FALL_SPEED = 5.0f; //ドロップアイテムの落下速度
	const float DROP_SPEED_DECELERATION = 2.0f; //ドロップアイテムの飛んでいく速度減衰率
	const float DROP_ROTATION_PI = 3.14159f / 180.0f; //ドロップアイテムの回転速度のπ/3
}

class DropItems : public IGameObject
{
	public:
	DropItems();
	~DropItems();
	bool Start() override;
	void Update() override;
	void DropItemBehavior(); //ドロップアイテムの挙動関数
	void SetDropItem(const Vector3& position, int itemType);
	void Render(RenderContext& rc);
	void DropItemOff(); //ドロップアイテムを消す関数
	void GetItemType();//アイテムの種類を取得する関数
	void RotationDropItem(); //ドロップアイテムの回転関数
	void SetDirection(Vector3& direction) //ドロップアイテムの飛んでいく向きを設定する関数
	{
		m_distance = direction;
		m_direction = direction.Length();
	}
	void SetIsStartDrop(bool isStartDrop) //ドロップアイテムが出現したかどうかを設定する関数
	{
		m_isStartDrop = isStartDrop;
	}
	
	
private:
	Player* m_player;
	DropItemsManager* m_dropItemsManager;		//ドロップアイテムマネージャーのポインタ
	ModelRender m_dropItemModel[5];				//落ちているアイテムのモデルレンダー
	CollisionObject m_dropItemCollisionObj;		//落ちているアイテムの当たり判定
	CharacterController m_characterController;	//キャラクターコントローラー
	Vector3 m_position;				//アイテムの座標
	Vector3 m_distance;				//プレイヤーとの距離
	Vector3 m_rotationVec;			//アイテムの回転ベクトル
	Quaternion m_rotation;		//アイテムの回転
	int m_itemType = 0;				//アイテムの種類
	float m_destroyTime = 10.0f;	//消滅までの時間
	float m_elapsedTime = 0.0f;		//経過時間
	float m_distanceToPlayer;		//プレイヤーとの取得距離
	float m_direction;				//ドロップアイテムの飛んでいく向き
	bool m_isStartDrop = false;		//ドロップアイテムが出現したかどうか
	float m_dropSpeed = 100.0f;		//ドロップアイテムの飛んでいく速度
	float m_rotationLength = 0.0f;	//ドロップアイテムの回転速度
	int m_circle = 360;					//ドロップアイテムの回転角度
};

