#include "stdafx.h"
#include "ResultUI.h"


namespace {
	std::string FILE_PATH = ("Assets/sprite/Number/");
	std::string FILE_PATH_DDS = (".DDS");
	std::string NUMBER_FILE_PATH[10] = {
		"0","1","2","3","4","5","6","7","8","9"
	};

	std::string ITEMMODEL_FILE_PATH[2] = {
		"None","Snowball"
	};

	inline std::string GetNumberFilePath(const int number)
	{
		return FILE_PATH + NUMBER_FILE_PATH[number] + FILE_PATH_DDS;
	}

	inline std::string GetItemFilePath(const int itemType)
	{
		return FILE_PATH + ITEMMODEL_FILE_PATH[itemType] + FILE_PATH_DDS;
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
		, const std::string filePath) {
		spriteRender->Init(filePath.c_str(), 1.0f, 1.0f);
		spriteRender->SetPosition(pos);
		spriteRender->SetScale(scl);
		spriteRender->Update();
	}

}





ResultUI::ResultUI()
{	

}

ResultUI::~ResultUI()
{

}

//開始処理
bool ResultUI::Start()
{
	return true;
}

//更新処理
void ResultUI::Update()
{	
	
}

//スコアUI初期化
void ResultUI::InitializeScore()
{
	m_nowScore = reUI::reScore::MIN;
	m_scoreUI[0].nowScore = 0;
	for (int i = 0; i < reMaxScoreDigit; i++)
	{
		int fileNum = m_scoreUI[i].nowScore;
		UpdateSpriteInfo(
			&m_scoreUI[i].spriteRender
			, reUI::reScore::POS[i]
			, reUI::reScore::SCALE
			, GetNumberFilePath(fileNum));
	}
}

//クリアタイムUI初期化
void ResultUI::InitializeClearTime()
{
	//クリアした時間を取得
	m_nowTime = m_inGameUI->GetNowTime();
	//0秒以下にはしない
	m_nowTime = std::max<float>(0.0f, m_nowTime);

	//計算したい桁数より上の桁の合計
	int harderDigitTimeCalc = 0;

	//桁数分繰り返す
	for (int i = reTime_num - 1; i >= 0; i--) {
		//一旦現在の数字を保存
		int oldTime = m_timeUI[i].nowTime;
		//計算する桁数より上の桁の合計を引いてさらにそれぞれの
		m_timeUI
			[i].nowTime = (m_nowTime - harderDigitTimeCalc) / reUI::reTimer::DIGIT[i];
		//今計算している桁の数値を合計値に加算
		harderDigitTimeCalc += m_timeUI[i].nowTime * reUI::reTimer::DIGIT[i];
		//今計算中の桁の数値が変化したかどうか判定
		//変化していなければ次の桁へ
		if (oldTime == m_timeUI[i].nowTime) continue;

		//時間が変化しているのでスプライトを更新
		int fileNum = m_timeUI[i].nowTime;

		UpdateSpriteInfo(
			&m_timeUI[i].spriteRender
			, reUI::reTimer::POS[i]
			, reUI::reTimer::SCALE
			, GetNumberFilePath(fileNum)
		);
	}
}

//獲得スターUI初期化
void ResultUI::InitializeGetStar()
{

}

//演出表示(死亡時の暗転のような)
void ResultUI::Direction()
{

}

//描画処理
void ResultUI::Render(RenderContext& rc)
{


}
