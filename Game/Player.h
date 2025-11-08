#pragma once
//#include "ObjectPool.h"

class GameCamera;
class SnowEnemy;
class SnowEnemyManager;


class Player:public IGameObject
{
public:
	Player();
	~Player()override;
	bool Start();
	void Update();
	void Move();
	void Rotate();
	void PlayAnimation();	
	void Atk();
	void Damage(int damage);
	void Render(RenderContext& rc);

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	//ここからメンバー変数
	ModelRender m_modelRender[4];//モデルレンダー。
	//Hands On1　座標データを追加する。
	Vector3 m_position;//座標。
	Vector3 m_moveSpeed;
	CharacterController m_characterController;
	Quaternion m_rotation;
	GameCamera* m_gameCamera;
	int m_formState = 1;//Playerの形態状態
	int m_residue=3;
	CollisionObject* m_playerCollisionObj;
private:
	//ObjectPool<SnowEnemy> m_snowEnemyPool;
	SnowEnemyManager* m_snwoEnemyManager;
	enum EnAnimaationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

	Vector3 m_playerCollisionScale;	
	AnimationClip m_animationClips[enAnimationClip_Num];
	float m_time = 0.0f;//時間
	float m_acceleration = 1.5f;//加速度
	float m_initialVelocity = 10.0f;//初速度
	float m_reset = 0.0f;	//リセット用
	int m_jumpCount = 0;//ジャンプ回数
	//int m_maxJumpCount = 3;//最大ジャンプ回数
	bool m_jumpFlag = false;//ジャンプフラグ
	int m_playerAnimationState = 0;//Playerのアニメーション状態	
	int m_form1 = 2;//チェック用
	int m_form2 = 3;//チェック用
	bool sperd = false;
};

