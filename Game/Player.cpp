#include "stdafx.h"
#include <string>
#include "Player.h"
#include "GameCamera.h"
#include "SnowEnemy.h"
#include "GhostEnemy.h"
#include "GolemEnemy.h"
#include "MushroomEnemy.h"
#include "Enemy.h"
#include "UI/InGameUI/InGameUI.h"
#include "SnowBallManager.h"


namespace {
	std::string FILE_PATH_GIRL = ("Assets/animData/girl/");
	std::string FILE_PATH_TKA = (".tka");
	std::string FILE_PATH_ANIMATION[7]= {
		"idle",
		"walk",
		"run",
		"jump",
		"victory",
		"death",
		"pitch"
	};
	inline std::string GetAnimationFilePath(const int animationState,const int m_formState)
	{
		return FILE_PATH_GIRL + FILE_PATH_ANIMATION[animationState] + FILE_PATH_TKA;
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
	//m_formStateに応じて読み込むアニメーションを変える
	//m_formStateが0か1なら基本形態のアニメーションクリップを読み込み
	//m_formStateが2なら大人形態のアニメーションクリップを読み込み
	//m_formStateが3なら魔女形態のアニメーションクリップを読み込み
	for (int j = enAnimationClip_Idle; j < enAnimationClip_Jump; j++)
	{			
		m_animationClips[j].Load(GetAnimationFilePath(j, 1).c_str()); // girl
		m_animationClips[j].SetLoopFlag(true);
	}

	for (int j = enAnimationClip_Jump; j < enAnimationClip_Num; j++)
	{
		m_animationClips[j].Load(GetAnimationFilePath(j, 1).c_str()); // girl
		m_animationClips[j].SetLoopFlag(false);
	}
	


	//モデルの初期化
	m_modelRender[0].Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//子供モデル（エラー回避のための死亡形態）
	m_modelRender[1].Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//子供モデル
	m_modelRender[2].Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//大人化モデル(サイズを1.5倍に変更)
	m_modelRender[3].Init("Assets/modelData/unityChan_hw.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);//魔法少女モデル（サイズを1.5倍に変更)
	m_position = Vector3{ 500.0f,1600.0f,0.0f };
	//モデルの位置設定
	for(int i=0;i<4;i++)
	{
		m_modelRender[i].SetPosition(m_position);
	}	
	//モデルのスケール変更
	for (int i = 2; i < 4; i++)
	{
		m_modelRender[i].SetScale(Vector3(1.5f, 1.5f, 1.5f));
	}
	//当たり判定オブジェクトの作成
	m_playerCollisionScale = Vector3(40.0f, 20.0f, 40.0f);
	m_playerCollisionObj = new CollisionObject;
	m_playerCollisionObj->CreateBox(
		m_position,
		Quaternion::Identity,
		m_playerCollisionScale);	

	m_formState = m_form0;
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_characterController.SetCollisionActive(true);
	m_residue = 3;
	m_jumpingPower = 1000.0f;
	m_snowBallManager = FindGO<SnowBallManager>("SnowBallManager");
	return true;
}

//更新処理
void Player::Update()
{
	if (m_backout)
	{
		return;
	}
	Move();//移動処理
	Rotate();//回転処理
	PlayAnimation();//アニメーション再生
	Atk();//攻撃処理
	//ダメージクールタイムの減算
	m_damageCoolTime -= g_gameTime->GetFrameDeltaTime();
}

void Player::Atk()
{
	if (m_itemStatus == 1&&g_pad[0]->IsTrigger(enButtonX))//アイテム所持状態が雪玉の場合
	{
		SnowAtk();//雪玉攻撃処理
	}
}

//雪玉攻撃処理
void Player::SnowAtk()
{
	// 敵の向き（前方向ベクトル）
	Vector3 dir(0, 0, 1);      // Z+方向を基準の前向きにする
	Quaternion rot = m_rotation;
	rot.Apply(dir);
	dir.Normalize(); // 念のため正規化

	// 敵の位置(少し前にずらすと自然)
	Vector3 pos = m_position + dir * 10.0f + Vector3(0.0f, 10.0f, 0);

	// 発射命令
	m_snowBallManager->Fire(pos, dir, rot);
	m_itemStatus = 0; // アイテム使用後、アイテム所持状態をリセット
}

//移動処理
void Player::Move()
{

	//xzの移動速度を0.0fにする
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	
	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持って来る。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//ｙ方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0;

	//左スティックの入力量と200.0fを乗算
	right *= stickL.x * 200.0f;
	forward *= stickL.y * 200.0f;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	//最初いきなり加速せず
	if (g_pad[0]->IsPress(enButtonB))
	{
		m_moveSpeed.x *= m_time; // Bボタンが押されている間、時間経過で加速していく
		m_moveSpeed.z *= m_time; // Bボタンが押されている間、時間経過で加速していく
		if (m_time <= 5.0f)
		{
			m_time += g_gameTime->GetFrameDeltaTime(); // 経過時間を更新
			sperd = true;
		}
		if(sperd)
		{
			m_time = 5.0f;
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
		m_moveSpeed.y = 0.0f;
		m_playerAnimationState = 0;
		m_jumpCount = 0;
		m_enemyjumpCount = 0;
	}
	else//地面についていなかったら
	{
		//重力を発生させる
		const float gravety = 50.0f;//重力の定数
		m_moveSpeed.y -= gravety;
	}

	
	if(m_position.y<=-1000.0f)
	{
		// リスポーン位置へ戻す
		m_position = Vector3{ 500.0f, 1600.0f, 0.0f };

		// 物理／制御系と同期する
		m_characterController.SetPosition(m_position);

		// 速度やジャンプ状態をリセット
		m_moveSpeed = Vector3::Zero;
		m_jumpCount = 0;
		m_enemyjumpCount = 0;

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

	//形態変化の処理(デバック用処理)
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		int form=m_formState;
		m_formState=m_form1;
		m_form1 = m_form2;
		m_form2 = form;

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

	// ジャンプ入力の処理は Move() に統合したためここでは扱わない

	// 地面についていなかったら強制的にジャンプアニメーションへ
	if (!m_characterController.IsOnGround())
	{
		m_playerAnimationState = enAnimationClip_Jump;
	}

	if (m_playerAnimationState != enAnimationClip_Jump) { // ジャンプ中は無視
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
	if(m_damageCoolTime>=0.0f)
	{
		return; // クールタイム中はダメージを受けない
	}
	else
	{		
		//形態ダウン
		m_formState -= damage;
		//形態が0以下になったら1に固定
		//m_formStateが1のときにさらにダメージを受けたら形態は変化しない
		//ただし、残り形残基は減少する
		//形態が0以下になったら1に固定
		if (m_formState == 0)
		{
			m_formState = 1;
			m_position = Vector3{500.0f,1600.0f,0.0f};
			// 物理／制御系と同期する
			m_characterController.SetPosition(m_position);

			// 速度やジャンプ状態をリセット
			m_moveSpeed = Vector3::Zero;
			m_jumpCount = 0;
			m_enemyjumpCount = 0;

			// 衝突オブジェクト／モデル位置を更新
			if (m_playerCollisionObj)
			{
				m_playerCollisionObj->SetPosition(m_position);
				m_playerCollisionObj->Update();
			}
			m_modelRender[m_formState].SetPosition(m_position);

			// アニメーション状態を初期化（必要に応じて）
			m_playerAnimationState = enAnimationClip_Idle;
			//m_modelRender.SetScale(Vector3(m_formState, m_formState, m_formState));
			m_residue--;
		}
		m_damageCoolTime = 1.0f; // ダメージクールタイムをリセット
	}
}


void Player::Render(RenderContext& rc)
{
	//wchar_t be[129];
	//m_posRender.SetPosition(-896.0f, 200.0f, 0.0f);
	//m_posRender.SetColor(g_vec4White);
	//Vector3 pos = m_position;
	//swprintf(be, 129, L"pos:x=%.0f,y=%.0f,z=%.0f", pos.x,pos.y,pos.z);
	//m_posRender.SetText(be);
	//m_posRender.Draw(rc);

	//プレイヤーが描画される設定になっていたら描画する
	if(m_playerRenderFlag)
	{
		//現在の形態状態のモデルレンダーを描画する
		m_modelRender[m_formState].Draw(rc);
	}
}