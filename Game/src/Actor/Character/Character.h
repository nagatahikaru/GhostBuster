#pragma once
#include "src/Actor/Actor.h"
#include "src/Actor/Character/Player/Player.h" // Player型の定義を確実にインクルード
#include "src/Manager/DropItemManager/DropItemsManager.h"

class Character : public Actor
{
	public:
		Character() {};
		virtual ~Character() {};
		virtual bool Start()
		{
			m_player = Player::GetInstance();
			m_dropItemsManager = FindGO<DropItemsManager>("dropItemsManager");
			return true;
		}

		virtual void Tach(
			CollisionObject& collisionObject,
			CharacterController& characterController,
			bool HitFlag,
			int ItemTipy);

		virtual void Damage(
			const int& amount,
			CharacterController& characterController,
			int ItemTipy);

	private:
		Player* m_player;
		DropItemsManager* m_dropItemsManager; // ドロップアイテムマネージャー	
		int m_hp = 0; // 体力	
		float m_coolTime; // 攻撃クールタイム
		float m_damageCoolTime = 2.0f; // ダメージクールタイム
		bool m_coolTimeFrag = false; // クールタイムフラグ
		int m_damage = 1; // 与えるダメージ
};

