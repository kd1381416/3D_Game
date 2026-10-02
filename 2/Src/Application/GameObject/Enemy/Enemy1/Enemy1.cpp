#include"Enemy1.h"

#include<Application/GameObject/Player/Player.h>

#include<Application/GameObject/Camera/TPSCamera/TPSCamera.h>

#include<Application/Scene/SceneManager.h>
#include<Application/Scene/GameScene/GameScene.h>

#include<Application/System/EnemySystem/EnemySystem.h>

void Enemy1::Init()
{
	//モデル読み込み
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Model/RobotBug/RobotBug.gltf");

	//アニメーション読み込み
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
	m_attackLength = 5.0f;
}

void Enemy1::PreUpdate()
{
//もしHPが0以下なら消える
	if (m_hp <= 0.0f)
	{
		m_isExpired = true;

		m_owner->GetEnemySystem()->RemoveEnemyNum();
	}

//Playerが索敵範囲内かどうかを判定(範囲内ならm_moveFlgをtrue)
	SearchPlayer();

	if (m_moveFlg)
	{
		m_dir = m_wpTarget.lock()->GetPos() - m_pos;
		m_dir.y = 0.0f;

		//攻撃可能範囲に入ったら攻撃状態にする
		if (m_dir.Length() <= m_attackLength)
		{
			if (m_currentState != MoveState::Attack)
			{
				m_currentState = MoveState::Attack;

				m_spAnimator->SetAnimationTime(60.0f, 70.0f);
			}
		}
	}
}

void Enemy1::Update()
{
	float _stopDistance = 8.0f;
	float _distance = m_dir.Length();

	if (_distance > _stopDistance)
	{
		m_dir.Normalize();

		m_movePower = 0.1f;

		if (_distance < _stopDistance + 0.1f)
		{
			m_movePower *= (_distance - _stopDistance) / 0.1f;

			if (m_movePower > 1.0f)
			{
				m_movePower = 1.0f;
			}
		}
	}
	else
	{
		m_animetionFlg = false;
	}

//ターゲット(Player)が索敵範囲内にいるなら動く+アニメーションする
	if (m_moveFlg)
	{
		m_pos += m_dir * m_movePower;
		m_animetionFlg = true;
	}

//アニメーション処理	
	if (m_animetionFlg)
	{
		if (!m_spAnimator)	return;
		if (!m_spModel)		return;

		m_spAnimator->AdvanceTime(m_spModel->WorkNodes());
		m_spModel->CalcNodeMatrices();
	}
}

void Enemy1::PostUpdate()
{
//押し出し処理
	for (auto& obj : m_owner->GetEnemySystem()->GetEnemyList())
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

//エイムを合わせる座標を割り出す
	m_aimPos = m_pos + Math::Vector3{ 0.0f, 1.5f, 0.0f };

//行列作成
	Math::Matrix	_scale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_pos);
	float	_angle = atan2(m_dir.x, m_dir.z) + DirectX::XM_PI;
	m_rotation = Math::Matrix::CreateRotationY(_angle);
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
	m_moveFlg = false;

	KdCollider::SphereInfo	_sphere;
	_sphere.m_sphere.Center = m_pos;
	_sphere.m_sphere.Radius = 50.0f;
	_sphere.m_type = KdCollider::TypePlayer;
	
	//全てのオブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//範囲内に入ったら追跡開始
		if (obj->Intersects(_sphere, nullptr))
		{
			m_moveFlg = true;
		}
	}
}
