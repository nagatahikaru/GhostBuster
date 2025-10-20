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
	ModelRender m_modelRender;//モデルレンダー。
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
	float m_time= 0.0f;
	float m_acceleration = 1.5f;
	float m_initialVelocity = 1.0f;
	float m_reset = 0.0f;
	int m_jumpCount = 0;
	int m_maxJumpCount = 3;
	bool m_jumpFlag = false;
	int m_playerState = 0;
};

