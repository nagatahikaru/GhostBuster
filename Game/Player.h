#pragma once
#include "UI/InGameUI/InGameUI.h"



class GameCamera;
class SnowEnemy;
class GhostEnemy;
class GolemEnemy;
class MushroomEnemy;
class Enemy;
class InGameUI;


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
	void ContactJudgment();
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
	int m_formState;//Playerの形態状態
	int m_residue=3;
	CollisionObject* m_playerCollisionObj;
private:
	InGameUI* m_inGameUI;
	Vector3 m_facingDir = Vector3(0.0f, 0.0f, 1.0f); // 初期向き
	GolemEnemy* m_golemEnemy;	
	enum EnAnimaationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num
	};
	FontRender m_posRender;
	Vector3 m_playerCollisionScale;	
	AnimationClip m_animationClips[enAnimationClip_Num];
	float m_time = 0.0f;//時間
	float m_acceleration = 1.5f;//加速度
	float m_initialVelocity = 10.0f;//初速度
	float m_reset = 0.0f;	//リセット用
	int m_jumpCount = 0;//ジャンプ回数
	int m_enemyjumpCount = 0;
	bool m_jumpFlag = false;//ジャンプフラグ
	int m_playerAnimationState = 0;//Playerのアニメーション状態	
	int m_form0 = 1;
	int m_form1 = 2;
	int m_form2 = 3;
	float m_jumpingPower = 0.0f;
	bool sperd = false;
};

