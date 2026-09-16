#pragma once

class Portal :public KdGameObject
{
public:
	Portal()			{};
	~Portal()override	{};
	
	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

	Math::Vector3 GetPos() const override { return m_pos; }

private:

	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Vector3	m_pos	= Math::Vector3::Zero;
	Math::Vector3	m_scale = Math::Vector3::One;
};