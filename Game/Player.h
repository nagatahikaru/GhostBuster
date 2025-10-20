#pragma once


class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move();
	void Rotate();
	void Render(RenderContext& renderContxt);
	//ここからメンバー変数
	ModelRender m_modelRender;//モデルレンダー。
	//Hands On1　座標データを追加する。
	Vector3 m_position;//座標。
	Vector3 m_moveSpeed;
	CharacterController m_characterController;
	Quaternion m_rotation;
	enum EnAnimaationClip {
		enAnimationClip_Idle,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
	bool m_renderFlag;
	float m_time= 0.0f;
	float m_acceleration = 1.5f;
	float m_initialVelocity = 1.0f;
	float m_reset = 0.0f;
};

