#include "stdafx.h"
#include "DropItems.h"
#include "Manager/DropItemManager/DropItemsManager.h"
#include "Character/Player/Player.h"

namespace {
	std::string FILE_PATH = ("Assets/modelData/");		
	std::string FILE_PATH_TKM = (".tkm");

	// アイテムモデルのファイルパス配列
	// 0:なし,1:スノーボール,2:スター,3:キノコ,4:本
	//Noneは存在しないので使用しない
	// インデックスとアイテムの種類を対応させる
	//	戻り値:アイテムモデルのファイルパス
	std::string ITEMMODEL_FILE_PATH[5] = {
		"None","SnowBall","Star","Mushroom","Book"
	};

	inline std::string GetItemModelFilePath(const int itemType)
	{
		return FILE_PATH + ITEMMODEL_FILE_PATH[itemType] + FILE_PATH_TKM;
	}



	/**
	モデルの一括初期化処理
	ModelRenderの初期化、位置、スケール設定、更新処理をまとめて行う関数
	modelRender			 初期化するModelRenderのポインタ
	pos					 モデルの位置
	scl					 モデルのスケール
	filePath			 モデルデータのファイルパス
	例:
	InitModelRender(
	&m_modelRender[i],
	Vector3::Zero,
	Vector3(0.5f, 0.5f, 0.5f),
	GetModelFilePath(i));
*/
	void InitModelRender(
		ModelRender* modelRender
		, const Vector3& pos
		, const Vector3& scl
		, std::string filePath) {
		modelRender->Init(filePath.c_str());
		modelRender->SetPosition(pos);
		modelRender->SetScale(scl);
		modelRender->Update();
	}

}


DropItems::DropItems()
{
}
DropItems::~DropItems()
{
	delete &m_dropItemCollisionObj;
}
bool DropItems::Start()
{
	for (int i = 1; i < 5; i++)
	{
		InitModelRender(
			&m_dropItemModel[i],
			Vector3::Zero,
			Vector3(0.5f, 0.5f, 0.5f),
			GetItemModelFilePath(i)
		);		
	}	
	m_characterController.Init(50.0f,50.0f,m_position);
	m_characterController.SetPosition(m_position);
	m_characterController.GetCollider();
	m_characterController.SetCollisionActive(true);

	m_dropItemCollisionObj.CreateSphere(
		Vector3::Zero,
		Quaternion::Identity,
		0.5f
	);
	m_player = Player::GetInstance();
	m_distance =m_player->GetPosition() - m_position;
	m_distance.y = 0.0f; //y軸の距離を無視
	m_distanceToPlayer = m_distance.Length();
	return true;
}
void DropItems::Update()
{
	if(m_destroyTime <= 0.0f)
	{
		DropItemOff();
	}

	if(m_distanceToPlayer<=150.0f)
	{
		GetItemType();
	}
	DropItemBehavior();
}

void DropItems::SetDropItem(const Vector3& position, int itemType)
{
	// 座標を設定。
	m_dropItemCollisionObj.SetPosition(position);
	m_position = position;
	// アイテムの種類を設定。
	m_itemType = itemType;
	m_dropItemCollisionObj.Update();
	// ドロップアイテムを出す。
	this->Activate();
}

void DropItems::DropItemBehavior()
{
	//ドロップ処理
	if(m_isStartDrop)
	{
		m_position.y += m_dropSpeed * g_gameTime->GetFrameDeltaTime(); //上昇
		m_isStartDrop = false;
	}
	m_distance.Normalize();
	m_position += m_distance * m_dropSpeed * g_gameTime->GetFrameDeltaTime(); //前進

	//回転処理

	m_destroyTime -= g_gameTime->GetFrameDeltaTime();
	//経過時間を加算
	//m_elapsedTimeにフレームの経過時間を加算
	m_elapsedTime += g_gameTime->GetFrameDeltaTime();
	if (!m_characterController.IsOnGround())
	{
		//落下処理
		m_position.y -= Variable::DROP_ITEM_FALL_SPEED * g_gameTime->GetFrameDeltaTime();
		m_characterController.SetPosition(m_position);
	}
	else
	{
		//バウンス処理		
		m_position.y += (sinf(m_elapsedTime * Variable::DROP_ITEM_BOUNCE_SPEED) * Variable::DROP_ITEM_BOUNCE_HEIGHT); //バウンス
		m_dropSpeed /= AVATAR_F2; //減速
		m_characterController.SetPosition(m_position);
		m_dropItemCollisionObj.SetPosition(m_position);
		m_dropItemCollisionObj.Update();
	}
	RotationDropItem();
}

void DropItems::DropItemOff()
{
	// ドロップアイテムを消すまでの時間を設定。
	if(m_destroyTime<=0.0f)
	{
		// ドロップアイテムを消す。
		this->Deactivate();
	}
}

void DropItems::GetItemType()
{
	// プレイヤーが近づいて、Mボタンを押したらアイテムを取得。
	if(m_distanceToPlayer <=150.0f&&g_pad[0]->IsTrigger(enButtonLB3))
	{
		// プレイヤーの所持アイテムにアイテムの種類を追加。
		m_player->m_itemStatus=m_itemType;
		int score = 500;
		m_player->SetScore(score); //スコア加算
		// ドロップアイテムを消す。
		this->Deactivate();
	}

}

void DropItems::RotationDropItem()
{
	// ドロップアイテムの回転を更新
	//その場で回り続ける
	//Y軸回転
	m_circle -= g_gameTime->GetFrameDeltaTime() * Variable::DROP_ITEM_ROTATION_SPEED;
	float angle = m_circle *Variable::DROP_ROTATION_PI;
	m_rotationVec.x += cosf(angle);
	m_rotationVec.z += sinf(angle);
	m_rotationLength = m_rotationVec.Length();
	m_rotation.SetRotationYFromDirectionXZ(m_rotationVec);
	// ドロップアイテムの回転処理
	m_dropItemModel[m_itemType].SetRotation(m_rotation);
	
}

void DropItems::Render(RenderContext& rc)
{
	if (this->IsActive()&&m_itemType!=0)
	{
		m_dropItemModel[m_itemType].SetPosition(m_position);
		m_dropItemModel[m_itemType].Update();
		m_dropItemModel[m_itemType].Draw(rc);
	}
}

