#pragma once
#include "UI/InGameUI/InGameUI.h"
#include "Manager/SnowBallManager/SnowBallManager.h"

//Playerの変数をまとめる名前空間
namespace PlayerVariable
{
	//Playerのアイテム所持状況
	//アイテム所持状況
	//0:なし、1:スノーボール、2:スター、3:キノコ、4:本
	//0:None, 1:SnowBall, 2:Star, 3:Mushroom, 4:Book
	//呼び出しかた
	// 例:ItemStatus::SnowBall
	namespace ItemStatus
	{
		enum {
			None = 0,
			SnowBall = 1,
			Star = 2,
			Mushroom = 3,
			Book = 4
		};
	}

	//Playerの形態状態
	//0:死亡形態、1:通常形態、2:大人形態、3:魔女形態、4:形態数
	//0:Death, 1:Normal, 2:Adult, 3:Witch、4:Num
	//呼び出しかた
	// 例:PlayerVariable::FormState::SpeedUp
	namespace FormState {
		enum {
			Death = 0,
			Normal = 1,
			Adult = 2,
			Witch = 3,
			Num = 4
		};
	}

	const uint8_t INITIAL_RESIDUE = 3; //初期残基数
	const float MAX_JUMP_POWER = 1000.0f; //最大ジャンプ力
	const float RESET_TIME = 0.0f; //リセット時間
	const uint8_t RESET_JUMP_COUNT = 0; //リセットジャンプ回数
	const float  NONE_SPEED = 0.0f; //スピードアップなし
	const uint8_t VECTOR_SIZE = 10; //ベクトルサイズ

	namespace Transform
	{
		const Vector3 INITIAL_COORDINATE = Vector3(500.0f, 1500.0f, 0.0f);//初期座標
		const float GRAVITY = 50.0f; //重力
		const uint8_t ACCELERATION_TIME = 5;//加速時間
		const float BASICS_SPEED = 400.0f; //基本速度
		const Vector3 VECTOR_UP = Vector3(0.0f, 1.0f, 0.0f); //上方向ベクトル
		const Vector3 INITIAL_SCALE = Vector3(1.5f, 1.5f, 1.5f); //初期スケール
		const Vector3 COLLISION_SCALE = Vector3(50.0f, 35.0f, 50.0f); //当たり判定スケール
	}
}


class Player
{
private:
	Player();
	~Player();
	static Player* m_instance;
public:
	static Player* GetInstance()
	{		
		return m_instance;
	}

	static void CreateInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Player();
		}
	}


	static void DeleteInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
	bool Start();
	void Update();
	void Move();
	void Rotate();
	void PlayAnimation();
	void SnowAtk();
	void Damage(int damage);
	void ItemUse();
	void Render(RenderContext& rc);
	void SetScore(int score) {
		m_score += score;
	}
	int GetScore() const{
		return m_score;
	}

	int GetResidue() const
	{
		return m_residue;
	}

	int GetItem() const
	{
		return m_itemStatus;
	}

	void SetBackout(bool backout)
	{
		m_backout = backout;
	}
	bool GetBackout() const
	{
		return m_backout;
	}

	const Vector3& GetPosition() const
	{
		return m_position;
	}
	const Vector3& GetPlayerDir()const
	{
		return m_facingDir;
	}
	const CollisionObject*GetPlayerCollisionObject() const
	{
		return m_playerCollisionObj;
	}

	//ここからメンバー変数
	ModelRender m_modelRender[4];//モデルレンダー。
	//Hands On1　座標データを追加する。
	Vector3 m_position;//座標。
	Vector3 m_moveSpeed;
	CharacterController m_characterController;
	Quaternion m_rotation;	
	int m_formState;//Playerの形態状態
	int m_residue=PlayerVariable::INITIAL_RESIDUE;//残り残基
	int m_itemStatus = 0;//アイテム所持状況
	CollisionObject* m_playerCollisionObj;
	InGameUI* m_inGameUI;
	Vector3 m_facingDir = Vector3(0.0f, 0.0f, 1.0f); // 初期向き	
	SnowBallManager* m_snowBallManager;
	enum EnAnimaationClip {
		enAnimationClip_Idle,//待機
		enAnimationClip_Walk,//歩き
		enAnimationClip_Run,//走り
		enAnimationClip_Jump,//ジャンプ
		enAnimationClip_Clear,//クリア
		enAnimationClip_Death,//死亡
		enAnimationClip_Pain,//ダメージ
		enAnimationClip_Num//アニメーションクリップ数
	};
	Vector3 m_playerCollisionScale;	//プレイヤーの当たり判定スケール
	AnimationClip m_animationClips[enAnimationClip_Num];//アニメーションクリップ
	float m_time = 0.0f;//時間
	float m_reset = 0.0f;	//リセット用
	int m_jumpCount = 0;//ジャンプ回数	
	bool m_jumpFlag = false;//ジャンプフラグ
	int m_playerAnimationState = 0;//Playerのアニメーション状態	
	float m_jumpingPower = 0.0f;//ジャンプ力
	bool sperd = false;//スピードアップフラグ
	bool m_playerRenderFlag = true; //プレイヤーの描画フラグ
	bool m_backout = true; //ブラックアウトフラグ
	int m_score = 0; //スコア
	float m_damageCoolTime = 0.0f; //ダメージクールタイム
};


class PlayerTest:public IGameObject
{
public:
	PlayerTest() 
	{ 
		Player::CreateInstance(); 
	}
	~PlayerTest()
	{

		Player::DeleteInstance();
	}
	bool Start() 
	{
		Player::GetInstance()->Start(); 
		return true;
	}
	void Update()
	{
		Player* player = Player::GetInstance();
		if (player==nullptr)return;
		player->Update(); 
	}
	void Render(RenderContext& rc) 
	{
		Player* player = Player::GetInstance();
		if (player == nullptr)return;
		player->Render(rc);
	}
};

