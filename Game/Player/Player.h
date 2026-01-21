#pragma once
#include "UI/InGameUI/InGameUI.h"



class GameCamera;
class SnowEnemy;
class GhostEnemy;
class GolemEnemy;
class MushroomEnemy;
class Enemy;
class InGameUI;
class SnowBallManager;


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
	void Atk();
	void Render(RenderContext& rc);

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
	int m_residue=3;
	int m_itemStatus = 0;//アイテム所持状況
	CollisionObject* m_playerCollisionObj;
	InGameUI* m_inGameUI;
	Vector3 m_facingDir = Vector3(0.0f, 0.0f, 1.0f); // 初期向き
	GolemEnemy* m_golemEnemy;	
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

	FontRender m_posRender;//座標表示用
	Vector3 m_playerCollisionScale;	//プレイヤーの当たり判定スケール
	AnimationClip m_animationClips[enAnimationClip_Num];//アニメーションクリップ
	float m_time = 0.0f;//時間
	float m_acceleration = 1.5f;//加速度
	float m_initialVelocity = 10.0f;//初速度
	float m_reset = 0.0f;	//リセット用
	int m_jumpCount = 0;//ジャンプ回数
	int m_enemyjumpCount = 0;
	bool m_jumpFlag = false;//ジャンプフラグ
	int m_playerAnimationState = 0;//Playerのアニメーション状態	
	int m_form0 = 1;//形態状態
	int m_form1 = 2;//形態状態
	int m_form2 = 3;//形態状態
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

