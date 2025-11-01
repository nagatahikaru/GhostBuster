#pragma once

class Player;

class SnowEnemy:public IGameObject
{
public:
	SnowEnemy();
	~SnowEnemy();
	bool Start();
	void Update();
	void Atk();
	void Move();
	void Rotation();
	void Damage(int damage);
	void Render(RenderContext& rc);

private:
	ModelRender m_snow[2];//雪だるまに擬態する敵
	enum EnAnimaationClip {
		enAnimationClip_Idle,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Player* m_player;
	CharacterController m_hitJudgment;//当たり判定
	Quaternion        m_rotation;     //クォータニオン。
	int m_form = 0;

	int m_hp=0;


};

