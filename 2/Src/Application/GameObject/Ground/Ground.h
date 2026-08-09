#pragma once

class Ground :public KdGameObject
{
public:

	Ground()			{};
	~Ground()override	{};

	void Init()		override;
	void Update()	override;
	void PostUpdate()	override;
	void DrawLit()	override;


private:

	std::shared_ptr<KdModelData>	m_spModel = nullptr;

	Math::Vector3	m_scale = Math::Vector3::Zero;
	Math::Vector3	m_pos	= Math::Vector3::Zero;
};