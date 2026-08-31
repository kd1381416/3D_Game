#include "Player.h"

#include<Application/Scene/SceneManager.h>

#include<Application/GameObject/Camera/TPSCamera/TPSCamera.h>

#include<Application/GameObject/Bullet/Bullet.h>

#include<Application/GameObject/Enemy/EnemyBase.h>

void Player::Init()
{
	m_spUnderModel = std::make_shared<KdModelWork>();
	m_spUnderModel->SetModelData("Asset/Model/TankUnder/TankUnder.gltf");

	m_spGatlingModel = std::make_shared<KdModelWork>();
	m_spGatlingModel->SetModelData("Asset/Model/Gatling/Gatling.gltf");

	m_spUpperModel = std::make_shared<KdModelWork>();
	m_spUpperModel->SetModelData("Asset/Model/TankUpper/TankUpper.gltf");

	if (!m_pDebugWire)
	{
		m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	}

	m_pos = { 0.0f,1.0f,0.0f };
}

void Player::Update()
{
	//===================================================================
	// 移動処理
	//===================================================================
		//方向ベクトル = 長さ1
	Math::Vector3 _dir = { 0,0,0 };

	bool _moveflg = false;

	//前
	if (GetAsyncKeyState('W') & 0x8000)
	{
		_dir += { 0, 0, 1 };
		_moveflg = true;
	}
	//左
	if (GetAsyncKeyState('A') & 0x8000)
	{
		_dir += {-1, 0, 0 };
		_moveflg = true;
	}
	//後
	if (GetAsyncKeyState('S') & 0x8000)
	{
		_dir += { 0, 0, -1 };
		_moveflg = true;
	}
	//右
	if (GetAsyncKeyState('D') & 0x8000)
	{
		_dir += { 1, 0, 0 };
		_moveflg = true;
	}

	//移動処理
	_dir = _dir.TransformNormal(_dir, m_wpCamera.lock()->GetRotationYMatrix());

	m_pos += _dir * m_movePower;

	//===================================================================
	//移動中
	//===================================================================
	if (_moveflg)
	{
		//方向ベクトルを強制的に1にする(正規化)
		_dir.Normalize();

		//キャラが向いている方向
		//①キャラの回転行列
		Math::Matrix	_nowrotatmat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
		//②ベクトルを変形させる
		Math::Vector3	_nowdir = Math::Vector3::TransformNormal(Math::Vector3{ 0,0,1 }, _nowrotatmat);
		//                                       ↑トランスフォームノーマル(ベクトルを回転行列を使って変形させる)

		//簡単にオブジェクトの向きを取得する方法
		//_nowdir = m_mWorld.Backward();

		//③向きたい方向
		Math::Vector3	_todir = _dir;

		//内積 = ベクトルA * ベクトルB * cos(なす角)
		//  ＝   _nowdir(1)* _todir(1) * cos(なす角) 
		//  ＝   cos(なす角)
		//※cosをacosで計算すると角度が出る

		//④内積を求める(ベクトルA・ベクトルB)
		float	dot = _nowdir.Dot(_todir);

		//⑤角度に変換
		float	_angle = DirectX::XMConvertToDegrees(acos(dot));

		KdDebugGUI::Instance().ClearLog();
		KdDebugGUI::Instance().AddLog("%f\n", _angle);

		//少しでも開店する必要があった場合
		if (_angle >= 0.1f)
		{
			//回転角度の上限
			if (_angle >= 5.0f)
			{
				_angle = 5.0f;
			}

			//外積 = 2本のベクトルに対して垂直なベクトル
			Math::Vector3	_cross = _nowdir.Cross(_todir);

			if (_cross.y >= 0)	//右回転
			{
				m_angle += _angle;
				if (m_angle >= 360) { m_angle -= 360; }
			}
			else				//左回転 
			{
				m_angle -= _angle;
				if (m_angle <= -360) { m_angle += 360; }
			}
		}

		KdDebugGUI::Instance().AddLog("%f\n", m_angle);

		std::shared_ptr<CameraBase> _camera = m_wpCamera.lock();

		if (_camera)
		{
			_dir = _dir.TransformNormal(_dir, _camera->GetRotationYMatrix());
		}
	}
	//===================================================================
	// 攻撃(左クリック)
	//===================================================================
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_shotFlg)
		{
			// 銃口位置をデバッグ表示
			Math::Vector3 _muzzlepos = (Math::Matrix::CreateTranslation({ 0.0f, 0.0f, 2.5f }) * m_upperMatrix).Translation();
			//m_pDebugWire->AddDebugSphere(_muzzlepos, 0.05f, kBlueColor);

			Math::Vector3	_bulletdir;
			float _bulletSpeed = 0.0f;
			auto _spCamera = m_wpCamera.lock();

			if (!_spCamera)return;

			auto _spTargetEnemy = _spCamera->GetTargetEnemy().lock();

			if (_spTargetEnemy)
			{
				_bulletdir = _muzzlepos - _spTargetEnemy->GetAimPos();
				_bulletdir.Normalize();
				_bulletSpeed = -5.0f;
			}
			else
			{
				if (!_spCamera)return;

				Math::Vector3	_cameraPos = _spCamera->GetPos();
				float	_range;

				_spCamera->WorkCamera()->GenerateRayInfoFromClientPos({ 640,360 }, _cameraPos, _bulletdir, _range);

				KdCollider::RayInfo	_ray;
				_ray.m_pos = _cameraPos;
				_ray.m_dir = _bulletdir;
				_ray.m_range = _range;
				_ray.m_type = KdCollider::TypeDamage | KdCollider::TypeGround;

				//全オブジェクトと当たり判定
				std::list<KdCollider::CollisionResult>	_hitraylist;

				for (auto& obj : SceneManager::Instance().GetObjList())
				{
					obj->Intersects(_ray, &_hitraylist);
				}

				//一番近いオブジェクトを検出
				float	_overlap = 0;

				for (auto& ret : _hitraylist)
				{
					if (_overlap < ret.m_overlapDistance)
					{
						//更新
						_overlap = ret.m_overlapDistance;

						//方向ベクトル
						_bulletdir = ret.m_hitPos - (m_pos + Math::Vector3{ 0,2.0f,0 });

						_bulletdir.Normalize();
					}
				}

				_bulletSpeed = 5.0f;
			}

			auto _bullet = std::make_shared<Bullet>();
			_bullet->Init();
			_bullet->Shot(_muzzlepos, _bulletdir, _bulletSpeed);
			SceneManager::Instance().AddObject(_bullet);

			switch (m_nowState)
			{
			case Player::PlayerState::Nomal:
				m_shotFlg = false;
				m_shotDilay = 60.0f;
				break;
			case Player::PlayerState::Gatling:
				m_shotFlg = false;
				m_gatlingCount++;

				if (m_gatlingCount >= 100)
				{
					m_shotDilay = 120.0f;
				}
				else { m_shotDilay = 3.0f; }
				break;
			default:
				break;
			}
		}
	}

	m_shotDilay--;
	if (m_shotDilay <= 0)
	{
		m_shotFlg = true;
		m_shotDilay = 0.0f;

		if (m_gatlingCount >= 100) { m_gatlingCount = 0; }
	}

	//モード切り替え
	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_nowState = PlayerState::Nomal;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_nowState = PlayerState::Gatling;
	}

	//行列作成
	Math::Matrix	_scale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_pos);
	m_underMatrix = _scale * _rotY * _trans;
	m_mWorld = m_underMatrix;

	_scale = Math::Matrix::CreateScale({ 1.0f,1.0f,1.0f });
	_rotY = m_wpCamera.lock()->GetRotationYMatrix();
	_trans = Math::Matrix::CreateTranslation(m_pos + Math::Vector3{ 0.0f,1.1f,0.0f });
	m_upperMatrix = _scale * _rotY * _trans;
	
}

void Player::PostUpdate()
{
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spUnderModel, m_underMatrix);

	switch (m_nowState)
	{
	case Player::PlayerState::Nomal:
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spUpperModel, m_upperMatrix);
		break;
	case Player::PlayerState::Gatling:
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spGatlingModel, m_upperMatrix);
		break;
	default:
		break;
	}
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spUnderModel, m_underMatrix);

	switch (m_nowState)
	{
	case Player::PlayerState::Nomal:
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spUpperModel, m_upperMatrix);
		break;
	case Player::PlayerState::Gatling:
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spGatlingModel, m_upperMatrix);
		break;
	default:
		break;
	}
}
