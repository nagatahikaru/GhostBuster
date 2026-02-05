#pragma once
#include "src/Actor/Character/Player/Player.h"
#include "src/Manager/DropItemManager/DropItemsManager.h"
#include "src/Actor/Character/Character.h"



//敵の基底クラス

class Enemy:public Character
{
	public:
	Enemy() 
	{
		m_player = Player::GetInstance();
		m_dropItemsManager = FindGO<DropItemsManager>("dropItemsManager");
	}
	virtual ~Enemy();

	/**
	 * 回転処理
	 * m_chracter:モデルレンダー
	 */	
	virtual void Rotation(ModelRender& m_chracter);
	
	/** 
	 * 攻撃可能か判定
	 * 戻り値:true:攻撃可能、false:攻撃不可
	 * プレイヤーとの距離が一定以上の場合は攻撃しない
	 * クールタイム中は攻撃しない
	 * Enemyクラスを継承したクラスでオーバーライドして使用
	 */	
	virtual bool CanAtk();

	/**
	 * 生成時設定リセット
	 * pos:設定する位置(自身の位置)
	 * m_characterController:キャラクターコントローラー
	 */	
	virtual void OnSpawn(const Vector3& pos, CharacterController& m_characterController);
	
	/**
	 * 徘徊処理
	 * m_character:モデルレンダー
	 * ランダムな方向を生成してその方向に移動する
	 * 一定時間経過後、再度ランダムな方向を生成する
	 */
	virtual void Wandering(ModelRender& m_character);
	
	/**
	 * 敵の存在フラグを設定。
	 */
	virtual void SetEnemyExistence(const bool existence)
	{
		m_existence = existence;
	}

	/*
	 * 敵の存在フラグを取得。
	 */
	virtual bool GetEnemyExistence() const
	{
		return m_existence;
	}

	/**
	 * 敵の体力を取得。
	 */
	virtual void SetEnemyHp(const int hp)
	{
		m_hp = hp;
	}

	/**
	 * 敵の体力を取得。
	 */
	virtual int GetEnemyHp() const
	{
		return m_hp;
	}

	/**
	 * 時間を設定。
	 * time:設定する時間
	 */
	virtual void SetTime(const float time)
	{
		m_time = time;
	}

	/**
	 * 時間を取得。
	 */
	virtual float GetTime() const
	{
		return m_time;
	}

	/**
	 * ダメージクールタイムフラグを設定。
	 * m_coolTimeFrag:設定するフラグ
	 */
	virtual void SetDamageCoolTimeFrag(const  bool coolTimeFrag)
	{
		m_coolTimeFrag = coolTimeFrag;
	}

	/**
	 * ダメージクールタイムフラグを取得。
	 */
	virtual bool GetDamageCoolTimeFrag() const
	{
		return m_coolTimeFrag;
	}


public:
	Player* m_player;//プレイヤー


private:	
	DropItemsManager* m_dropItemsManager;//ドロップアイテムマネージャー	
	int m_hp = 0;//体力	
	float m_time = 0.0f;//時間
	int m_posStert = 0;//移動開始位置	
	float m_coolTime;//攻撃クールタイム
	float m_damageCoolTime = 2.0f;//ダメージクールタイム
	bool m_coolTimeFrag = false;//クールタイムフラグ
	Vector3 m_randPos;//ランダム移動方向
	int m_vec = 0;//ランダム方向決定用変数
	bool randVec = false;//ランダム方向フラグ
	bool m_existence = false;//敵の存在フラグ
	float m_wanderTime = 0.0f;//徘徊時間
	int m_enemyjump = 500;//敵を踏んだ時のジャンプ力
	int m_damage = 1;//与えるダメージ
};

