#pragma once
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& renderContxt);
private:

	//�������烁���o�[�ϐ�
	ModelRender m_modelRender;//���f�������_�[�B
	//Hands On1�@���W�f�[�^��ǉ�����B
	Vector3 m_position;//���W�B

	//�N�H�[�^�j�I���B
	Quaternion rot;
};

