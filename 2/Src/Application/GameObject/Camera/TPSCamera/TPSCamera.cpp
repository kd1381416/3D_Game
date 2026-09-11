#include "TPSCamera.h"

#include<Application/GameObject/Enemy/EnemyBase.h>

#include<Application/Scene/SceneManager.h>
#include<Application/Scene/GameScene/GameScene.h>

#include<Application/System/EnemySystem/EnemySystem.h>

void TPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f, 2.0f, -5.0f);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void TPSCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	SearchTargetEnemy();	//ターゲットのエネミーを探す
	UpdateAimAssist();		//エイムアシスト
	m_mRotation = GetRotationMatrix();
	m_mWorld = m_mLocalPos * m_mRotation * _targetMat;


	// ↓めり込み防止の為の座標補正計算↓
	// ①当たり判定(レイ判定)用の情報作成
	KdCollider::RayInfo rayInfo;
	// レイの発射位置を設定
	rayInfo.m_pos = GetPos();

	// レイの発射方向を設定
	rayInfo.m_dir = Math::Vector3::Down;
	// レイの長さを設定
	rayInfo.m_range = 1000.f;
	if (_spTarget)
	{
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetPos.y += 0.1f;
		rayInfo.m_dir = _targetPos - GetPos();
		rayInfo.m_range = rayInfo.m_dir.Length();
		rayInfo.m_dir.Normalize();
	}

	// 当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	// ②HIT判定対象オブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject> spGameObj = wpGameObj.lock();
		if (spGameObj)
		{
			std::list<KdCollider::CollisionResult> retRayList;
			spGameObj->Intersects(rayInfo, &retRayList);

			// ③ 結果を使って座標を補完する
			// レイに当たったリストから一番近いオブジェクトを検出
			float maxOverLap = 0;
			Math::Vector3 hitPos = {};
			bool hit = false;
			for (auto& ret : retRayList)
			{
				// レイを遮断しオーバーした長さが
				// 一番長いものを探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					hit = true;
				}
			}
			if (hit)
			{
				// 何かしらの障害物に当たっている
				Math::Vector3 _hitPos = hitPos;
				_hitPos += rayInfo.m_dir * 0.4f;
				SetPos(_hitPos);
			}
		}
	}
}

void TPSCamera::SearchTargetEnemy()
{
	//現在のカメラの正面
	Math::Vector3	_cameraDir = m_mWorld.Backward();

	//カメラの位置
	Math::Vector3	_cameraPos = GetPos();
	
	//照準からの最大距離
	float _bestDot = 0.95f;

	//ターゲットをリセット
	m_wpTargetEnemy.reset();

	for (auto& _wpEnemy : m_owner->GetEnemySystem()->GetEnemyList())
	{
		auto _spEnemy = _wpEnemy.lock();

		//敵がいなければ次のループへ
		if (!_spEnemy) continue;
	
		//敵の位置
		Math::Vector3	_enemyPos = _spEnemy->GetAimPos();

		//カメラから敵までの方向
		Math::Vector3	_enemyDir = _enemyPos - _cameraPos;

		//距離が0ならスキップ
		if (_enemyPos.LengthSquared() <= 0.0f) continue;

		//正規化
		_enemyDir.Normalize();

		//カメラの正面との一致度
		float _dot = _cameraDir.Dot(_enemyDir);

		//照準範囲外時
		if (_dot < 0.991f)continue;

		//一番近い敵をターゲットにする
		if(_dot > _bestDot)
		{ 
			_bestDot = _dot;
			m_wpTargetEnemy = _spEnemy;
		}
	}
}

void TPSCamera::UpdateAimAssist()
{
	auto _spTarget = m_wpTargetEnemy.lock();

	//ターゲットがいなければ終了
	if (!_spTarget) return;

	//ターゲットの位置
	Math::Vector3	_targetPos = _spTarget->GetAimPos();

	//少し上に照準を合わせる
	_targetPos.y += 1.0f;

	//カメラから敵の方向
	Math::Vector3	_targetDir = _targetPos - GetPos();

	//距離が0なら終了
	if (_targetDir.LengthSquared() <= 0.0f) return;

	//正規化
	_targetDir.Normalize();

	//敵方向のYawを計算
	float _targetYaw = DirectX::XMConvertToDegrees(atan2(_targetDir.x, _targetDir.z));

	//xz平面での距離
	float _horizontalLength = sqrt(_targetDir.x * _targetDir.x + _targetDir.z * _targetDir.z);

	//敵方向のPitchを計算
	float _targetPitch = DirectX::XMConvertToDegrees(-atan2(_targetDir.y, _horizontalLength));

	//現在の角度の差
	float _yawDiff		= GetAngleDifferene(m_DegAng.y, _targetYaw);
	float _pitchDiff	= _targetPitch - m_DegAng.x;

	//エイムアシストの強さ
	float _assistPower = 0.1f;

	//現在の角度を少しずつターゲット方向に近づける
	m_DegAng.y += _yawDiff	 * _assistPower;
	m_DegAng.x += _pitchDiff * _assistPower;
}

float TPSCamera::GetAngleDifferene(float _current, float _target)
{
	float _diff = _target - _current;

	while (_diff > 180.0f)
	{
		_diff -= 360.0f;
	}

	while (_diff < -180.0f)
	{
		_diff += 360.0f;
	}

	return _diff;
}
