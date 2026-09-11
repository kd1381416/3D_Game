#include "Enemy1.h"

#include<Application/GameObject/Player/Player.h>

#include<Application/GameObject/Camera/TPSCamera/TPSCamera.h>

#include<Application/Scene/SceneManager.h>
#include<Application/Scene/GameScene/GameScene.h>

#include<Application/System/EnemySystem/EnemySystem.h>

void Enemy1::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Model/RobotBug/RobotBug.gltf");
	m_spAnimator = std::make_shared<KdAnimator>();
	m_spAnimator->SetAnimation(m_spModel->GetAnimation("WALKING"));

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RobotBug", m_spModel, KdCollider::TypeDamage | KdCollider::TypeObject);

	if (!m_pDebugWire)
	{
		m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	}

	m_pos	= { 0.0f,1.0f,15.0f };
	m_aimPos = m_pos + Math::Vector3{ 0.0f, 0.0f, 0.0f };
	m_scale = { 0.03f,0.03f,0.03f };

	m_hp = 100.0f;
}

void Enemy1::Update()
{
	m_dir = m_wpTarget.lock()->GetPos() - m_pos;
	m_dir.y = 0;

	float _stopDistance = 5.0f;
	float _distance = m_dir.Length();

	if (_distance > _stopDistance)
	{

		m_dir.Normalize();

		float _moveSpeed = 0.1f;

		if (_distance < _stopDistance + 0.1f)
		{
			_moveSpeed *= (_distance - _stopDistance) / 0.1f;
		}

		float	_angle = atan2(m_dir.x, m_dir.z) + DirectX::XM_PI;
		m_rotation = Math::Matrix::CreateRotationY(_angle);

		m_pos += m_dir * _moveSpeed;
		m_animetionFlg = true;
	}
	else
	{
		m_animetionFlg = false;
	}

	if(m_animetionFlg)
	{
		if (!m_spAnimator)	return;
		if (!m_spModel)		return;

		m_spAnimator->AdvanceTime(m_spModel->WorkNodes());
		m_spModel->CalcNodeMatrices();
	}

	for(auto& obj : m_owner->GetEnemySystem()->GetEnemyList())
	{
		auto _enemy = obj.lock();

		if (!_enemy)continue;
		if (_enemy.get() == this)continue;

		Math::Vector3 diff = _enemy->GetPos() - m_pos;

		diff.y = 0.0f;

		float distance = diff.Length();

		float hitDistance = 4.0f;

		if (distance < hitDistance)
		{
			// 重なり量
			float overlap = hitDistance - distance;

			// 敵同士の方向
			diff.Normalize();

			// 半分ずつ押し戻す
			m_pos -= diff * (overlap * 0.5f);
			_enemy->SetPos(_enemy->GetPos() + diff * (overlap * 0.5f));
		}
	}
	//m_pDebugWire->AddDebugSphere(m_aimPos, 2.0f, kBlueColor);
}

void Enemy1::PostUpdate()
{
	m_aimPos = m_pos + Math::Vector3{ 0.0f, 1.5f, 0.0f };

	if (m_hp <= 0.0f) { m_isExpired = true; }

	//行列作成
	Math::Matrix	_scale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * m_rotation * _trans;
}

void Enemy1::DrawLit()
{
	EnemyBase::DrawLit();
}

void Enemy1::GenerateDepthMapFromLight()
{
	if (!m_spModel) return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Enemy1::OnHit()
{
	float	_hitDamege = 0.0f;

	switch (m_wpTarget.lock()->GetNowState())
	{
	case Player::PlayerState::Nomal:
		_hitDamege = 35.0f;
		break;
	case Player::PlayerState::Gatling:
		_hitDamege = 10.0f;
		break;
	default:
		break;
	}

	m_hp -= _hitDamege;
}

void Enemy1::SearchPlayer()
{
	KdCollider::SphereInfo	_spher;
	_spher.m_sphere.Center = m_pos;
	_spher.m_sphere.Radius = 5.0f;
	_spher.m_type = KdCollider::TypePlayer;
}
