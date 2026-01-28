#include "stdafx.h"
#include "InGameUI.h"
#include "Character/Player/Player.h"
#include <algorithm>

//ファイルパス関連
//namespaceを使わないとグローバル変数になる
//このファイル内でしか使わないので無名名前空間にする
//無名名前空間:このファイル内でしか使わない変数や関数を定義する
//外部からアクセスできないようにする
//GetNumberFilePath:数字のファイルパス取得
//GetItemFilePath:アイテムのファイルパス取得
//UpdateSpriteInfo:スプライト情報更新
namespace {
	std::string FILE_PATH = ("Assets/sprite/");
	std::string FILE_PATH_NUMBER = ("Number/");
	std::string FILE_PATH_ITEM = ("Item/");
	std::string FILE_PATH_DDS = (".DDS");
	std::string NUMBER_FILE_PATH[10] = {
		"0","1","2","3","4","5","6","7","8","9"
	};

	std::string ITEMMODEL_FILE_PATH[5] = {
		"None","Snowball","StarPowr","Mushroom","Book"
	};

	inline std::string GetNumberFilePath(const int number)
	{
		return FILE_PATH+ FILE_PATH_NUMBER +NUMBER_FILE_PATH[number]+ FILE_PATH_DDS;
	}

	inline std::string GetItemFilePath(const int itemType)
	{
		return FILE_PATH + FILE_PATH_ITEM + ITEMMODEL_FILE_PATH[itemType] + FILE_PATH_DDS;
	}

	/**
		スプライト情報更新
		spriteRender:スプライトレンダー
		pos:座標
		scl:スケール 
		基礎値:X=1.0f,Y=1.0f
		最大値:X1920.0f,Y1080.0f
		中心を0として
		x:-960.0f~960.0f
		y:-540.0f~540.0f
		filePath:ファイルパス
		戻り値:なし	
		例:
		UpdateSpriteInfo(&spriteRender, 
		Vector3(0.0f,0.0f,0.0f), 
		Vector3(1.0f,1.0f,1.0f), 
		"Assets/sprite/Number/0.DDS"); 
	*/
	void UpdateSpriteInfo(
		SpriteRender* spriteRender
		, const Vector3& pos
		, const Vector3& scl
		, const std::string& filePath) {
		spriteRender->Init(filePath.c_str(), 1.0f, 1.0f);
		spriteRender->SetPosition(pos);
		spriteRender->SetScale(scl);
		spriteRender->Update();
	}
}


//タイマー初期化
void InGameUI::InitializeTimer() {
	m_nowTime = nsUI::nsTimer::LIMIT;
	m_timeUI[0].nowTime = 0;
	m_timeUI[1].nowTime = 0;
	m_timeUI[2].nowTime = 3;


	for (int i = 0; i < enTime_num; i++) {
		int fileNum = m_timeUI[i].nowTime;
		UpdateSpriteInfo(
			&m_timeUI[i].spriteRender
			, nsUI::nsTimer::POS[i]
			, nsUI::nsTimer::SCALE
			, GetNumberFilePath(fileNum));
	}
}


//残基初期化
void InGameUI::InitializeResidue(){
	m_nowResidue = nsUI::nsResidue::MIN;
	m_residueUI[0].nowResidue = 3;
	m_residueUI[1].nowResidue = 0;
	m_residueUI[2].nowResidue = 0;

	for (int i = 0; i < enResidue_num; i++)
	{
		int fileNum = m_residueUI[i].nowResidue;
		UpdateSpriteInfo(
			&m_residueUI[i].spriteRender
			, nsUI::nsResidue::POS[i]
			, nsUI::nsResidue::SCALE
			, GetNumberFilePath(fileNum));
	}
}


//アイテム初期化
void InGameUI::InitializeItem()
{
	m_nowItem = nsUI::nsItem::NONE;
	m_itemUI[0].nowItem = 0;
	for (int i = 0; i < enItem_num; i++)
	{
		int fileNum = m_itemUI[i].nowItem;
		UpdateSpriteInfo(
			&m_itemUI[i].spriteRender
			, nsUI::nsItem::POS[i]
			, nsUI::nsItem::SCALE
			, GetItemFilePath(fileNum));
	}
}


//スコア初期化
void InGameUI::InitializeScore()
{
	m_nowScore = nsUI::nsScore::MIN;
	m_scoreUI[0].nowScore = 0;
	for (int i = 0; i < enMaxScoreDigit; i++)
	{
		int fileNum = m_scoreUI[i].nowScore;
		UpdateSpriteInfo(
			&m_scoreUI[i].spriteRender
			, nsUI::nsScore::POS[i]
			, nsUI::nsScore::SCALE
			, GetNumberFilePath(fileNum));
	}
}


InGameUI::~InGameUI()
{

}


//開始処理
bool InGameUI::Start()
{
	//暗転スプライトの初期化
	UpdateSpriteInfo(&m_spriteRender,		
		Vector3::Zero,
		Vector3(1920.0f, 1080.0f, 1.0f),
		("Assets/sprite/Blackout.DDS"));

	//ゲームオーバー選択枠の初期化
	UpdateSpriteInfo(&m_overSelectionFrame,
		Vector3(0.0f, 250.0f, 0.0f),
		Vector3(500.0f,300.0f,1.0),
		("Assets/sprite/SelectionFrame.DDS"));

	//ロード画面選択枠の初期化
	UpdateSpriteInfo(&m_lordSelectionFrame,
		Vector3(0.0f, -150.0f, 0.0f),
		Vector3(500.0f, 300.0f, 1.0),
		("Assets/sprite/SelectionFrame.DDS"));

	//コロンの初期化
	UpdateSpriteInfo(&m_koronSprite,
		Vector3(760.0f, 490.0f, 0.0f),
		Vector3(100.0f, 100.0f, 1.0f),
		("Assets/sprite/koron.DDS"));

	//プレイヤー顔アイコンの初期化
	UpdateSpriteInfo(&m_playerfestureUI,
		Vector3(-885.0f, 445.0f, 0.0f),
		Vector3(150, 150.0f, 1.0f),
		("Assets/sprite/Icon.DDS"));

	//アイテム欄の初期化
	UpdateSpriteInfo(&m_itemColumnUI,
		Vector3(-900.0f, -400.0f, 0.0f),
		Vector3(150.0f, 150.0f, 1.0f),
		("Assets/sprite/ItemFrame.DDS"));

	InitializeTimer();
	InitializeResidue();
	InitializeItem();
	InitializeScore();
	m_player = Player::GetInstance();
	m_player->SetBackout(false);
	return true;
}


//更新処理
void InGameUI::Update()
{	
	// 時間は毎フレーム更新が必要
    MeasureNowTime();
    
    // プレイヤー関連は変化があったときだけ更新
    if (m_player)
    {
        // 残基が変化したときだけ更新
        if (m_player->GetResidue() != m_nowResidue)
        {
            PlayerResidueUI();
        }
        
        // アイテムが変化したときだけ更新
        if (m_player->GetItem() != m_nowItem)
        {
            ItemUI();
        }
        
        // スコアが変化したときだけ更新
        if (m_player->GetScore() != m_pastScore)
        {
            AddScore();
        }
    }
    
    // 演出中だけ実行
    if (m_blackout || g_pad[0]->IsTrigger(enButtonSelect))
    {
        Direction();
    }
    
    // 選択中だけ実行
    if (m_blackout)
    {
        Selection();
    }
}


//残基表示
void InGameUI::PlayerResidueUI()
{
	//プレイヤーの残基を代入
	m_nowResidue = m_player->GetResidue();
	//0以下にはしない
	m_nowResidue = max(0.0f, m_nowResidue);

	//計算したい桁数より上の桁の合計
	int harderDigitTimeCalc = 0;

	//桁数分繰り返す
	for (int i = enResidue_num - 1; i >= 0; i--) {
		//一旦現在の数字を保存
		int oldResidue = m_residueUI[i].nowResidue;
		//計算する桁数より上の桁の合計を引いてさらにそれぞれの
		//m_nowResidueを桁数で割った値を代入
		m_residueUI[i].nowResidue = (m_nowResidue - harderDigitTimeCalc) / nsUI::nsResidue::COUNT[i];
		//今計算している桁の数値を合計値に加算
		harderDigitTimeCalc += m_residueUI[i].nowResidue * nsUI::nsResidue::COUNT[i];
		//今計算中の桁の数値が変化したかどうか判定
		//変化していなければ次の桁へ
		if (oldResidue == m_residueUI[i].nowResidue) continue;

		//時間が変化しているのでスプライトを更新
		int fileNum = m_residueUI[i].nowResidue;
		UpdateSpriteInfo(
			&m_residueUI[i].spriteRender
			, nsUI::nsResidue::POS[i]
			, nsUI::nsResidue::SCALE
			, GetNumberFilePath(fileNum)
		);
	}
}

//スコア加算
void InGameUI::AddScore()
{
	//スコア加算
	m_nowScore = m_player->GetScore();
	//時間ボーナス分加算
	m_TimeBonusScore += enScoreType_TimeBonus * m_gameTimer;
	//最大スコアを超えないようにする
	m_nowScore = std::min<int>(m_nowScore, nsUI::nsScore::MAX);
	//計算したい桁数より上の桁の合計
	int harderDigitTimeCalc = 0;	

	//桁数分繰り返す
	for (int i = enMaxScoreDigit - 1; i >= 0; i--) {
		//一旦現在の数字を保存
		int oldScore = m_scoreUI[i].nowScore;			
		//計算する桁数より上の桁の合計を引いてさらにそれぞれの
		//m_nowScoreを桁数で割った値を代入
		m_scoreUI[i].nowScore = (m_nowScore - harderDigitTimeCalc) / nsUI::nsScore::DIGIT[i];
		//今計算中の桁の数値が変化したかどうか判定
		harderDigitTimeCalc += m_scoreUI[i].nowScore * nsUI::nsScore::DIGIT[i];
		//変化していなければ次の桁へ
		if (oldScore == m_scoreUI[i].nowScore) continue;

		//時間が変化しているのでスプライトを更新
		int fileNum = m_scoreUI[i].nowScore;
		UpdateSpriteInfo(
			&m_scoreUI[i].spriteRender
			, nsUI::nsScore::POS[i]
			, nsUI::nsScore::SCALE
			, GetNumberFilePath(fileNum)
		);
	}
	//過去のスコアを現在のスコアに更新
	if (m_nowScore >= m_pastScore)
	{
		m_pastScore = m_nowScore;
	}
}


//アイテム表示
void InGameUI::ItemUI()
{
	m_nowItem = m_player->GetItem();
	int fileNum = m_itemUI[m_nowItem].nowItem;
	UpdateSpriteInfo(
		&m_itemUI[m_nowItem].spriteRender
		, nsUI::nsItem::POS[m_nowItem]
		, nsUI::nsItem::SCALE
		, GetItemFilePath(fileNum)
	);
}


//マップ表示
void InGameUI:: MapUI()
{

}


//演出表示(死亡時の暗転のような)
void InGameUI::Direction()
{
	
	//プレイヤーの残基が0以下の時、又はスペースキーを押した際に半暗転する
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		SetBlackout(true);
		m_player->m_backout = true;
		UIColors::TRANSPARENCY_DEFAULT;
	}	
	Vector4 blackoutColor(UIColors::BLACK, UIColors::BLACK, UIColors::BLACK, UIColors::TRANSPARENCY_DEFAULT);
	m_spriteRender.SetMulColor(blackoutColor);
	m_spriteRender.Update();
	//プレイヤーの残基が０より大きい時Bボタンを押したら半暗転を解除する
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		SetBlackout(false);
	}	
}


//現在の時間を計測
void InGameUI::MeasureNowTime() {
	if(m_blackout)
	{
		return;
	}
	//一フレーム加算
	m_gameTimer += g_gameTime->GetFrameDeltaTime();
	//経ったフレーム分の時間を引く
	m_nowTime = nsUI::nsTimer::LIMIT - m_gameTimer;
	//0秒以下にはしない
	m_nowTime = std::max<float>(0.0f, m_nowTime);

	//計算したい桁数より上の桁の合計
	int harderDigitTimeCalc = 0;

	//桁数分繰り返す
	for (int i = enTime_num - 1; i >= 0; i--) {
		//一旦現在の数字を保存
		int oldTime = m_timeUI[i].nowTime;
		//計算する桁数より上の桁の合計を引いてさらにそれぞれの
		m_timeUI
			[i].nowTime = (m_nowTime - harderDigitTimeCalc) / nsUI::nsTimer::DIGIT[i];
		//今計算している桁の数値を合計値に加算
		harderDigitTimeCalc += m_timeUI[i].nowTime * nsUI::nsTimer::DIGIT[i];
		//今計算中の桁の数値が変化したかどうか判定
		//変化していなければ次の桁へ
		if (oldTime == m_timeUI[i].nowTime) continue;

		//時間が変化しているのでスプライトを更新
		int fileNum = m_timeUI[i].nowTime;

		UpdateSpriteInfo(
			&m_timeUI[i].spriteRender
			, nsUI::nsTimer::POS[i]
			, nsUI::nsTimer::SCALE
			, GetNumberFilePath(fileNum)
		);
	}
}


//画面移動先選択UI
void InGameUI::Selection()
{
	if (!m_blackout)
	{
		return;
	}
	if (GetAsyncKeyState(VK_UP)||g_pad[0]->IsTrigger(enButtonUp))
	{
		float emptiness = m_overFrameTransparency;
		m_overFrameTransparency = m_lordFrameTransparency;
		m_lordFrameTransparency = emptiness;
		m_sceneMovement = true;
	}
	if (GetAsyncKeyState(VK_DOWN)||g_pad[0]->IsTrigger(enButtonDown))
	{
		float emptiness = m_lordFrameTransparency;
		m_lordFrameTransparency = m_overFrameTransparency;
		m_overFrameTransparency = emptiness;
		m_sceneMovement = false;
	}

	Vector4 OverFrameColor(UIColors::RED, UIColors::BLUE, UIColors::GREEN, m_overFrameTransparency);
	Vector4 LordFrameColor(UIColors::RED, UIColors::BLUE, UIColors::GREEN, m_lordFrameTransparency);

	m_overSelectionFrame.SetMulColor(OverFrameColor);
	m_lordSelectionFrame.SetMulColor(LordFrameColor);

	m_overSelectionFrame.Update();
	m_lordSelectionFrame.Update();
}


//描画処理
void InGameUI::Render(RenderContext& rc)
{
	// 暗転中の描画
    if (m_blackout)
    {
        m_spriteRender.Draw(rc);
        m_overSelectionFrame.Draw(rc);
        m_lordSelectionFrame.Draw(rc);
    }
    
    // 常に表示されるUI
    m_koronSprite.Draw(rc);
    m_itemColumnUI.Draw(rc);
    m_playerfestureUI.Draw(rc);
    
    // 残基表示（配列を逆順で描画すると重なりが自然）
    for (int i = enResidue_num - 1; i >= 0; --i)
    {
        m_residueUI[i].spriteRender.Draw(rc);
    }
    
    // 時間表示
    for (int i = 0; i < enTime_num; ++i)
    {
        m_timeUI[i].spriteRender.Draw(rc);
    }
    
    // スコア表示
    for (int i = 0; i < enMaxScoreDigit; ++i)
    {
        m_scoreUI[i].spriteRender.Draw(rc);
    }
    
    // アイテム表示（現在選択中のアイテムのみ）
    if (m_nowItem >= 0 && m_nowItem < enItem_num)
    {
        m_itemUI[m_nowItem].spriteRender.Draw(rc);
    }
}
