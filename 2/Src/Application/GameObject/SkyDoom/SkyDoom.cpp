#include "SkyDoom.h"

void SkyDoom::Init()
{
	m_spSkyDoomModel = std::make_shared<KdModelData>();
	m_spSkyDoomModel->Load("Asset/Model/SkyDoom/SkyDoom.gltf");

	m_pos = { 0.0f,0.0f,0.0f };
	m_scale = 100.0f;

	Math::Matrix	_scale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * _trans;

}

void SkyDoom::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spSkyDoomModel, m_mWorld);
}
