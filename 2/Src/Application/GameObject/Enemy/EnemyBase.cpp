#include "EnemyBase.h"

#include <Application/GameObject/Player/Player.h>

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

void EnemyBase::UpdateState()
{
	//HPが０になったら死亡状態にする
	if (m_hp <= 0.0f)
	{
		ChangeState(MoveState::Death);
	}

	//攻撃中は状態を変更しない
	if (m_currentState == MoveState::Attack)
	{
		return;
	}

	//ターゲットが見つかっていなけらば何もしない
	if (!m_moveFlg)
	{
		return;
	}

	//ターゲットとの距離で行動を決める
	float _distance = m_dir.Length();

	if(_distance < m_attackLength && m_attackRecast <= 0.0f)
	{
		ChangeState(MoveState::Attack);
	}
	else
	{
		ChangeState(MoveState::Move);
	}
}
