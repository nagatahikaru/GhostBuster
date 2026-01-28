#pragma once
#include "Character/Player/Player.h"
#include "Manager/DropItemManager/DropItemsManager.h"



//敵の基底クラス

class Enemy:public IGameObject
{
	public:
	Enemy() 
	{
		m_player = Player::GetInstance();
		m_dropItemsManager = FindGO<DropItemsManager>("dropItemsManager");
		//collider.Create(Vector3(25.0f,75.0f,1.0f));
	}
	virtual ~Enemy();

	//回転処理
	//m_chracter:モデルレンダー
	virtual void Rotation(ModelRender& m_chracter);
	
	//攻撃可能か判定
	//戻り値:true:攻撃可能、false:攻撃不可
	//プレイヤーとの距離が一定以上の場合は攻撃しない
	//クールタイム中は攻撃しない
	//Enemyクラスを継承したクラスでオーバーライドして使用
	virtual bool CanAtk();

	//生成時設定リセット
	//pos:設定する位置(自身の位置)
	//m_characterController:キャラクターコントローラー
	virtual void OnSpawn(const Vector3& pos, CharacterController& m_characterController);
		
	//徘徊処理
	//m_character:モデルレンダー
	//ランダムな方向を生成してその方向に移動する
	//一定時間経過後、再度ランダムな方向を生成する
	virtual void Wandering(ModelRender& m_character);

	//ダメージ処理
	//amount:ダメージ量
	//characterController:キャラクターコントローラー
	//ItemTipy:ドロップアイテムの種類
	//		  :無し=0,雪玉=1,星=2,キノコ=3,本=4
	//Enemyクラスを継承したクラスでオーバーライドして使用
	virtual void Damage(const int&damage, CharacterController&characterController, int& ItemTipy);
	
	//virtual void Tach(CharacterController& characterController);
	//当たり判定処理
	//collisionObject:当たり判定オブジェクト
	//characterController:キャラクターコントローラー
	//HitFlag:当たり判定フラグ
	//ItemTipy:ドロップアイテムの種類
	//		  :無し=0,雪玉=1,星=2,キノコ=3,本=4 
	//HitFlagがtrueならプレイヤーにダメージ、falseなら敵にダメージ
	//Enemyクラスを継承したクラスでオーバーライドして使用
	virtual void Tach(CollisionObject& collisionObject, CharacterController& characterController,bool hitFlag,int *ItemTipy);
		


	//Vector3 startPos;//移動開始位置
	//Vector3 endPos;//移動開始位置、終了位置
	//BulletCallback callback;//当たり判定コールバック
	//BoxCollider collider;//当たり判定用ボックスコライダー
	Vector3 m_position;//座標
	Vector3 m_moveSpeed;//移動速度
	Player* m_player;//プレイヤーのインスタンス
	DropItemsManager* m_dropItemsManager;//ドロップアイテムマネージャー
	Quaternion m_rotation;     //クォータニオン。	
	int m_hp = 0;//体力
	int m_maxHp = 10;//最大体力
	int m_posStert = 0;//移動開始位置
	float m_speed = 0.0f;//移動速度
	float m_coolTime;//攻撃クールタイム
	float m_damageCoolTime = 2.0f;//ダメージクールタイム
	bool m_coolTimeFrag = false;//クールタイムフラグ
	Vector3 m_randPos;//ランダム移動方向
	int m_vec = 0;//ランダム方向決定用変数
	bool randVec = false;//ランダム方向フラグ
	bool m_existence = false;//敵の存在フラグ
	float m_wanderTime = 0.0f;//徘徊時間
	float m_buoyancy;//浮力
	float m_jaumTime;//ジャンプ時間
	int m_itemTypeNone = 0; //ドロップ無し
	int m_itemTypeSnowball = 1; //ドロップ雪玉
	int m_itemTypeStar = 2;//ドロップ星
	int m_itemTypeMushroom = 3;//ドロップキノコ
	int m_itemTypeBook = 4;//ドロップ本
	int m_enemyjump = 500;//敵を踏んだ時のジャンプ力
	int m_damage = 1;//敵がプレイヤーに与えるダメージ
};

