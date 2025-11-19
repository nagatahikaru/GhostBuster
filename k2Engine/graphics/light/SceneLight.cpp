#include "k2EnginePreCompile.h"
#include "graphics/light/SceneLight.h"
#include "graphics/light/VolumeSpotLight.h"

namespace nsK2Engine {
    void SPointLight::Update()
    {
        // 使用中のライトはカメラ空間での座標を計算する。
        if (!isUse) {
            return;
        }
        positionInView = m_position;
        g_camera3D->GetViewMatrix().Apply(positionInView);
    }
    void SSpotLight::Update()
    {
        // 使用中のライトはカメラ空間での座標を計算する。
        if (!isUse) {
            return;
        }
        positionInView = m_position;
        g_camera3D->GetViewMatrix().Apply(positionInView);
        Matrix cameraRotInv = g_camera3D->GetCameraRotation();
        cameraRotInv.Inverse();
        cameraRotInv.Apply(directionInView);
    }
    void SceneLight::Init()
    {
        // 太陽光
        m_light.directionalLight[0].color.x = 1.2f;//赤
        m_light.directionalLight[0].color.y = 1.2f;//緑
        m_light.directionalLight[0].color.z = 1.2f;//青

		m_light.directionalLight[0].direction.x = 0.0f;//ｘ方向
		m_light.directionalLight[0].direction.y = -1.0f;//ｙ方向
		m_light.directionalLight[0].direction.z = 0.0f;//ｚ方向
		m_light.directionalLight[0].direction.Normalize();//正規化
		m_light.directionalLight[0].castShadow = true;//影を落とす

        //
      /*  m_light.directionalLight[1].color.x = 1.0f;
        m_light.directionalLight[1].color.y = 1.0f;
        m_light.directionalLight[1].color.z = 1.0f;

        m_light.directionalLight[1].direction.x = -1.0f;
        m_light.directionalLight[1].direction.y = -1.0f;
        m_light.directionalLight[1].direction.z = 1.0f;
        m_light.directionalLight[1].direction.Normalize();
        m_light.directionalLight[1].castShadow = false;

        // 地面からの照り返し
        m_light.directionalLight[2].color.x = 0.6f;
        m_light.directionalLight[2].color.y = 0.6f;
        m_light.directionalLight[2].color.z = 0.6f;

        m_light.directionalLight[2].direction.x = -1.0f;
        m_light.directionalLight[2].direction.y = 1.0f;
        m_light.directionalLight[2].direction.z = 1.0f;
        m_light.directionalLight[2].direction.Normalize();*/

		m_light.ambinetLight.x = 1.0f;//環境光の色 赤
		m_light.ambinetLight.y = 1.0f;//環境光の色 緑
		m_light.ambinetLight.z = 1.0f;//環境光の色 青
        m_light.eyePos = g_camera3D->GetPosition();
        m_light.numPointLight = 0;

        // 全てのポイントライトを未使用にする
        for (auto& pt : m_light.pointLights) {
            pt.UnUse();
            pt.SetAffectPowParam(1.0f);
            m_unusePointLightQueue.push_back(&pt);
        }
        // すべてのスポットライトを未使用にする。
        int spNo = 0;
        for (auto& sp : m_light.spotLights) {
            sp.UnUse();
            sp.SetNo(spNo);
            m_unuseSpotLightQueue.push_back(&sp);
            spNo++;
        }
    }
    
    
    
    void SceneLight::Update()
    {
        m_light.numPointLight = MAX_POINT_LIGHT - static_cast<int>(m_unusePointLightQueue.size());
        m_light.numSpotLight = MAX_SPOT_LIGHT - static_cast<int>(m_unuseSpotLightQueue.size());
    }
}