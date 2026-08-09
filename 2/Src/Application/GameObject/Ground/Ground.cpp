#include "Ground.h"

void Ground::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Model/Block/Block.gltf");
	
	m_scale = { 10.0f,1.0f,10.0f };
	m_pos	= { 0.0f,0.0f,0.0f };
}

void Ground::Update()
{}

void Ground::PostUpdate()
{
	Math::Matrix	_scale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * _trans;
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
