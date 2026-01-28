#include "stdafx.h"
#include "Enemy.h"
#include "Character/Player/Player.h"
#include "Manager/DropItemManager/DropItemsManager.h"


Enemy::~Enemy()
{
}


//生成時設定リセット
//pos:設定する位置(自身の位置)
//m_characterController:キャラクターコントローラー
void Enemy::OnSpawn(const Vector3& pos, CharacterController& m_characterController)
{		
	m_characterController.SetCollisionActive(true);
	m_hp = m_maxHp;
	m_position = pos;
	m_characterController.SetPosition(pos);
}

//回転処理
//m_chracter:モデルレンダー
void Enemy::Rotation(ModelRender& m_chracter)
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_position;
	toPlayer.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y軸回りの回転を設定
	m_chracter.SetRotation(m_rotation);
}

//攻撃可能か判定
//戻り値:true:攻撃可能、false:攻撃不可
//プレイヤーとの距離が一定以上の場合は攻撃しない
//クールタイム中は攻撃しない
//Enemyクラスを継承したクラスでオーバーライドして使用
bool Enemy::CanAtk() {
	if (m_coolTimeFrag)
	{
		//クールタイム中
		m_coolTime -= g_gameTime->GetFrameDeltaTime();
		if (m_coolTime <= 0.0f)
		{
			m_coolTime = 0.0f;
			m_coolTimeFrag = false;
		}
		else
		{
			return false;
		}
	}
	//プレイヤーとの距離が一定以上の場合は攻撃しない
	Vector3 dif = m_position - m_player->m_position;
	if (dif.Length() > 750.0f) {
		return false;
	}
	return true;
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
void Enemy::Tach(CollisionObject& collisionObject, 
	CharacterController& characterController,
	bool HitFlag,
	int* ItemTipy)
{
    if (m_player == nullptr) return;

    if (!HitFlag) {
		// プレイヤーの当たり判定が渡されたオブジェクトに当たったか？
		if (m_player->m_playerCollisionObj->IsHit(&collisionObject)) {
			Damage(m_damage, characterController, *ItemTipy);
		}
    }
	else
	{
		// 引数 collisionObject がプレイヤーの当たり判定に当たったか？
		//if (collisionObject.IsHit(m_player->m_playerCollisionObj)) {
		//	m_player->Damage(m_damage);
		//	HitFlag = false;
		//}
    }
}

//徘徊処理
//m_character:モデルレンダー
//ランダムな方向を生成してその方向に移動する
//一定時間経過後、再度ランダムな方向を生成する
void Enemy::Wandering(ModelRender& m_character)
{
	//徘徊処理
	//ランダムなベクトルを取得
	if (!randVec)
	{
		//そのベクトルに向かって移動
		// 基準点から半径250の円範囲内でランダムに出現位置を決定
		//ランダムな角度と距離を生成
		float angle = (rand() % 360) * 3.1415f / 180.0f;
		float radius = rand() % 750;
		m_randPos.x += cosf(angle) * radius;
		m_randPos.z += sinf(angle) * radius;
		m_vec = m_randPos.Length();
		m_randPos.Normalize();
		m_wanderTime = rand() % 8 + 2.0f;
		randVec = true;
	}
	m_rotation.SetRotationDegY(m_vec);
	m_character.SetRotation(m_rotation);
	m_position += m_randPos * m_speed * g_gameTime->GetFrameDeltaTime();
	//一定時間経過後、再度ランダムなベクトルを取得	
	m_wanderTime -= g_gameTime->GetFrameDeltaTime();
	if (m_wanderTime <= 0)
	{
		randVec = false;
	}	
}

//ダメージ処理
//amount:ダメージ量
//characterController:キャラクターコントローラー
//ItemTipy:ドロップアイテムの種類
//		  :無し=0,雪玉=1,星=2,キノコ=3,本=4
//Enemyクラスを継承したクラスでオーバーライドして使用
void Enemy::Damage(const int&amount,
	CharacterController& characterController, 
	int& ItemTipy)
{
	m_damageCoolTime -= g_gameTime->GetFrameDeltaTime();	

	if (m_damageCoolTime <= 0.0f)
	{
		m_damageCoolTime = 0.0f;
	}
	else
	{
		//クールタイム中はダメージを受けない
		return;
	}
	//敵を踏んだ時のジャンプ力をジャンプパワーに代入して
	//m_player->m_jumpingPower = m_enemyjump;
	//上記のジャンプ力でジャンプ（想定外の力で飛ぶことを抑制）
	//m_player->m_position.y += m_player->m_jumpingPower;
	//ジャンプし終わったらジャンプ力を戻す
	//m_player->m_jumpingPower = 1000.0f;


	m_hp -= amount;
	if (m_hp <= 0)
	{
		Vector3 dropPos = 
			Vector3(
				m_position.x,
				m_position.y+50.0f,
				m_position.z);
		m_dropItemsManager->DropItemSet(dropPos,ItemTipy);
		characterController.SetCollisionActive(false);
		m_player->SetScore(300);
		Deactivate();
	}
}




