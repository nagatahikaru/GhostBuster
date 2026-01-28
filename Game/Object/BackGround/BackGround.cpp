#include "stdafx.h"
#include <string>
#include "BackGround.h"
#include "Character/Player/Player.h"

namespace {
	std::string FILE_PATH = ("Assets/stage/Maguma/");
	std::string FILE_PATH_TKM = (".tkm");
	std::string MAGUMA_FILE_PATH[4] = {
		"up","down","left","right"
	};
	std::string FILE_PATH_SRASYU = ("/");

	inline std::string GetMagumaFilePath(const int number)
	{
		return FILE_PATH + MAGUMA_FILE_PATH[number] + FILE_PATH_SRASYU + MAGUMA_FILE_PATH[number] + FILE_PATH_TKM;
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
	void InitData(
		ModelRender* modelRender
		, PhysicsStaticObject* physicsStaticObject	
		, std::string filePath) {
		modelRender->Init(filePath.c_str());
		physicsStaticObject->CreateFromModel(
		modelRender->GetModel()
		, modelRender->GetModel().GetWorldMatrix());//モデルから静的な物理オブジェクトを生成
		return;
	}
}


BackGround::BackGround()
{

	
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{
	if(m_stageSelect< m_bossStage)
	{
		if(!m_generate)
		{
			InitData(
				&m_modelRender
				, &m_physicsStaticObject
				, "Assets/stage/stage1.tkm"
			);
			m_generate = true;
		}
	}

	if(m_stageSelect==m_bossStage)
	{
		if (!m_generate)
		{
		for (int i = 0; i < 4; i++)
		{
			InitData(
				&m_magumaModelRender[i]
				, &m_magumaObject[i]
				, GetMagumaFilePath(i)
			);
		}

		InitData(
			&m_boosBattleField
			, &m_boosFieldObejct
			, "Assets/stage/BossField.tkm"
		);

		InitData(
			&m_boosStageModelRender
			, &m_boosStageObject
			, "Assets/stage/BossStage.tkm"
		);
		m_generate = true;
		}
	}


	if (m_stageSelect == m_bossStage)
	{
		//マグマの動作
		m_magumaTimer += g_gameTime->GetFrameDeltaTime();
		if (m_magumaTimer > m_switchingTime)
		{
			m_magumaState++;
			if (m_magumaState >= m_maxMaguma)
			{
				m_magumaState = m_minMaguma;
			}
			m_magumaTimer = m_resetTime;
		}
	}
}

void BackGround::StageSelectSet(int stage)
{
	//ステージ選択結果を保存
	m_stageSelect = stage;
}


void BackGround::Render(RenderContext& rc)
{
	//ステージ選択結果に応じて描画
	
	if(m_stageSelect< m_bossStage)
	{
		m_modelRender.Draw(rc);
	}

	if(m_stageSelect== m_bossStage)
	{
		m_boosStageModelRender.Draw(rc);
		m_magumaModelRender[m_magumaState].Draw(rc);
		m_boosBattleField.Draw(rc);
	}

}