#pragma once

class Player;

class GhostEnemy:public IGameObject
{
public:
	GhostEnemy();
	~GhostEnemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void SetPosition(const Vector3& pos);
	bool CanAtk();
	void Atk();
	void Move();
	void Rotation();
	void Damage(int damage);
	void PlayAnimation();	
	CharacterController m_characterController;//当たり判定
	bool m_isInited = false;
	bool m_IsSpawn = true;
		private:
	ModelRender m_ghost;//幽霊の敵
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_snowEnemyCollisionScale;
	Player* m_player;
	Quaternion m_rotation;     //クォータニオン。
	int m_form = 0;
	int m_hp = 0;
	int m_posStert = 0;
	float m_speed = 0.0f;
	FontRender m_distance;
	float m_coolTime;
	bool m_coolTimeFrag = false;
};




