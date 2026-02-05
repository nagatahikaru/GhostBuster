#include "stdafx.h"
#include "Character.h"
#include "Player/Player.h"

namespace {
	int MAX_HP = 10;
	float ZERO_FLOAT = 0.0f;
	int GET_SCORE = 300;
	float PI = 3.1415f / 180.0f;
	int PLAYER_UP_DAMAGE = 10;
}

//当たり判定処理
//collisionObject:当たり判定オブジェクト
//characterController:キャラクターコントローラー
//HitFlag:当たり判定フラグ
//		 :trueならプレイヤーにダメージ、falseなら敵にダメージ
//ItemTipy:ドロップアイテムの種類
//		  :無し=0,雪玉=1,星=2,キノコ=3,本=4 
//HitFlagがtrueならプレイヤーにダメージ、falseなら敵にダメージ
//Enemyクラスを継承したクラスでオーバーライドして使用
void Character::Tach(CollisionObject& collisionObject,
	CharacterController& characterController,
	bool HitFlag,
	int ItemTipy)
{
	if (m_player == nullptr) return;

	if (!HitFlag) {
		// プレイヤーの当たり判定が渡されたオブジェクトに当たったか？
		if (m_player->m_playerCollisionObj->IsHit(&collisionObject)) {
			Damage(m_damage * PLAYER_UP_DAMAGE, characterController, ItemTipy);
		}
	}
	else
	{
		// 引数 collisionObject がプレイヤーの当たり判定に当たったか？
		if (collisionObject.IsHit(m_player->m_characterController)) {
			m_player->Damage(m_damage);
			HitFlag = false;
		}
	}
}

//ダメージ処理
//amount:ダメージ量
//characterController:キャラクターコントローラー
//ItemTipy:ドロップアイテムの種類
//		  :無し=0,雪玉=1,星=2,キノコ=3,本=4
//Enemyクラスを継承したクラスでオーバーライドして使用
void Character::Damage(const int& amount,
	CharacterController& characterController,
	int ItemTipy)
{
	m_damageCoolTime -= g_gameTime->GetFrameDeltaTime();

	if (m_damageCoolTime <= ZERO_FLOAT)
	{
		m_damageCoolTime = ZERO_FLOAT;
	}
	else
	{
		//クールタイム中はダメージを受けない
		return;
	}
	m_hp -= amount;
	if (m_hp <= ZERO_FLOAT)
	{
		Vector3 dropPos =
			Vector3(
				m_transform.m_position.x,
				m_transform.m_position.y + 50.0f,
				m_transform.m_position.z);
		m_dropItemsManager->DropItemSet(dropPos, ItemTipy);
		characterController.SetCollisionActive(false);
		m_player->SetScore(GET_SCORE);
		Deactivate();
	}
}