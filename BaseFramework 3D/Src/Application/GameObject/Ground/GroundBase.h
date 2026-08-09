#pragma once

class GroundBase :public KdGameObject
{
public:
	GroundBase()						{}
	virtual ~GroundBase()	override	{}

	virtual void Init()				override;
	virtual void Update()			override;
	virtual void DrawLit()			override;

protected:

	//モデル
	std::shared_ptr<KdModelData>	m_spModel = nullptr;

	//座標
	Math::Vector3	m_pos = Math::Vector3::Zero;

	//拡縮
	Math::Vector3	m_scale = { 1.0f,1.0f,1.0f };
};