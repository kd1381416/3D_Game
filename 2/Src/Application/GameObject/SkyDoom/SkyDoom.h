#pragma once

class SkyDoom :public KdGameObject
{
public:

	SkyDoom()			{}
	~SkyDoom()override	{}

	void Init()			override;
	void DrawUnLit()	override;

private:

	std::shared_ptr<KdModelData>	m_spSkyDoomModel;

	Math::Vector3	m_pos = Math::Vector3::Zero;

	float	m_scale;
};