#pragma once

class GameCamera;

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move();
	void Rotate();
	void PlayAnimation();
	void SetAnimation();	
	void Render(RenderContext& renderContxt);

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	//ここからメンバー変数
	ModelRender m_modelRender[3];//モデルレンダー。
	//Hands On1　座標データを追加する。
	Vector3 m_position;//座標。
	Vector3 m_moveSpeed;
	CharacterController m_characterController;
	Quaternion m_rotation;
	GameCamera* m_gameCamera;
	enum EnAnimaationClip {
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Walk,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
	float m_time = 0.0f;//時間
	float m_acceleration = 1.5f;//加速度
	float m_initialVelocity = 1.0f;//初速度
	float m_reset = 0.0f;	//リセット用
	int m_jumpCount = 0;//ジャンプ回数
	int m_maxJumpCount = 3;//最大ジャンプ回数
	bool m_jumpFlag = false;//ジャンプフラグ
	int m_playerAnimationState = 0;//Playerのアニメーション状態
	int m_formState = 0;//Playerの形態状態
	
};

