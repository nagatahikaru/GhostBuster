#pragma once
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& renderContxt);
private:

	//ここからメンバー変数
	ModelRender m_modelRender;//モデルレンダー。
	//Hands On1　座標データを追加する。
	Vector3 m_position;//座標。

	//クォータニオン。
	Quaternion rot;
};

