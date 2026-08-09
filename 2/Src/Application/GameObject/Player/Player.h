#pragma once

class Player :public KdGameObject
{
public:

	Player()			{};
	~Player()override	{};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

private:

	std::shared_ptr<KdModelWork>	m_spModel;

	Math::Vector3	m_scale = Math::Vector3::One;
	Math::Vector3	m_pos	= Math::Vector3::Zero;

	float	m_movePower = 0.3f;
};