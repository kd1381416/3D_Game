#pragma once

class TPSCamera;
class EnemyBase;

class Retricle :public KdGameObject
{
public:
	Retricle()			{};
	~Retricle()override {};

	void Init()			override;
	void Update()		override;
	void DrawEffect()	override;
	void DrawBright()	override;
	void DrawSprite()	override;

	void SetTargetEnemy(const std::shared_ptr<EnemyBase>& _target)
	{
		m_wpTargetEnemy = _target;
	}

	void SetCamera(const std::shared_ptr<TPSCamera>& _camera)
	{
		m_wpCamera = _camera;
	}

private:

	std::shared_ptr<KdTexture>			m_spReticleTexture	= nullptr;	//通常時のレティクル
	std::shared_ptr<KdSquarePolygon>	m_spTargetPolygon	= nullptr;	//ターゲット時のレティクル
	std::weak_ptr<EnemyBase>			m_wpTargetEnemy;				//ターゲットしているエネミー
	std::weak_ptr<TPSCamera>			m_wpCamera;						//カメラ

	Math::Vector3	m_pos = Math::Vector3::Zero;	//座標

	bool	m_isTargetEnemy = false;	//ターゲットしているかどうか
};