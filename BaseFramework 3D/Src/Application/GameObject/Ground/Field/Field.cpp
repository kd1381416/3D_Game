#include "Field.h"

void Field::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Model/Block/Block.gltf");
}

void Field::Update()
{
	m_mWorld = Math::Matrix::CreateTranslation(m_position);
}

void Field::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Field::JsonInput(const nlohmann::json& _injson)
{
	KdGameObject::JsonInput(_injson);
}
