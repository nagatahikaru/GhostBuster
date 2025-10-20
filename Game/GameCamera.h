#pragma once
#include "camera/SpringCamera.h"



class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void FixedCamera();
	void CameraDistance();
	void CameraMove();

	Player* m_player = nullptr;
	Vector3 m_toCameraPos;
	Vector3 m_cameraSpeed;
	Quaternion  m_toCameraRot;
	SpringCamera m_springCamera;
	float m_t = 0.1f;

	/*enum CameraPos {
		cameraPos_Start,
		cameraPos_InGame,
		cameraPos_OutGame,
	};
	CameraPos m_cameraPos = cameraPos_Start;*/

	bool m_fixedCameraFlag = false;
	bool m_cameraMoveFlag = true;
};