#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class GameClear;

//Game�V�[�����Ǘ�����N���X�B
class Game : public IGameObject
{
public:
	Game();
	~Game();
	//�X�V����
	void Update();

	// "*"�����鎞��->�Ł@����ȊO�̎���"."��"*"���g��Ȃ�
	Player* player;         //�v���C���[
	GameCamera* gameCamera; //�Q�[���J����
	SoundSource* gameBGM;   //�Q�[������BGM
	GameClear* gameclear;   //�Q�[���J����
	BackGround* backGround; //�w�i	
};

