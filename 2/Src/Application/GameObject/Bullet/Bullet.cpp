#include "Bullet.h"

#include <Application/Scene/SceneManager.h>

void Bullet::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Model/Bullet/Bullet.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Bullet", m_pos + Math::Vector3(0, 0.2f, 0.0f), 0.35f, KdCollider::TypeDamage);
	}

	if (!m_pDebugWire)
	{
		m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	}

	m_lifeTime = 60.0f;
}

void Bullet::Update()
{
	m_lifeTime--;

	m_pos += (m_dir * m_movePower);

	KdCollider::SphereInfo _sphere;
	_sphere.m_sphere.Center = m_pos + Math::Vector3(0, 0.2f, 0.0f);
	_sphere.m_sphere.Radius = 0.35f; // 弾の半径を設定
	_sphere.m_type = KdCollider::TypeDamage | KdCollider::TypeGround;

	//全てのオブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//敵と当たったら入る
		if (obj->Intersects(_sphere, nullptr))
		{
			OnHit();
			obj->OnHit();
		}
	}

	//m_pDebugWire->AddDebugSphere(_sphere.m_sphere.Center,_sphere.m_sphere.Radius,kRedColor);

	Math::Matrix	_scale		= Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_trans		= Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * m_rotation * _trans;
}

void Bullet::PostUpdate()
{
	if (m_lifeTime <= 0)
	{
		m_isExpired = true;
	}
}

void Bullet::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Bullet::Shot(const Math::Vector3 & _pos, const Math::Vector3 & _dir, const float _movePower)
{
	m_pos = _pos;
	m_dir = _dir;
	m_dir.Normalize();

	m_movePower = _movePower;

//======================================================================
// 照準へのベクトルと弾の進行ベクトルから弾の向き(回転行列)を作成
//======================================================================

// ① ベクトルＡ　・・・　弾の現在の進行ベクトル
	Math::Vector3 vecA = m_mWorld.Backward();
	vecA.Normalize();

	// ② ベクトルＢ　・・・　照準への進行ベクトル
	Math::Vector3 vecB = m_dir;
	vecB.Normalize();
		
	// ①と②のベクトルの内積値から角度を算出
	float dot = vecA.Dot(vecB);		// 内積値を算出
	float angle = acos(dot);		// 内積値からacosで２つのベクトルの角度を算出

	// ①と②のベクトルの外積を利用して、回転する為のベクトル(回転軸)を作成
	Math::Vector3 rotAxis = vecA.Cross(vecB);

	// 内積で算出した角度分、外積で算出したベクトル(回転軸)で回転する行列を作成
	// 弾がレティクルの方向を向く
	m_rotation = Math::Matrix::CreateFromAxisAngle(rotAxis, angle);

}
