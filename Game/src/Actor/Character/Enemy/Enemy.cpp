#include "stdafx.h"
#include "Enemy.h"
#include "src/Actor/Character/Player/Player.h"
#include "src/Manager/DropItemManager/DropItemsManager.h"

namespace {
	int MAX_HP = 10;
	float ZERO_FLOAT = 0.0f;
	int GET_SCORE = 300;
	float PI = 3.1415f/180.0f;
	int PLAYER_UP_DAMAGE = 10;
}


Enemy::~Enemy()
{
}


//生成時設定リセット
//pos:設定する位置(自身の位置)
//m_characterController:キャラクターコントローラー
void Enemy::OnSpawn(const Vector3& pos, CharacterController& m_characterController)
{		
	m_characterController.SetCollisionActive(true);
	m_hp = MAX_HP;
	m_transform.m_position = pos;
	m_characterController.SetPosition(pos);
}

//回転処理
//m_chracter:モデルレンダー
void Enemy::Rotation(ModelRender& m_chracter)
{
	if (m_player == nullptr) return;
	Vector3 toPlayer = m_player->GetPosition() - m_transform.m_position;
	toPlayer.Normalize();
	m_transform.m_rotation.SetRotationYFromDirectionXZ(toPlayer);// Y軸回りの回転を設定
	m_chracter.SetRotation(m_transform.m_rotation);
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
		if (m_coolTime <= ZERO_FLOAT)
		{
			m_coolTime = ZERO_FLOAT;
			m_coolTimeFrag = false;
		}
		else
		{
			return false;
		}
	}
	//プレイヤーとの距離が一定以上の場合は攻撃しない
	Vector3 dif = m_transform.m_position - m_player->m_position;
	if (dif.Length() > 750.0f) {
		return false;
	}
	return true;
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
		float angle = (rand() % 360) * PI;
		float radius = rand() % 750;
		m_randPos.x += cosf(angle) * radius;
		m_randPos.z += sinf(angle) * radius;
		m_vec = m_randPos.Length();
		m_randPos.Normalize();
		m_wanderTime = rand() % 8 + 2.0f;
		randVec = true;
	}
	m_transform.m_rotation.SetRotationDegY(m_vec);
	m_character.SetRotation(m_transform.m_rotation);
	m_transform.m_position += m_randPos * m_transform.m_speed * g_gameTime->GetFrameDeltaTime();
	//一定時間経過後、再度ランダムなベクトルを取得
	m_wanderTime -= g_gameTime->GetFrameDeltaTime();
	if (m_wanderTime <= ZERO_FLOAT)
	{
		randVec = false;
	}	
}




