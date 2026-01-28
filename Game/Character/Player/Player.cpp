#include "stdafx.h"
#include <string>
#include "Player.h"
#include "Manager/SnowBallManager/SnowBallManager.h"




namespace {
	std::string FILE_PATH_GIRL = ("Assets/animData/girl/");
	std::string FILE_PATH_MODELDATA = ("Assets/modelData/");	
	std::string FILE_PATH_DDS = (".tka");
	std::string FILE_PATH_TKM = (".tkm");
	std::string FILE_PATH_ANIMATION[7]= {
		"idle",//待機
		"walk",//歩く
		"run",//走る
		"jump",//ジャンプ
		"victory",//勝利
		"death",//負け
		"pitch"//ダメージ
	};
	std::string FILE_PATH_UNITYCHAN[4] = {
		"unityChan",//子供モデル
		"unityChan",//子供モデル
		"unityChan",//子供モデル
		"unityChan_hw",//魔法少女モデル		
	};

	inline std::string GetAnimationFilePath(const int animationState)
	{
		return FILE_PATH_GIRL + FILE_PATH_ANIMATION[animationState] + FILE_PATH_DDS;
	}

	inline std::string GetModelFilePath(const int m_formState)
	{
		return FILE_PATH_MODELDATA + FILE_PATH_UNITYCHAN[m_formState] + FILE_PATH_TKM;
	}

	/**
	モデルの一括初期化処理
	ModelRenderの初期化、位置、スケール設定、更新処理をまとめて行う関数
	modelRender			 初期化するModelRenderのポインタ
	m_animationClips	 アニメーションクリップの配列
	enAnimationClip_Num	 アニメーションクリップの数
	pos					 モデルの位置
	scl					 モデルのスケール
	filePath			 モデルデータのファイルパス	
	例:
	InitModelRender(
		&m_modelRender[i],
		m_animationClips,
		enAnimationClip_Num,
		PlayerVariable::Transform::INITIAL_COORDINATE,
		(i == PlayerVariable::FormState::Normal) ? Vector3(1.0f, 1.0f, 1.0f) : PlayerVariable::Transform::INITIAL_SCALE,
		GetModelFilePath(i));
	*/
	void InitModelRender(
		ModelRender* modelRender
		, AnimationClip* m_animationClips
		, int enAnimationClip_Num
		, const Vector3& pos
		, const Vector3& scl
		, std::string filePath) {
		modelRender->Init(filePath.c_str(), m_animationClips, enAnimationClip_Num, enModelUpAxisY);
		modelRender->SetPosition(pos);
		modelRender->SetScale(scl);
		modelRender->Update();
	}
};



 Player* Player::m_instance = nullptr;
Player::Player()
{
	
}

Player::~Player()
{
	if(m_playerCollisionObj!=nullptr)
	{
		delete m_playerCollisionObj;
		m_playerCollisionObj = nullptr;
	}
}

bool Player::Start()
{
	//forループでまとめる
	//アニメーションクリップの読み込み
	for (int j = enAnimationClip_Idle; j < enAnimationClip_Jump; j++)
	{			
		m_animationClips[j].Load(GetAnimationFilePath(j).c_str());
		m_animationClips[j].SetLoopFlag(true);
	}

	//ジャンプ、クリア、死亡、ダメージアニメーションの読み込み
	for (int j = enAnimationClip_Jump; j < enAnimationClip_Num; j++)
	{
		m_animationClips[j].Load(GetAnimationFilePath(j).c_str());
		m_animationClips[j].SetLoopFlag(false);
	}
	
	//モデルレンダーの初期化
	for (int i = PlayerVariable::FormState::Death; i < PlayerVariable::FormState::Num; i++)
	{		
		InitModelRender(
			&m_modelRender[i],
			m_animationClips,
			enAnimationClip_Num,
			PlayerVariable::Transform::INITIAL_COORDINATE,
			(i == PlayerVariable::FormState::Normal) ? Vector3(1.0f, 1.0f, 1.0f) : PlayerVariable::Transform::INITIAL_SCALE,
			GetModelFilePath(i));			
	}
	//当たり判定オブジェクトの作成
	m_playerCollisionScale = PlayerVariable::Transform::COLLISION_SCALE;
	m_playerCollisionObj = new CollisionObject;
	m_playerCollisionObj->CreateBox(
		m_position,
		Quaternion::Identity,
		m_playerCollisionScale);

	m_jumpingPower = PlayerVariable::MAX_JUMP_POWER;
	m_formState = PlayerVariable::FormState::Normal;
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_characterController.SetCollisionActive(true);
	m_residue = PlayerVariable::INITIAL_RESIDUE;
	//SnowBallManagerの取得
	m_snowBallManager = FindGO<SnowBallManager>("snowBallManager");

	return true;
}

//更新処理
void Player::Update()
{
	if(!m_snowBallManager)
	{
		m_snowBallManager = FindGO<SnowBallManager>("snowBallManager");
	}
	if (m_backout)
	{
		return;
	}
	Move();//移動処理
	Rotate();//回転処理

	//アイテム使用処理
	//アイテムを持っていて、かつ死亡アニメーション中でなければ
	if (m_itemStatus!=PlayerVariable::ItemStatus::None &&
		m_playerAnimationState != enAnimationClip_Death)
	{
		ItemUse();
	}

	if (m_damageCoolTime >= PlayerVariable::RESET_TIME)
	{
		//ダメージクールタイムの減算
		m_damageCoolTime -= g_gameTime->GetFrameDeltaTime();
	}
	PlayAnimation();//アニメーション再生
}

void Player::ItemUse()
{
	//Xボタンが押されたら
	// Lキー入力処理
	//アイテム所持状態に応じて処理を分岐
	if(g_pad[0]->IsTrigger(enButtonX))
	{
		switch (m_itemStatus)
		{
		case PlayerVariable::ItemStatus::None :				 //アイテム所持状態が無しの場合
			break;

		case PlayerVariable::ItemStatus::SnowBall:			 //アイテム所持状態が雪玉の場合
			SnowAtk();										 //雪玉攻撃処理
			m_itemStatus = PlayerVariable::ItemStatus::None; // アイテム使用後、アイテム所持状態をリセット
			break;

		case PlayerVariable::ItemStatus::Star:				 //残基Upアイテムの場合
			m_residue++;									 //残基を1増やす
			m_itemStatus = PlayerVariable::ItemStatus::None; // アイテム使用後、アイテム所持状態をリセット
			break;

		case PlayerVariable::ItemStatus::Mushroom:			 //大人化アイテムの場合
			m_formState = PlayerVariable::FormState::Adult;  // 大人化形態に変化
			m_itemStatus = PlayerVariable::ItemStatus::None; // アイテム使用後、アイテム所持状態をリセット
			break;

		case PlayerVariable::ItemStatus::Book:				 //魔女化アイテムの場合
			m_formState = PlayerVariable::FormState::Witch;	 // 魔女化形態に変化
			m_itemStatus = PlayerVariable::ItemStatus::None; // アイテム使用後、アイテム所持状態をリセット
			break;

		default:
			break;
		}
	}	
}

//雪玉攻撃処理
void Player::SnowAtk(){
	// 敵の位置(少し前にずらすと自然)
	// 発射位置をプレイヤーの前方に設定
	Vector3 pos = m_position + m_facingDir * PlayerVariable::VECTOR_SIZE + PlayerVariable::Transform::VECTOR_UP;

	// 発射命令
	m_snowBallManager->Fire(pos, m_facingDir, m_rotation);
	m_itemStatus = PlayerVariable::ItemStatus::None; // アイテム使用後、アイテム所持状態をリセット
}

//移動処理
void Player::Move()
{
	if(m_playerAnimationState == enAnimationClip_Death ||
		m_playerAnimationState == enAnimationClip_Clear)
	{
		return;
	}

	//xzの移動速度を0.0fにする
	m_moveSpeed.x = PlayerVariable::NONE_SPEED;
	m_moveSpeed.z = PlayerVariable::NONE_SPEED;
	
	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持って来る。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//ｙ方向には移動させない
	forward.y = PlayerVariable::NONE_SPEED;
	right.y = PlayerVariable::NONE_SPEED;

	//左スティックの入力量と200.0fを乗算
	right *= stickL.x * PlayerVariable::Transform::BASICS_SPEED;
	forward *= stickL.y * PlayerVariable::Transform::BASICS_SPEED;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	//最初いきなり加速せず
	if (g_pad[0]->IsPress(enButtonB))
	{
		m_moveSpeed.x *= m_time; // Bボタンが押されている間、時間経過で加速していく
		m_moveSpeed.z *= m_time; // Bボタンが押されている間、時間経過で加速していく
		if (m_time <= PlayerVariable::Transform::ACCELERATION_TIME)
		{
			m_time += g_gameTime->GetFrameDeltaTime(); // 経過時間を更新
			sperd = true;
		}
		if(sperd)
		{
			m_time = PlayerVariable::Transform::ACCELERATION_TIME;
		}		
	}
	else
	{
		//経過時間を減算していく
		m_time = m_reset;
		sperd = false;
	}
	if (m_time <= m_reset) // 経過時間が0以下になったら
	{
		m_time = m_reset; // 経過時間を0にリセット
	}

	//地面についていたら
	if (m_characterController.IsOnGround())
	{
		//重力をなくす
		m_moveSpeed.y = PlayerVariable::NONE_SPEED;
		m_playerAnimationState = enAnimationClip_Idle;
		m_jumpCount = 0;			
	}
	else//地面についていなかったら
	{
		//重力を発生させる
		
		m_moveSpeed.y -= PlayerVariable::Transform::GRAVITY;
	}

	
	if(m_position.y<=-1000.0f)
	{
		// リスポーン位置へ戻す
		m_position = PlayerVariable::Transform::INITIAL_COORDINATE;

		// 物理／制御系と同期する
		m_characterController.SetPosition(m_position);

		// 速度やジャンプ状態をリセット
		m_moveSpeed = Vector3::Zero;
		m_jumpCount = 0;		

		// 衝突オブジェクト／モデル位置を更新
		if (m_playerCollisionObj)
		{
			m_playerCollisionObj->SetPosition(m_position);
			m_playerCollisionObj->Update();
		}
		m_modelRender[m_formState].SetPosition(m_position);

		// アニメーション状態を初期化（必要に応じて）
		m_playerAnimationState = enAnimationClip_Idle;
	}
	//ジャンプの処理
	//Jボタンを押したときジャンプのカウントが最大でなければジャンプする
	//形態によってジャンプできる回数は変化する
	// 修正: ジャンプ回数のインクリメントとアニメーション切替をここで行い、重複を防ぐ
	if (g_pad[0]->IsTrigger(enButtonA) && m_jumpCount < m_formState)
	{
		//上方向に初速を加える
		m_moveSpeed.y += m_jumpingPower;
		// ジャンプ回数を増やす（重要：一元管理）
		m_jumpCount++;
		// アニメーションはジャンプにする
		m_playerAnimationState = enAnimationClip_Jump;
	}
	//キャラクターコントローラーを使って座標を移動させる
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_playerCollisionObj->SetPosition(m_position);
	m_playerCollisionObj->SetRotation(Quaternion::Identity);
	m_playerCollisionObj->Update();
	m_modelRender[m_formState].SetPosition(m_position);
	m_modelRender[m_formState].Update();
}

//回転処理
void Player::Rotate()
{
	if (m_playerAnimationState == enAnimationClip_Death ||
		m_playerAnimationState == enAnimationClip_Clear)
	{
		return;
	}
	Vector3 forward = m_moveSpeed;
	forward.y = 0.0f;

	const float kEps = 0.001f;
	if (forward.Length() > kEps) {
		// 移動があるときだけ向きを更新する
		forward.Normalize();
		m_facingDir = forward; // last non-zero direction を保持
	}
	// m_facingDir を使って回転を作る（移動が無いときは前の向きを使う）
	m_rotation.SetRotationYFromDirectionXZ(m_facingDir);
	m_modelRender[m_formState].SetRotation(m_rotation);
}


//アニメーションの再生
void Player::PlayAnimation()
{	
	// 地面についていなかったら強制的にジャンプアニメーションへ
	if (!m_characterController.IsOnGround())
	{
		m_playerAnimationState = enAnimationClip_Jump;
	}
	
	if (m_playerAnimationState != enAnimationClip_Jump) { // ジャンプ中は無視
		if (m_playerAnimationState == enAnimationClip_Death ||
			m_playerAnimationState == enAnimationClip_Clear)
		{
			return;
		}
		//ｘかｚの移動速度があったら（スティックの入力があったら）
		if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		{
			//歩きアニメーションを再生する
			m_playerAnimationState = enAnimationClip_Walk;
			//走るアニメーションを再生する
			if (g_pad[0]->IsPress(enButtonB))
			{
				m_playerAnimationState = enAnimationClip_Run;
			}
		}
		//ｘとｚの移動速度が無かったら（スティックの入力が無かったら）
		else
		{
			m_playerAnimationState = enAnimationClip_Idle;
		}		
	}
	//現在の形態状態のモデルレンダーでアニメーションを再生する
	m_modelRender[m_formState].PlayAnimation(m_playerAnimationState);
}

//ダメージ処理
void Player::Damage(int damage)
{
	if(m_damageCoolTime>=PlayerVariable::RESET_TIME)
	{
		return; // クールタイム中はダメージを受けない
	}
	else
	{		
		//形態ダウン
		m_formState -= damage;
		m_playerAnimationState = enAnimationClip_Pain;
		
		//形態が0以下になったら1に固定
		//m_formStateが1のときにさらにダメージを受けたら形態は変化しない
		//ただし、残り形残基は減少する
		//形態が0以下になったら1に固定
		if (m_formState == PlayerVariable::FormState::Death)
		{			
			m_formState = PlayerVariable::FormState::Normal;

			// リスポーン位置へ戻す
			m_position = PlayerVariable::Transform::INITIAL_COORDINATE;
			// 物理／制御系と同期する
			m_characterController.SetPosition(m_position);

			// 速度やジャンプ状態をリセット
			m_moveSpeed = Vector3::Zero;
			m_jumpCount = 0;				

			// 衝突オブジェクト／モデル位置を更新
			if (m_playerCollisionObj)
			{
				m_playerCollisionObj->SetPosition(m_position);
				m_playerCollisionObj->Update();
			}
			m_modelRender[m_formState].SetPosition(m_position);

			// アニメーション状態を初期化（必要に応じて）
			m_playerAnimationState = enAnimationClip_Idle;
			m_residue--;			
			
		}
		m_damageCoolTime = 1.0f; // ダメージクールタイムをリセット
	}
}

void Player::Render(RenderContext& rc)
{
	//プレイヤーが描画される設定になっていたら描画する
	if(m_playerRenderFlag)
	{
		//現在の形態状態のモデルレンダーを描画する
		m_modelRender[m_formState].Draw(rc);
	}
}