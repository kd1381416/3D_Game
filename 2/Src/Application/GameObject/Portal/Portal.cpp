#include "Pch.h"
#include "Portal.h"

void Portal::Init()
{
	if(!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Model/Portal/Portal.gltf");
	}

	m_pos = { 0.0f,1.0f,50.0f };
	m_scale = { 2.0f,2.0f,2.0f };
}

void Portal::Update()
{
	Math::Matrix	_scale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * _trans;
}

void Portal::DrawLit()
{
	if (!m_spModel)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
