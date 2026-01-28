#pragma once

//背景。
class Player;


class BackGround : public IGameObject
{
public:
    BackGround();
    ~BackGround();
	void Update();
    //ステージ選択結果を反映させるための関数
	void StageSelectSet(int stage);
    //描画関数。
    void Render(RenderContext& rc);
    //モデルレンダ―。     

    ModelRender m_modelRender;
	ModelRender m_boosStageModelRender;//ボスステージ用モデルレンダー
	ModelRender m_magumaModelRender[4];//マグマ用モデルレンダー
	ModelRender m_boosBattleField;
    PhysicsStaticObject m_physicsStaticObject;// 物理オブジェクト
    PhysicsStaticObject m_boosStageObject;//ボスステージ用の物理オブジェクト
	PhysicsStaticObject m_magumaObject[4];//マグマ用の物理オブジェクト
	PhysicsStaticObject m_boosFieldObejct;

	int m_stageSelect = 0;//ステージ選択結果保存用変数


private:
	int m_magumaTimer = 0;//マグマの動作タイマー
	int m_magumaState = 0;//マグマの状態
	int m_maxMaguma = 3;//マグマの最大値
	int m_minMaguma = 0;//マグマの最小値
	Player* m_player;//プレイヤー
	int m_plain=1;//平原ステージ用変数
	int m_indoor=2;//屋内ステージ用変数
	int m_snowField=3;//雪原ステージ用変数
	int m_bossStage=4;//ボスステージ用変数
	float m_switchingTime = 1.0f;//ステージ切り替え時間管理用変数
	float m_resetTime = 0.0f;//リセット用時間管理変数
	bool m_generate=false;
};