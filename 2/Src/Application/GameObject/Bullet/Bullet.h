#pragma once

class Bullet :public KdGameObject
{
public:
	Bullet()			{};
	~Bullet()override	{};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	void Shot(const Math::Vector3& _pos, const Math::Vector3& _dir, const float _movePower);

	void OnHit() override 
	{
		m_isExpired = true; 
	}

private:

	std::shared_ptr<KdModelWork>	m_spModel = nullptr;	//モデル

	Math::Vector3	m_pos	= Math::Vector3::Zero;	//座標
	Math::Vector3	m_dir	= Math::Vector3::Zero;	//方向
	Math::Vector3	m_scale = Math::Vector3::One;	//拡縮
	
	Math::Matrix	m_rotation = Math::Matrix::Identity;	//回転

	float	m_movePower = 0.3f;	//移動力
	float	m_lifeTime	= 0.0f;
};