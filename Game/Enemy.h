#pragma once

class Player;

//敵の基底クラス

class Enemy:public IGameObject
{
	public:
		Enemy();
		virtual ~Enemy();
		virtual void Damage(int amount,CharacterController& m_characterControlle);
		virtual void Rotation(ModelRender& m_chracter);
		virtual bool CanAtk();
		virtual void OnSpawn(const Vector3& pos, CharacterController& m_characterController);
		virtual void Wandering(ModelRender& m_character);

//private:
		Vector3 m_position;
		Vector3 m_moveSpeed;
		Player* m_player;
		Quaternion m_rotation;     //クォータニオン。		
		int m_hp = 0;
		int m_maxHp = 10;
		int m_posStert = 0;
		float m_speed = 0.0f;
		float m_coolTime;
		float m_damageCoolTime = 2.0f;
		bool m_coolTimeFrag = false;
		Vector3 m_randPos;//ランダム移動方向
		int m_vec = 0;
		bool randVec = false;
		bool m_existence = false;
		float m_wanderTime = 0.0f;
};

