#include "GroundBase.h"

void GroundBase::Init()
{}

void GroundBase::Update()
{}

void GroundBase::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
