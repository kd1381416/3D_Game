#include"Enemy1.h"

#include<Application/main.h>

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

	m_pos	= { 0.0f,0.0f,15.0f };
	m_aimPos = m_pos + Math::Vector3{ 0.0f, 0.0f, 0.0f };
	m_scale = { 0.03f,0.03f,0.03f };

	m_hp = 1.0f;
	m_attackLength = 8.0f;
}

void Enemy1::PreUpdate()
{
	// 死亡状態なら、死亡処理を繰り返さない
	if (m_currentState == MoveState::Death)
	{
		return;
	}

	// HPが0以下なら死亡
	if (m_hp <= 0.0f)
	{
		ChangeState(MoveState::Death);
		return;
	}

	// プレイヤーの索敵
	SearchPlayer();

	// ターゲットの方向と距離を更新
	auto target = m_wpTarget.lock();

	if (!target)
	{
		m_moveFlg = false;
		m_dir = Math::Vector3::Zero;
	}
	else
	{
		m_dir = target->GetPos() - m_pos;
		m_dir.y = 0.0f;
	}

	// 状態遷移
	EnemyBase::UpdateState();
}

void Enemy1::Update()
{
	//今の状態に合わせて行動する
	switch (m_currentState)
	{
	case MoveState::None:
		break;

	case MoveState::Move:
		Move();
		break;
	
	case MoveState::Attack:
		Attack();
		break;
	
	case MoveState::Death:
		Death();
		break;
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

		m_spAnimator->AdvanceTime(m_spModel->WorkNodes(), m_animetionSpeed);
		m_spModel->CalcNodeMatrices();
	}

	//攻撃リキャスト時間を進める
	if (m_attackRecast >= 0.0f)
	{
		m_attackRecast -= 1.0f;

		if (m_attackRecast < 0.0f)
		{
			m_attackRecast = 0.0f;
		}
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

void Enemy1::ChangeState(MoveState _nextState)
{
	// 同じ状態なら何もしない
	if (m_currentState == _nextState) return;

	// 状態を変更
	m_currentState = _nextState;

	// 状態に応じて初期化
	switch (m_currentState)
	{
	case MoveState::None:
		m_movePower = 0.0f;
		m_animetionSpeed = 1.0f;
		m_animetionFlg = false;

		m_spAnimator->SetAnimationTime(0.0f, 0.0f);
		break;

	case MoveState::Move:
		m_movePower = 0.0f;
		m_animetionSpeed = 1.0f;
		m_animetionFlg = true;

		m_spAnimator->SetAnimationTime(0.0f, 100.0f);
		break;

	case MoveState::Attack:
		m_movePower = 0.0f;
		m_animetionSpeed = 0.8f;
		m_animetionFlg = true;

		m_attackJumpSpeed	= 0.25f;
		m_attackMoveSpeed	= 0.12f;
		m_attackGravity		= 0.01f;

		m_spAnimator->SetAnimationTime(110.0f, 250.0f);
		break;

	case MoveState::Death:
		m_movePower = 0.0f;
		m_animetionSpeed = 1.0f;
		m_animetionFlg = true;

		m_spAnimator->SetAnimationTime(260.0f, 350.0f);
		break;
	}
}

void Enemy1::OnHit()
{
	auto _target = m_wpTarget.lock();

	if (!_target) return;

	float _hitDamage = 0.0f;

	switch (_target->GetNowState())
	{
	case Player::PlayerState::Nomal:
		_hitDamage = 35.0f;
		break;
	case Player::PlayerState::Gatling:
		_hitDamage = 10.0f;
		break;
	default:
		break;
	}

	m_hp -= _hitDamage;
}

void Enemy1::SearchPlayer()
{
	auto _target = m_wpTarget.lock();

	if (!_target)
	{
		m_moveFlg = false;
		return;
	}

	Math::Vector3 _diff = _target->GetPos() - m_pos;
	_diff.y = 0.0f;

	float _distance = _diff.Length();

	float _searchRange = 50.0f;

	m_moveFlg = _distance <= _searchRange;
}

//攻撃処理
// とびかかり攻撃
void Enemy1::Attack()
{
	if (!m_spAnimator) return;

	float animTime = m_spAnimator->GetAnimationTime();

	//攻撃アニメーションの開始位置でジャンプを開始
	if (!m_attackStarted && animTime >= 183.0f)
	{
		m_attackStarted = true;

		auto target = m_wpTarget.lock();

		if (target)
		{
			// プレイヤーの位置から飛ぶ方向を計算
			m_attackDir = target->GetPos() - m_pos;

			// 水平方向だけを使う
			m_attackDir.y = 0.0f;

			if (m_attackDir.LengthSquared() > 0.0001f)
			{
				m_attackDir.Normalize();
			}
			else
			{
				m_attackDir = Math::Vector3::Zero;
			}
		}
		else
		{
			// ターゲットがいない場合は停止する
			m_attackDir = Math::Vector3::Zero;
		}

		// ジャンプ開始時の地面の高さを保存
		m_attackGroundY = m_pos.y;

		// 水平方向への初速
		m_attackVelocity = m_attackDir * m_attackMoveSpeed;

		// 上方向への初速
		m_attackVelocity.y = m_attackJumpSpeed;
	}

	//空中移動・重力・着地判定
	if (m_attackStarted && !m_attackLanded)
	{
		// 速度を位置に加算
		m_pos += m_attackVelocity;

		// 重力によって落下速度を増やす
		m_attackVelocity.y -= m_attackGravity;

		// 仮の接地判定
		if (m_pos.y <= m_attackGroundY)
		{
			m_pos.y = m_attackGroundY;

			m_attackVelocity = Math::Vector3::Zero;
			m_attackLanded = true;
		}
	}

	//攻撃アニメーション終了
	if (animTime >= 249.0f)
	{
		m_attackRecast = 6000.0f;

		ChangeState(MoveState::None);
	}
}

void Enemy1::Move()
{
	float _stopDistance = 8.0f;
	float _distance = m_dir.Length();

	//プレイヤーとの距離が一定以上なら移動する
	if (_distance > _stopDistance)
	{
		m_dir.Normalize();

		m_movePower = 0.1f;

		if (_distance < _stopDistance + 0.1f)
		{
			m_movePower *= (_distance - _stopDistance) / 0.1f;

			if (m_movePower > 0.5f)
			{
				m_movePower = 0.5f;
			}
		}
	}
	else
	{
		m_movePower = 0.0f;
		ChangeState(MoveState::None);
	}
}

void Enemy1::Death()
{	


}
