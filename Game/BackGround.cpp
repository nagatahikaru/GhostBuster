#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_modelRender.Init("Assets/stage/stage1.tkm");
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());//モデルから静的な物理オブジェクトを生成
}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}