#include "EnemyBase.h"

void EnemyBase::Init()
{}

void EnemyBase::Update()
{
}

void EnemyBase::PostUpdate()
{
	//行列作成
	Math::Matrix	_scale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * _trans;
}

void EnemyBase::DrawLit()
{
	if (!m_spModel) return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}